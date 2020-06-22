#include "component.hpp"
#include <mutex>

#ifndef RPICOMPONENTS_MPU6050_H
#define RPICOMPONENTS_MPU6050_H

namespace rpicomponents {
    constexpr const char* COMPONENT_MPU6050 = "mpu6050";

	enum GYRO_SENSITIVITY {
		DPS_250, DPS_500, DPS_1000, DPS_2000 // available gyro scale ranges; see data sheet
	};

	enum ACCEL_SENSITIVITY {
		G_2, G_4, G_8, G_16 // available acceleration scale ranges; see data sheet
	};

	static const std::map<GYRO_SENSITIVITY, int> GYRO_SEL_MAP = { 
		{DPS_250, 0b00000000}, 
		{DPS_500, 0b00001000}, 
		{DPS_1000, 0b00010000}, 
		{DPS_2000, 0b00011000}
	};

	static const std::map<GYRO_SENSITIVITY, float> GYRO_SCALE_FACTOR_MAP = { 
		{DPS_250, 131.0}, 
		{DPS_500, 65.5}, 
		{DPS_1000, 32.8}, 
		{DPS_2000, 16.4} 
	};

	static const std::map<ACCEL_SENSITIVITY, int> ACCEL_SEL_MAP = { 
		{G_2, 0b00000000}, 
		{G_4, 0b00001000}, 
		{G_8, 0b00010000}, 
		{G_16, 0b00011000}
	};

	static const std::map<ACCEL_SENSITIVITY, float> ACCEL_SCALE_FACTOR_MAP = { 
		{G_2, 16384.0}, 
		{G_4, 8192.0}, 
		{G_8, 4096.0}, 
		{G_16, 2048.0}
	};

	struct Accelerations {
		float a_x = 0, a_y = 0, a_z = 0;
	};

	struct Gyro {
		float g_x = 0, g_y = 0, g_z = 0;
	};

	class MPU6050 : public Component {
	// see https://www.electronicwings.com/raspberry-pi/mpu6050-accelerometergyroscope-interfacing-with-raspberry-pi
	private:
		const int PWR_MGMT_1 {0x6B}, SMPLRT_DIV {0x19}, CONFIG {0x1A}, GYRO_CONFIG {0x1B}, ACCEL_CONFIG {0x1C}, INT_ENABLE {0x38},
			ACCEL_XOUT_H {0x3B}, ACCEL_YOUT_H {0x3D}, ACCEL_ZOUT_H {0x3F}, GYRO_XOUT_H {0x43}, GYRO_YOUT_H {0x45}, GYRO_ZOUT_H {0x47}, // collection of needed addresses of MPU according to data sheet
			OFFSET_RUNS = 100; 

		const int address_ {0x68}, fd_; //std address
		const float gyro_scale_, accel_scale_;
		std::mutex mtx_;
		Accelerations offset_acc_; 
		Gyro offset_gyro_;
		
		/*
		Method to init component

		@param accel: Acceleration range of MPU
		@param gyro: Gyro range of mMPUu
		*/
		void Init(ACCEL_SENSITIVITY accel, GYRO_SENSITIVITY gyro) const;

		/*
		Method to read raw value from i2c and converts it via given scale

		@param reg: The register from which the value is to be read
		@param scale: The scale for value conversion
		@returns the read and converted value
		*/
		float ReadRawAndConvert(int reg, float scale);

	public:
		

        /*
         Constructor for this component
		 
		 @param address: Address of MPU
         @param accel: Acceleration range of MPU
		 @param gyro: Gyro range of MPU
        */
        MPU6050(int address = 0x68, ACCEL_SENSITIVITY accel = G_2, GYRO_SENSITIVITY gyro = DPS_250);

		/*
         Constructor for this component
		 
		 @param address: Address of MPU
		 @param offset_acc: Previously retrieved acceleration offset of MPU
		 @param offset_gyro: Previously retrieved gyro offset of MPU
         @param accel: Acceleration range of MPU
		 @param gyro: Gyro range of MPU
        */
        MPU6050(int address, Accelerations offset_acc, Gyro offset_gyro, ACCEL_SENSITIVITY accel = G_2, GYRO_SENSITIVITY gyro = DPS_250);

		/*
		Method to read acceleration of MPU at all three axis

		@returns struct containing the acceleration of all three axis
		*/
		Accelerations GetAcceleration();

		/*
		Method to calibrate accelerations. 
		The calibrated values are automatically substracted when retrieving the values via GetAcceleration().
		Note: Keep MPU horizontally and vertically aligned on a flat surface. Process takes <1s
		@returns offset of the accelerations
		*/
		const Accelerations& CalibrateAcceleration();

		/*
		Method to get acceleration offset
		@returns offset of the acceleration
		*/
		const Accelerations& GetAccelerationOffset() const;

		/*
		Method to read gyro values of MPU at all three axis

		@returns struct containing the gyro values of all three axis
		*/
		Gyro GetGyro();

		/*
		Method to calibrate gyro. 
		The calibrated values are automatically substracted when retrieving the values via GetGyro().
		Note: Keep MPU horizontally and vertically aligned on a flat surface. Process takes < 1s
		@returns offset of the gyro
		*/
		const Gyro& CalibrateGyro();

		/*
		Method to get gyro offset
		@returns offset of the gyro
		*/
		const Gyro& GetGyroOffset() const;

	};
}

#endif // RPICOMPONENTS_MPU6050_H
