#include "mpu6050.hpp"
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <iostream>

namespace rpicomponents
{
	void MPU6050::Init(ACCEL_SENSITIVITY accel, GYRO_SENSITIVITY gyro) const
	{
		//x axis gyro as clock ref
		wiringPiI2CWriteReg8 (fd_, PWR_MGMT_1, 0b00000001);	
		//setup sample rate -> Sample Rate = Gyroscope Output Rate / (1 + SMPLRT_DIV) with SMPLRT_DIV=7
		wiringPiI2CWriteReg8 (fd_, SMPLRT_DIV, 0b00000111); 
		//no FSYNC & filtering of accel and gyro signals
		wiringPiI2CWriteReg8 (fd_, CONFIG, 0b00000000); 
		//enable data interrupt -> occurs each time a write operation to all of the sensor registers has been completed.
		wiringPiI2CWriteReg8 (fd_, INT_ENABLE, 0b00000001);	

		//set gyro sensitivity
		auto g = GYRO_SEL_MAP.at(gyro);
		wiringPiI2CWriteReg8 (fd_, GYRO_CONFIG, g);

		//set accel sensitivity
		auto a = ACCEL_SEL_MAP.at(accel);
		wiringPiI2CWriteReg8 (fd_, ACCEL_CONFIG, a);
	}

	float MPU6050::ReadRawAndConvert(int reg, float scale)
	{
		short low, high;
		{
			std::lock_guard<std::mutex> guard(mtx_);
			high = wiringPiI2CReadReg8(fd_, reg);
			low = wiringPiI2CReadReg8(fd_, reg + 1);
		}
		high <<= 8;
		high |= low;
		float value = high / scale;
		return value;
	}
	
	MPU6050::MPU6050(int address, ACCEL_SENSITIVITY accel, GYRO_SENSITIVITY gyro) : 
		Component(COMPONENT_MPU6050), 
		address_{address},
		gyro_scale_{GYRO_SCALE_FACTOR_MAP.at(gyro)},
		accel_scale_{ACCEL_SCALE_FACTOR_MAP.at(accel)},
		fd_{wiringPiI2CSetup(address)}
	{
		if(fd_ < 0) {
			throw std::invalid_argument("Error while initializing MPU6050");
		}
		Init(accel, gyro);
	}

	MPU6050::MPU6050(int address, Accelerations offset_acc, Gyro offset_gyro, ACCEL_SENSITIVITY accel, GYRO_SENSITIVITY gyro) : 
		Component(COMPONENT_MPU6050), 
		address_{address},
		gyro_scale_{GYRO_SCALE_FACTOR_MAP.at(gyro)},
		accel_scale_{ACCEL_SCALE_FACTOR_MAP.at(accel)},
		fd_{wiringPiI2CSetup(address)}
	{
		if(fd_ < 0) {
			throw std::invalid_argument("Error while initializing MPU6050");
		}
		offset_acc_ = offset_acc;
		offset_gyro_ = offset_gyro;
		Init(accel, gyro);
	}
	
	Accelerations MPU6050::GetAcceleration()
	{
		Accelerations acc;
		acc.a_x = ReadRawAndConvert(ACCEL_XOUT_H, accel_scale_) - offset_acc_.a_x;
		acc.a_y = ReadRawAndConvert(ACCEL_YOUT_H, accel_scale_) - offset_acc_.a_y;
		acc.a_z = ReadRawAndConvert(ACCEL_ZOUT_H, accel_scale_) - offset_acc_.a_z;
		return acc;
	}
	
	const Accelerations& MPU6050::CalibrateAcceleration() 
	{
		Accelerations acc;
		for(int i = 0; i < OFFSET_RUNS; i++){
			acc.a_x += ReadRawAndConvert(ACCEL_XOUT_H, accel_scale_);
			acc.a_y += ReadRawAndConvert(ACCEL_YOUT_H, accel_scale_);
			acc.a_z += ReadRawAndConvert(ACCEL_ZOUT_H, accel_scale_);
		}
		acc.a_x /= OFFSET_RUNS;
		acc.a_y /= OFFSET_RUNS;
		acc.a_z /= OFFSET_RUNS;
		acc.a_z -= 1; //std value should be 1g, so substract 1
		offset_acc_ = acc;
		return offset_acc_;
	}
	
	const Accelerations& MPU6050::GetAccelerationOffset() const
	{
		return offset_acc_;
	}
	
	Gyro MPU6050::GetGyro()
	{
		Gyro g;
		g.g_x = ReadRawAndConvert(GYRO_XOUT_H, gyro_scale_) - offset_gyro_.g_x;
		g.g_y = ReadRawAndConvert(GYRO_YOUT_H, gyro_scale_) - offset_gyro_.g_y;
		g.g_z = ReadRawAndConvert(GYRO_ZOUT_H, gyro_scale_) - offset_gyro_.g_z;
		return g;
	}
	
	const Gyro& MPU6050::CalibrateGyro() 
	{
		Gyro g;
		for(int i = 0; i < OFFSET_RUNS; i++){
			g.g_x += ReadRawAndConvert(GYRO_XOUT_H, gyro_scale_);
			g.g_y += ReadRawAndConvert(GYRO_YOUT_H, gyro_scale_);
			g.g_z += ReadRawAndConvert(GYRO_ZOUT_H, gyro_scale_);
		}
		g.g_x /= OFFSET_RUNS;
		g.g_y /= OFFSET_RUNS;
		g.g_z /= OFFSET_RUNS;	
		offset_gyro_ = g;
		return offset_gyro_;
	}
	
	const Gyro& MPU6050::GetGyroOffset() const
	{
		return offset_gyro_;
	}
}