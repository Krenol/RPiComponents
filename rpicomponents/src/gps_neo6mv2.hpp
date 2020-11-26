#include "component.hpp"

#ifndef RPICOMPONENTS_GPS_NEO_6MV2_H
#define RPICOMPONENTS_GPS_NEO_6MV2_H

namespace rpicomponents {
    constexpr const char* COMPONENT_GPS_NEO_6MV2 = "GPS NEO-6MV2";

    struct GPSCoordinates {
        float longitude = 0, latitude = 0, altitude = 0;
    };

	class GpsNeo6MV2 : public Component {
    private:
        static const std::string PROTOCOL_HEAD, DELIM, NEW_LINE;
        static const int BUFFER_SIZE;
        char* sertty_;
        int handle_;

        /**
         * Method that reads all lines from the Serial
         * @param l string to store all read lines
         */
        void readFromSerial(std::string& l);

        /**
         * Method that reads the PROTOCOL_HEAD line
         * @param l string to store the PROTOCOL_HEAD line
         */
        void getCoordLine(std::string& l);

        /**
         * Method that splits a string at the DELIM
         * @param l string to be split
         * @param out The vector where the splits are to be stored
         */
        void splitLine(const std::string& l, std::vector<std::string>& out);

        /**
         * Convert a read longitude/latitude to degrees
         * @param all the value to be converted
         * @returns the read values transformed to degrees or INFINITIY on error
         */
        float convertToDegrees(const std::string& val);

	public:
        /**
         * Constructor for GPS NEO 6MV2 module
         * @param sertty The serial file to open
         * @param baud Baud rate to read from file
         */
        GpsNeo6MV2(const std::string& sertty = "/dev/ttyS0", int baud = 4800);

        /**
         * Destructor
         */
        ~GpsNeo6MV2();

        /**
         * Get GPS coordinates from serial
         * @param c Struct to write cords to
         */
        void getCoordinates(GPSCoordinates& c);
	};
}

#endif // RPICOMPONENTS_MOTOR_H
