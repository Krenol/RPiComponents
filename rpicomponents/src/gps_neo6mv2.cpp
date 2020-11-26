#include "gps_neo6mv2.hpp"
#include <pigpio.h>
#include <cmath>
#include <string.h>

const std::string rpicomponents::GpsNeo6MV2::PROTOCOL_HEAD = "$GPGGA", rpicomponents::GpsNeo6MV2::DELIM = ",", rpicomponents::GpsNeo6MV2::NEW_LINE = "\r\n";
const int rpicomponents::GpsNeo6MV2::BUFFER_SIZE = 200;

namespace rpicomponents
{
    void GpsNeo6MV2::readFromSerial(std::string &l)
    {
        std::vector<char> buf(BUFFER_SIZE);
        int bytes_read = serRead(handle_, &buf[0], BUFFER_SIZE);
        if (bytes_read < 0)
        {
            l = "error";
        }
        else
        {
            l = std::string(buf.begin(), buf.end());
        }
    }

    void GpsNeo6MV2::getCoordLine(std::string &l)
    {
        std::string buf = "";
        size_t pos_h, pos_n;
        // read from Serial as long as the PROTOCOL_HEAD is not found and the string doesn't end with a new line
        do
        {
            readFromSerial(l);
            buf += l;
            pos_h = buf.find(PROTOCOL_HEAD);
            pos_n = buf.find_last_of(NEW_LINE);
        } while (pos_h != std::string::npos && pos_n != std::string::npos && pos_n < pos_h);
        // trim string
        buf.erase(0, pos_h);
        pos_n = buf.find(NEW_LINE);
        buf.erase(pos_n);
        // save string to return
        l = buf;
    }

    void GpsNeo6MV2::splitLine(const std::string &l, std::vector<std::string> &out)
    {
        size_t pos = 0;
        std::string s = l;
        while ((pos = s.find(DELIM)) != std::string::npos)
        {
            out.push_back(s.substr(0, pos));
            s.erase(0, pos + DELIM.length());
        }
    }

    float GpsNeo6MV2::convertToDegrees(const std::string &val)
    {
        float f;
        int deg;
        try
        {
            f = std::stof(val) / 100;
            deg = (int)f;
            f = (f - deg) / 0.6;
            f += (float)deg;
        }
        catch (...)
        {
            return INFINITY;
        }
        return f;
    }

    GpsNeo6MV2::GpsNeo6MV2(const std::string &sertty, int baud) : Component(COMPONENT_GPS_NEO_6MV2)
    {
        sertty_ = new char[sertty.length() + 1];
        strcpy(sertty_, sertty.c_str());
        handle_ = serOpen(sertty_, baud, 0);
        if (handle_ < 0)
        {
            throw std::runtime_error("couldn't open serial to GPS module!");
        }
    }

    GpsNeo6MV2::~GpsNeo6MV2() 
    {
        serClose(handle_);
        delete [] sertty_;
    }

    void GpsNeo6MV2::getCoordinates(GPSCoordinates &c)
    {
        std::string l;
        std::vector<std::string> out;
        // line should be $GPGGA,hhmmss:ss,Latitude,N,Longitude,E,FS,NoSV,HDOP,Alt,m,Altref,m,DiffAge,DiffStation*cs
        getCoordLine(l);
        splitLine(l, out);
        // with 15 lines read, read serial line is valid
        if (out.size() == 15)
        {
            c.latitude = convertToDegrees(out[2]);
            c.longitude = convertToDegrees(out[4]);
            c.altitude = std::stof(out[9]);
        }
        else
        {
            // set error values
            c.latitude = INFINITY;
            c.longitude = INFINITY;
            c.altitude = INFINITY;
        }
    }

} // namespace rpicomponents