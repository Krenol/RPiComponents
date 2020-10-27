#include "mpu6050.hpp"
#include <cmath>
#include <iostream>

namespace rpicomponents
{
	void MPU6050::Init(ACCEL_SENSITIVITY accel, GYRO_SENSITIVITY gyro) const
	{
		//x axis gyro as clock ref
		i2cWriteByteData (fd_, PWR_MGMT_1, 0b00000001);	
		//setup sample rate -> Sample Rate = Gyroscope Output Rate / (1 + SMPLRT_DIV) with SMPLRT_DIV=7
		i2cWriteByteData (fd_, SMPLRT_DIV, 0b00000111); 
		//no FSYNC & filtering of accel and gyro signals -> DLPF with 5 Hz bandwidth
		i2cWriteByteData (fd_, CONFIG, 0b00000110); 
		//enable data interrupt -> occurs each time a write operation to all of the sensor registers has been completed.
		i2cWriteByteData (fd_, INT_ENABLE, 0b00000001);	

		//set gyro sensitivity
		auto g = GYRO_SEL_MAP.at(gyro);
		i2cWriteByteData (fd_, GYRO_CONFIG, g);

		//set accel sensitivity
		auto a = ACCEL_SEL_MAP.at(accel);
		i2cWriteByteData (fd_, ACCEL_CONFIG, a);
	}

	float MPU6050::ReadRawAndConvert(int reg, float scale)
	{
		short low, high;
		{
			std::lock_guard<std::mutex> guard(mtx_);
			high = i2cReadByteData(fd_, reg);
			low = i2cReadByteData(fd_, reg + 1);
		}
		high <<= 8;
		high |= low;
		float value = high / scale;
		return value;
	}

	MPU6050::~MPU6050() 
	{
		try{
			i2cClose(fd_);
		} catch(...) {

		}
	}
	
	MPU6050::MPU6050(int address, ACCEL_SENSITIVITY accel, GYRO_SENSITIVITY gyro) : 
		Component(COMPONENT_MPU6050), 
		address_{address},
		gyro_scale_{GYRO_SCALE_FACTOR_MAP.at(gyro)},
		accel_scale_{ACCEL_SCALE_FACTOR_MAP.at(accel)},
		fd_{i2cOpen(I2C_BUS_CHANNEL, address_, 0)}
	{
		if(fd_ < 0) {
			throw std::invalid_argument("Error while initializing MPU6050");
		}
		Init(accel, gyro);
	}

	MPU6050::MPU6050(int address, mpu_data offset_acc, mpu_data offset_gyro, ACCEL_SENSITIVITY accel, GYRO_SENSITIVITY gyro) : 
		Component(COMPONENT_MPU6050), 
		address_{address},
		gyro_scale_{GYRO_SCALE_FACTOR_MAP.at(gyro)},
		accel_scale_{ACCEL_SCALE_FACTOR_MAP.at(accel)},
		fd_{i2cOpen(I2C_BUS_CHANNEL, address_, 0)}
	{
		if(fd_ < 0) {
			throw std::invalid_argument("Error while initializing MPU6050");
		}
		offset_acc_ = offset_acc;
		offset_gyro_ = offset_gyro;
		Init(accel, gyro);
	}
	
	mpu_data MPU6050::GetAcceleration()
	{
		mpu_data acc;
		GetAcceleration(acc);
		return acc;
	}
	
	void MPU6050::GetAcceleration(mpu_data& out) 
	{
		out.x = ReadRawAndConvert(ACCEL_XOUT_H, accel_scale_) - offset_acc_.x;
		out.y = ReadRawAndConvert(ACCEL_YOUT_H, accel_scale_) - offset_acc_.y;
		out.z = ReadRawAndConvert(ACCEL_ZOUT_H, accel_scale_) - offset_acc_.z;
		out.unit = MPU_ACC;
	}
	
	void MPU6050::GetAccelerationJSON(nlohmann::json& out) 
	{
		auto data = GetAcceleration();
		out = data;
	}
	
	nlohmann::json MPU6050::GetAccelerationJSON() 
	{
		nlohmann::json j;
		GetAccelerationJSON(j);
		return j;
	}
	
	mpu_angles MPU6050::GetKalmanAngles() 
	{
		mpu_angles a;
		GetKalmanAngles(a);
		return a;
	}
	
	void MPU6050::GetKalmanAngles(mpu_angles& out) 
	{
		out = GetAccelerationAngles();
		mpu_data vel;
		GetAngularVelocity(vel);
		Eigen::VectorXd u(1), z(1);
		z << out.beta;
		std::cout << "z = " << z << std::endl;
		u << vel.x;
		std::cout << "u = " << u << std::endl;
		out.beta = kalman_beta_.predict(z, u)[0];
		z << out.gamma;
		u << vel.y;
		out.gamma = kalman_gamma_.predict(z, u)[0];
		out.unit = MPU_ANGLE;
	}

	void MPU6050::GetKalmanAnglesJSON(nlohmann::json& out) 
	{
		mpu_angles a;
		GetKalmanAngles(a);
		out = a;
	}
	
	nlohmann::json MPU6050::GetKalmanAnglesJSON() 
	{
		nlohmann::json j;
		GetKalmanAnglesJSON(j);
		return j;
	}
	

	mpu_angles MPU6050::GetAccelerationAngles() 
	{
		mpu_angles a;
		GetAccelerationAngles(a);
		return a;
	}

	void MPU6050::GetAccelerationAngles(mpu_angles& out) 
	{
		auto acc = GetAcceleration();
		out.beta = atan2(-acc.x, sqrt(powf(acc.y, 2.0) + powf(acc.z, 2.0))) * RAD_TO_DEG;
		out.gamma = atan2(acc.y, acc.z) * RAD_TO_DEG;
		out.unit = MPU_ANGLE;
	}

	void MPU6050::GetAccelerationAnglesJSON(nlohmann::json& out) 
	{
		mpu_angles a;
		GetAccelerationAngles(a);
		out = a;
	}

	nlohmann::json MPU6050::GetAccelerationAnglesJSON() 
	{
		nlohmann::json j;
		GetAccelerationAnglesJSON(j);
		return j;
	}
	
	const mpu_data& MPU6050::CalibrateAcceleration() 
	{
		std::vector<double> x, y, z;
		for(int i = 0; i < OFFSET_RUNS; i++){
			x.push_back(ReadRawAndConvert(ACCEL_XOUT_H, accel_scale_));
			y.push_back(ReadRawAndConvert(ACCEL_YOUT_H, accel_scale_));
			z.push_back(ReadRawAndConvert(ACCEL_ZOUT_H, accel_scale_));
		}
		{
			std::lock_guard<std::mutex> guard(mtx_);
			offset_acc_.x = utils::Maths::mean(x);
			offset_acc_.y = utils::Maths::mean(y);
			offset_acc_.z = utils::Maths::mean(z) - 1;
			offset_acc_.dx = utils::Maths::deviation(x);
			offset_acc_.dy = utils::Maths::deviation(y);
			offset_acc_.dz = utils::Maths::deviation(z);
			offset_acc_.unit = MPU_ACC;
		}

		return offset_acc_;
	}
	
	const mpu_data& MPU6050::GetAccelerationOffset() const
	{
		return offset_acc_;
	}
	
	mpu_data MPU6050::GetAngularVelocity()
	{
		mpu_data g;
		GetAngularVelocity(g);
		return g;
	}
	
	void MPU6050::GetAngularVelocityJSON(nlohmann::json& out) 
	{
		auto data = GetAngularVelocity();
		out = data;
	}
	
	nlohmann::json MPU6050::GetAngularVelocityJSON() 
	{
		nlohmann::json j;
		GetAngularVelocityJSON(j);
		return j;
	}
	
	void MPU6050::GetAngularVelocity(mpu_data& out) 
	{
		out.x = ReadRawAndConvert(GYRO_XOUT_H, gyro_scale_) - offset_gyro_.x;
		out.y = ReadRawAndConvert(GYRO_YOUT_H, gyro_scale_) - offset_gyro_.y;
		out.z = ReadRawAndConvert(GYRO_ZOUT_H, gyro_scale_) - offset_gyro_.z;
		out.unit = MPU_VEL;
	}
	
	const mpu_data& MPU6050::CalibrateGyro() 
	{
		std::vector<double> x, y, z;
		for(int i = 0; i < OFFSET_RUNS; i++){
			x.push_back(ReadRawAndConvert(GYRO_XOUT_H, gyro_scale_));
			y.push_back(ReadRawAndConvert(GYRO_YOUT_H, gyro_scale_));
			z.push_back(ReadRawAndConvert(GYRO_ZOUT_H, gyro_scale_));
		}
		{
			std::lock_guard<std::mutex> guard(mtx_);
			offset_gyro_.x = utils::Maths::mean(x);
			offset_gyro_.y = utils::Maths::mean(y);
			offset_gyro_.z = utils::Maths::mean(z);
			offset_gyro_.dx = utils::Maths::deviation(x);
			offset_gyro_.dy = utils::Maths::deviation(y);
			offset_gyro_.dz = utils::Maths::deviation(z);
			offset_gyro_.unit = MPU_VEL;
		}
		
		return offset_gyro_;
	}
	
	const mpu_data& MPU6050::GetAngularVelocityOffset() const
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
		json["offsets"]["gyro"] = offset_gyro_;
		json["offsets"]["acceleration"] = offset_acc_;
	}



	void to_json(nlohmann::json& j, const mpu_data& d) {
        j = nlohmann::json{{"x", d.x}, {"y", d.y}, {"z", d.z}, {"dx", d.dx}, {"dy", d.dy}, {"dz", d.dz}, {"unit", d.unit}};
    }

    void from_json(const nlohmann::json& j, mpu_data& d) {
        j.at("x").get_to(d.x);
        j.at("y").get_to(d.y);
		j.at("z").get_to(d.z);
		j.at("dx").get_to(d.dx);
        j.at("dy").get_to(d.dy);
		j.at("dz").get_to(d.dz);
		j.at("unit").get_to(d.unit);
    }
	
	void to_json(nlohmann::json &j, const mpu_angles &d) 
	{
		
	}
	
	void from_json(const nlohmann::json &j, mpu_angles &d) 
	{
		
	}
}