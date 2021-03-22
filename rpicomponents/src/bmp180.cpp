#include "bmp180.hpp"
#include <pigpio.h>
#include <cmath>
#include <unistd.h>

namespace rpicomponents
{

    template <typename T>
    void Bmp180<T>::Initialize()
    {
        std::vector<int> addr = {AC1, AC2, AC3, AC4, AC5, AC6, B1, B2, MB, MC, MD};
        std::map<int, int> reg_table = {
            {AC1, 1},
            {AC2, 1},
            {AC3, 1},
            {AC4, 0},
            {AC5, 0},
            {AC6, 0},
            {B1, 1},
            {B2, 1},
            {MB, 1},
            {MC, 1},
            {MD, 1}};
        int ad;
        for (auto i = 0; i < addr.size(); i++)
        {
            ad = addr.at(i);
            auto data = i2cReadByteData(handle_, addr.at(i)); // & 0xFFFF;
            auto store = ((data << 8) & 0xFF00) + (data >> 8);
            if (reg_table.at(addr.at(i)) && (store > 32767))
            {
                store -= 65536;
            }
            eprom_.emplace(ad, store);
        }
        bmp_kalman_conf c;
        SetKalmanConfig(c);
    }

    template <typename T>
    int Bmp180<T>::readRawTemperature()
    {
        // https://cdn.shopify.com/s/files/1/1509/1638/files/GY-68_BMP180_Barometrischer_Sensor_Luftdruck_Modul_fur_Arduino_und_Raspberry_Pi_Datenblatt.pdf?15836792964504220844
        // tell device we want to read the temp
        i2cWriteByteData(handle_, CTRL, TMP_RD_CMD);
        // wait for callback from i2c
        usleep(TMP_WAIT_TIME);
        // read data & convert
        auto msb = i2cReadByteData(handle_, TMP); // & 0xFFFF;
        auto lsb = i2cReadByteData(handle_, LSB); // I added this..
        auto data = (msb << 8) + lsb;
        return data;
    }

    template <typename T>
    int Bmp180<T>::readRawPressure()
    {
        //https://cdn.shopify.com/s/files/1/1509/1638/files/GY-68_BMP180_Barometrischer_Sensor_Luftdruck_Modul_fur_Arduino_und_Raspberry_Pi_Datenblatt.pdf?15836792964504220844
        i2cWriteByteData(handle_, CTRL, pres_.cmd);
        usleep(pres_.t);
        auto msb = i2cReadByteData(handle_, PRE);   // & 0xFF;
        auto lsb = i2cReadByteData(handle_, LSB);   // & 0xFF;
        auto xlsb = i2cReadByteData(handle_, XLSB); // & 0xFF;
        auto data = ((msb << 16) + (lsb << 8) + xlsb) >> (8 - pres_.res);
        return data;
    }

    template <typename T>
    void Bmp180<T>::getTempByteData(bmp180_temp_data &data)
    {
        data.UT = readRawTemperature();
        data.X1 = ((data.UT - eprom_.at(AC6)) * eprom_.at(AC5)) >> 15;
        data.X2 = (eprom_.at(MC) << 11) / (data.X1 + eprom_.at(MD));
        data.B5 = data.X1 + data.X2;
    }

    template <typename T>
    float Bmp180<T>::getTemperature()
    {
        bmp180_temp_data data;
        getTempByteData(data);
        auto t = ((data.B5 + 8) >> 4) / 10.0;

        return t - T_ABS_ZERO; // convert to K
    }

    template <typename T>
    long Bmp180<T>::getPressure()
    {
        bmp180_temp_data data;
        getTempByteData(data);
        auto UP = readRawPressure();
        auto B6 = data.B5 - 4000;
        auto X1 = (eprom_.at(B2) * ((B6 * B6) >> 12)) >> 11;
        auto X2 = (eprom_.at(AC2) * B6) >> 11;
        auto X3 = X1 + X2;
        auto B3 = ((((eprom_.at(AC1) * 4) + X3) << pres_.res) + 2) / 4;

        X1 = (eprom_.at(AC3) * B6) >> 13;
        X2 = (eprom_.at(B1) * ((B6 * B6) >> 12)) >> 16;
        X3 = ((X1 + X2) + 2) >> 2;

        unsigned long B4 = eprom_.at(AC4) * (unsigned long)(X3 + 32768) >> 15;
        unsigned long B7 = ((unsigned long)UP - B3) * (50000 >> pres_.res);

        long p = B7 < 0x80000000 ? ((B7 * 2) / B4) : ((B7 / B4) * 2);
        X1 = (p >> 8) * (p >> 8);
        X1 = (X1 * 3038) >> 16;
        X2 = (-7357 * p) >> 16;
        p = p + ((X1 + X2 + 3791) >> 4);

        return p;
    }

    template <typename T>
    long Bmp180<T>::getPressureKalman()
    {
        auto p = getPressure();
        Eigen::VectorXd z(1), x;
        z << p;
        kalman_->predict(x, z);
        return x[0];
    }

    template <typename T>
    float Bmp180<T>::getAltitude()
    {
        float p = getPressure() / 100.0;
        float alt = 44330.77 * (1 - pow((p / PRESSURE_SEA_LVL), 1 / 5.255));
        return alt;
    }

    template <typename T>
    float Bmp180<T>::getAltitudeKalman()
    {
        auto p = getPressureKalman() / 100.0;
        float alt = 44330.77 * (1 - pow((p / PRESSURE_SEA_LVL), 1 / 5.255));
        return alt;
    }

    template <typename T>
    float Bmp180<T>::getDensity()
    {
        float p = getPressure();
        float t = getTemperature();
        float rho = p / (R * t);
        return rho;
    }

    template <typename T>
    void Bmp180<T>::getBarometricData(BarometricData &data)
    {
        data.altitude = getAltitude();
        data.density = getDensity();
        data.pressure = getPressure();
        data.temperature = getTemperature();
    }

    template <typename T>
    void Bmp180<T>::SetKalmanConfig(bmp_kalman_conf &conf)
    {
        conf.res = pres_.res;
        auto p = getPressure();
        Eigen::VectorXd x_0(2);
        x_0 << p, 0;
        kalman_ = std::make_unique<Bmp180_Kalman<T>>(conf, x_0);
    }

    template <typename T>
    Bmp180<T>::Bmp180(int address, const bmp180_pressure_resolution &res) : Component(COMPONENT_BMP180), address_{address}, handle_{i2cOpen(I2C_BUS_CHANNEL, address, 0)}, pres_{BMP_RES_MAP.at(res)}
    {
        if (handle_ < 0)
        {
            throw std::invalid_argument("Error while initializing BMP180");
        }
        Initialize();
    }

    template <typename T>
    Bmp180<T>::~Bmp180()
    {
        try
        {
            i2cClose(handle_);
        }
        catch (...)
        {
        }
    }

    template <typename T>
    const float Bmp180<T>::R = 287.05;
    template <typename T>
    const float Bmp180<T>::PRESSURE_SEA_LVL = 1013.25;
    template <typename T>
    const float Bmp180<T>::T_ABS_ZERO = -273.15;

    template <typename T>
    const int Bmp180<T>::AC1 = 0xAA;
    template <typename T>
    const int Bmp180<T>::AC2 = 0xAC;
    template <typename T>
    const int Bmp180<T>::AC3 = 0xAE;
    template <typename T>
    const int Bmp180<T>::AC4 = 0xB0;
    template <typename T>
    const int Bmp180<T>::AC5 = 0xB2;
    template <typename T>
    const int Bmp180<T>::AC6 = 0xB4;
    template <typename T>
    const int Bmp180<T>::B1 = 0xB6;
    template <typename T>
    const int Bmp180<T>::B2 = 0xB8;
    template <typename T>
    const int Bmp180<T>::MB = 0xBA;
    template <typename T>
    const int Bmp180<T>::MC = 0xBC;
    template <typename T>
    const int Bmp180<T>::MD = 0xBE;
    template <typename T>
    const int Bmp180<T>::CTRL = 0xF4;
    template <typename T>
    const int Bmp180<T>::TMP = 0xF6;
    template <typename T>
    const int Bmp180<T>::PRE = 0xF6;
    template <typename T>
    const int Bmp180<T>::LSB = 0xF7;
    template <typename T>
    const int Bmp180<T>::XLSB = 0xF8;
    template <typename T>
    const int Bmp180<T>::TMP_RD_CMD = 0x2E;
    template <typename T>
    const int Bmp180<T>::TMP_WAIT_TIME = 5000;

    template class Bmp180<std::chrono::hours>;
    template class Bmp180<std::chrono::minutes>;
    template class Bmp180<std::chrono::seconds>;
    template class Bmp180<std::chrono::milliseconds>;
    template class Bmp180<std::chrono::microseconds>;
    template class Bmp180<std::chrono::nanoseconds>;
} // namespace rpicomponents
