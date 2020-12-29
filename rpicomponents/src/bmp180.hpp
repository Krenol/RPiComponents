#include "component.hpp"
#include "bmp180_kalman.hpp"

#ifndef RPICOMPONENTS_BMP180_H
#define RPICOMPONENTS_BMP180_H

namespace rpicomponents {
    constexpr const char* COMPONENT_BMP180 = "BMP180";

    struct BarometricData {
        double temperature = 0, density = 0, altitude = 0;
        long pressure = 0;
    };

    struct bmp180_temp_data {
        long X1, X2, B5, UT;
    };
    
    enum class bmp180_pressure_resolution
	{
		LOW_POWER = 0,
		STANDARD,
		HIGH_RES,
		ULTRA_HIGH_RES
	};

    enum class bmp180_pressure_cmd
	{
		LOW_POWER = 0x34,
		STANDARD = 0x74,
		HIGH_RES = 0xB4,
		ULTRA_HIGH_RES = 0xF4
	};

    enum class bmp180_pressure_wait_time
	{
		LOW_POWER = 5000,
		STANDARD = 8000,
		HIGH_RES = 14000,
		ULTRA_HIGH_RES = 26000
	};

    struct bmp180_pressure {
	    /* Eprom values */
	    int res, cmd, t;

        bmp180_pressure(const bmp180_pressure_resolution& res, const bmp180_pressure_cmd& cmd, const bmp180_pressure_wait_time& t) {
            this->res = (int)res;
            this->cmd = (int)cmd;
            this->t = (int)t;
        };

        bmp180_pressure(const bmp180_pressure& p) {
            this->res = (int)p.res;
            this->cmd = (int)p.cmd;
            this->t = (int)p.t;
        };
    };

    static const std::map<bmp180_pressure_resolution, bmp180_pressure> BMP_RES_MAP = {
		{bmp180_pressure_resolution::LOW_POWER, bmp180_pressure(bmp180_pressure_resolution::LOW_POWER, bmp180_pressure_cmd::LOW_POWER, bmp180_pressure_wait_time::LOW_POWER)},
		{bmp180_pressure_resolution::STANDARD, bmp180_pressure(bmp180_pressure_resolution::STANDARD, bmp180_pressure_cmd::STANDARD, bmp180_pressure_wait_time::STANDARD)},
		{bmp180_pressure_resolution::HIGH_RES, bmp180_pressure(bmp180_pressure_resolution::HIGH_RES, bmp180_pressure_cmd::HIGH_RES, bmp180_pressure_wait_time::HIGH_RES)},
		{bmp180_pressure_resolution::ULTRA_HIGH_RES, bmp180_pressure(bmp180_pressure_resolution::ULTRA_HIGH_RES, bmp180_pressure_cmd::ULTRA_HIGH_RES, bmp180_pressure_wait_time::ULTRA_HIGH_RES)}};

	class Bmp180 : public Component {
    private:
        static const int AC1, AC2, AC3, AC4, AC5, AC6, B1, B2, MB, MC, MD, CTRL, TMP, PRE, TMP_RD_CMD, TMP_WAIT_TIME, LSB, XLSB;
        static const float R, PRESSURE_SEA_LVL, T_ABS_ZERO;
        const int address_;
        int handle_;
        bmp180_pressure pres_;
        std::map<int, int> eprom_;
        std::unique_ptr<Bmp180_Kalman> kalman_;
        
        /**
         * Init eprom of BMP180
         */
        void Initialize();
        
        /**
         * Read raw temp from BMP 180
         */
        int readRawTemperature();

        /**
         * Read raw pressure from BMP180
         */
        int readRawPressure();

        /**
         * Get the temp bytes we need for pressure and temp
         * @param data struct to hold the vals
         */
        void getTempByteData(bmp180_temp_data& data);

	public:
        /**
         * Constructor for GPS NEO 6MV2 module
         * @param address BMP180 address
         * @param res Baud rate to read from file
         */
        Bmp180(int address = 0x77, const bmp180_pressure_resolution& res = bmp180_pressure_resolution::STANDARD);

        /**
         * Destructor
         */
        ~Bmp180();

        /**
         * Get the current temperature in Kelvin
         * @returns the current temperature in Kelvin
         */
        float getTemperature();

        /**
         * Get the current air pressure in Pa
         * @returns the current air pressure in Pa
         */
        long getPressure();
        
        /**
         * Get the current air pressure in Pa
         * @returns the current air pressure in Pa estimated by Kalman Filter
         */
        long getPressureKalman();

        /**
         * Get the altitude based upon the alitude estimation formula 
         * @returns the estimated alitutude above sea level in m
         */
        float getAltitude();

        /**
         * Get the altitude based upon the alitude estimation formula  with kalman estimated pressure
         * @returns the estimated alitutude above sea level in m
         */
        float getAltitudeKalman();

        /**
         * Get the current air density based upon the current pressure and temperature
         * @returns the current air density in kg/m³
         */
        float getDensity();

        /**
         * Get all values inside the barometric data struct
         * @param data the struct where to store the values
         */
        void getBarometricData(BarometricData& data);

        /**
		 * Method to set the config values of the kalman filters
		 * @param conf the config struct
		 */
		void SetKalmanConfig(bmp_kalman_conf& conf);
	};
}

#endif // RPICOMPONENTS_MOTOR_H
