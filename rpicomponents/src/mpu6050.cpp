#include "mpu6050.hpp"
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <iostream>
#include "utils/utils.hpp"

namespace rpicomponents
{
	void MPU6050::Init(ACCEL_SENSITIVITY accel, GYRO_SENSITIVITY gyro) const
	{
		//x axis gyro as clock ref
		wiringPiI2CWriteReg8 (fd_, PWR_MGMT_1, 0b00000001);	
		//setup sample rate -> Sample Rate = Gyroscope Output Rate / (1 + SMPLRT_DIV) with SMPLRT_DIV=7
		wiringPiI2CWriteReg8 (fd_, SMPLRT_DIV, 0b00000111); 
		//no FSYNC & filtering of accel and gyro signals -> DLPF with 5 Hz bandwidth
		wiringPiI2CWriteReg8 (fd_, CONFIG, 0b00000110); 
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
		GetAcceleration(acc);
		return acc;
	}
	
	void MPU6050::GetAcceleration(Accelerations& out) 
	{
		out.a_x = ReadRawAndConvert(ACCEL_XOUT_H, accel_scale_) - offset_acc_.a_x;
		out.a_y = ReadRawAndConvert(ACCEL_YOUT_H, accel_scale_) - offset_acc_.a_y;
		out.a_z = ReadRawAndConvert(ACCEL_ZOUT_H, accel_scale_) - offset_acc_.a_z;
	}
	
	void MPU6050::GetAccelerationJSON(nlohmann::json& out) 
	{
		float val = ReadRawAndConvert(ACCEL_XOUT_H, accel_scale_) - offset_acc_.a_x;
		out.at("a_x").get_to(val);
		val = ReadRawAndConvert(ACCEL_YOUT_H, accel_scale_) - offset_acc_.a_y;
        out.at("a_y").get_to(val);
		val = ReadRawAndConvert(ACCEL_ZOUT_H, accel_scale_) - offset_acc_.a_z;
		out.at("a_z").get_to(val);
	}
	
	nlohmann::json MPU6050::GetAccelerationJSON() 
	{
		nlohmann::json j;
		GetAccelerationJSON(j);
		return j;
	}
	
	const Accelerations& MPU6050::CalibrateAcceleration() 
	{
		std::vector<double> x, y, z;
		for(int i = 0; i < OFFSET_RUNS; i++){
			x.push_back(ReadRawAndConvert(ACCEL_XOUT_H, accel_scale_));
			y.push_back(ReadRawAndConvert(ACCEL_YOUT_H, accel_scale_));
			z.push_back(ReadRawAndConvert(ACCEL_ZOUT_H, accel_scale_));
		}
		{
			std::lock_guard<std::mutex> guard(mtx_);
			offset_acc_.a_x = utils::Maths::mean(x);
			offset_acc_.a_y = utils::Maths::mean(y);
			offset_acc_.a_z = utils::Maths::mean(z) - 1;
			offset_acc_.d_x = utils::Maths::deviation(x);
			offset_acc_.d_y = utils::Maths::deviation(y);
			offset_acc_.d_z = utils::Maths::deviation(z);
		}

		return offset_acc_;
	}
	
	const Accelerations& MPU6050::GetAccelerationOffset() const
	{
		return offset_acc_;
	}
	
	Gyro MPU6050::GetGyro()
	{
		Gyro g;
		GetGyro(g);
		return g;
	}
	
	void MPU6050::GetGyroJSON(nlohmann::json& out) 
	{
		float val = ReadRawAndConvert(GYRO_XOUT_H, gyro_scale_) - offset_gyro_.g_x;
		out.at("g_x").get_to(val);
		val = ReadRawAndConvert(GYRO_YOUT_H, gyro_scale_) - offset_gyro_.g_y;
        out.at("g_y").get_to(val);
		val = ReadRawAndConvert(GYRO_ZOUT_H, gyro_scale_) - offset_gyro_.g_z;
		out.at("g_z").get_to(val);
	}
	
	nlohmann::json MPU6050::GetGyroJSON() 
	{
		nlohmann::json j;
		GetGyroJSON(j);
		return j;
	}
	
	void MPU6050::GetGyro(Gyro& out) 
	{
		out.g_x = ReadRawAndConvert(GYRO_XOUT_H, gyro_scale_) - offset_gyro_.g_x;
		out.g_y = ReadRawAndConvert(GYRO_YOUT_H, gyro_scale_) - offset_gyro_.g_y;
		out.g_z = ReadRawAndConvert(GYRO_ZOUT_H, gyro_scale_) - offset_gyro_.g_z;
	}
	
	const Gyro& MPU6050::CalibrateGyro() 
	{
		std::vector<double> x, y, z;
		for(int i = 0; i < OFFSET_RUNS; i++){
			x.push_back(ReadRawAndConvert(GYRO_XOUT_H, gyro_scale_));
			y.push_back(ReadRawAndConvert(GYRO_YOUT_H, gyro_scale_));
			z.push_back(ReadRawAndConvert(GYRO_ZOUT_H, gyro_scale_));
		}
		{
			std::lock_guard<std::mutex> guard(mtx_);
			offset_gyro_.g_x = utils::Maths::mean(x);
			offset_gyro_.g_y = utils::Maths::mean(y);
			offset_gyro_.g_z = utils::Maths::mean(z);
			offset_gyro_.d_x = utils::Maths::deviation(x);
			offset_gyro_.d_y = utils::Maths::deviation(y);
			offset_gyro_.d_z = utils::Maths::deviation(z);
		}
		
		return offset_gyro_;
	}
	
	const Gyro& MPU6050::GetGyroOffset() const
	{
		return offset_gyro_;
	}
	
	nlohmann::json MPU6050::GetOffsets() 
	{
		nlohmann::json j;
		GetOffsets(j);
		return j;
	}
	
	void MPU6050::GetOffsets(nlohmann::json& json) 
	{
		j["offsets"]["gyro"] = offset_gyro_;
		j["offsets"]["acceleration"] = offset_acc_;
	}

	void to_json(nlohmann::json& j, const Accelerations& d) {
        j = nlohmann::json{{"a_x", d.a_x}, {"a_y", d.a_y}, {"z", d.a_z}, {"d_x", d.d_x}, {"d_y", d.d_y}, {"z", d.d_z}};
    }

    void from_json(const nlohmann::json& j, Accelerations& d) {
        j.at("a_x").get_to(d.a_x);
        j.at("a_y").get_to(d.a_y);
		j.at("a_z").get_to(d.a_z);
		j.at("d_x").get_to(d.d_x);
        j.at("d_y").get_to(d.d_y);
		j.at("d_z").get_to(d.d_z);
    }

	void to_json(nlohmann::json& j, const Gyro& d) {
        j = nlohmann::json{{"g_x", d.g_x}, {"g_y", d.g_y}, {"g_z", d.g_z}, {"d_x", d.d_x}, {"d_y", d.d_y}, {"z", d.d_z}};
    }

    void from_json(const nlohmann::json& j, Gyro& d) {
        j.at("g_x").get_to(d.g_x);
        j.at("g_y").get_to(d.g_y);
		j.at("g_z").get_to(d.g_z);
		j.at("d_x").get_to(d.d_x);
        j.at("d_y").get_to(d.d_y);
		j.at("d_z").get_to(d.d_z);
    }
}