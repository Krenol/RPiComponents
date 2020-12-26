#include "mpu6050.hpp"
#include <cmath>
#include <pigpio.h>
#include <unistd.h>


namespace rpicomponents
{
	const int MPU6050::PWR_MGMT_1 = 0x6B, MPU6050::SMPLRT_DIV = 0x19, MPU6050::CONFIG = 0x1A, MPU6050::GYRO_CONFIG = 0x1B, MPU6050::ACCEL_CONFIG = 0x1C, 
			MPU6050::INT_ENABLE = 0x38, MPU6050::ACCEL_XOUT_H = 0x3B, MPU6050::ACCEL_YOUT_H = 0x3D, MPU6050::ACCEL_ZOUT_H = 0x3F, MPU6050::GYRO_XOUT_H = 0x43, 
			MPU6050::GYRO_YOUT_H = 0x45, MPU6050::GYRO_ZOUT_H = 0x47, MPU6050::CALIBRATION_RUNS = 1000, MPU6050::CALIBRATION_SLEEP = 1000;
			
	void MPU6050::Init(ACCEL_SENSITIVITY accel, GYRO_SENSITIVITY gyro)
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
		SetKalmanConfig(mpu_kalman_angles_conf());
		SetKalmanConfig(mpu_kalman_vel_conf());
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
	
	
	mpu_angles MPU6050::GetKalmanAngles() 
	{
		mpu_angles a;
		GetKalmanAngles(a);
		return a;
	}
	
	void MPU6050::GetKalmanAngles(mpu_angles& out, bool use_kalman_vel) 
	{
		Eigen::VectorXd u(2), z(2), x;
		mpu_data vel;
		GetAccelerationAngles(out);
		if(use_kalman_vel){
			GetKalmanVelocity(vel);
		} else {
			GetAngularVelocity(vel);
		}
		z << out.roll_angle, out.pitch_angle;
		u << vel.x, vel.y;
		kalman_angles_->predict(x, z, u);
		out.roll_angle = x[0];
		out.pitch_angle = x[2];		
		out.unit = MPU_ANGLE;
	}
	
	void MPU6050::GetKalmanVelocity(mpu_data& out) 
	{
		Eigen::VectorXd z(3), x;
		GetAngularVelocity(out);
		z << out.x, out.y, out.z;
		kalman_vel_->predict(x, z);
		out.x = x[0];
		out.y = x[2];
		out.z = x[4];
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
		out.roll_angle = atan2(-acc.x, sqrt(powf(acc.y, 2.0) + powf(acc.z, 2.0))) * RAD_TO_DEG;
		out.pitch_angle = atan2(acc.y, acc.z) * RAD_TO_DEG;
		out.unit = MPU_ANGLE;
	}
	
	const mpu_data& MPU6050::CalibrateAcceleration(int calib_runs) 
	{
		std::vector<double> x, y, z;
		do{
			x.push_back(ReadRawAndConvert(ACCEL_XOUT_H, accel_scale_));
			y.push_back(ReadRawAndConvert(ACCEL_YOUT_H, accel_scale_));
			z.push_back(ReadRawAndConvert(ACCEL_ZOUT_H, accel_scale_));
			usleep(CALIBRATION_SLEEP);
			--calib_runs;
		} while(calib_runs > 0);
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
	

	void MPU6050::GetAngularVelocity(mpu_data& out) 
	{
		out.x = ReadRawAndConvert(GYRO_XOUT_H, gyro_scale_) - offset_gyro_.x;
		out.y = ReadRawAndConvert(GYRO_YOUT_H, gyro_scale_) - offset_gyro_.y;
		out.z = ReadRawAndConvert(GYRO_ZOUT_H, gyro_scale_) - offset_gyro_.z;
		out.unit = MPU_VEL;
	}
	
	const mpu_data& MPU6050::CalibrateGyro(int calib_runs) 
	{
		std::vector<double> x, y, z;
		do {
			x.push_back(ReadRawAndConvert(GYRO_XOUT_H, gyro_scale_));
			y.push_back(ReadRawAndConvert(GYRO_YOUT_H, gyro_scale_));
			z.push_back(ReadRawAndConvert(GYRO_ZOUT_H, gyro_scale_));
			usleep(CALIBRATION_SLEEP);
			--calib_runs;
		} while(calib_runs > 0);

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
	
	void MPU6050::CalibrateFromJson(const nlohmann::json& j) 
	{
		offset_gyro_ = j["offsets"]["gyro"];
		offset_acc_ = j["offsets"]["acceleration"];
	}
	
	void MPU6050::SetKalmanConfig(const mpu_kalman_angles_conf& conf) 
	{
		mpu_angles a;
        GetAccelerationAngles(a);
        Eigen::VectorXd x_0(4);
        x_0 << a.roll_angle, 0, a.pitch_angle, 0;
		kalman_angles_ = std::make_unique<MPU6050_Kalman_Angles>(conf, x_0);
	}
	
	void MPU6050::SetKalmanConfig(const mpu_kalman_vel_conf& conf) 
	{
		mpu_data d;
		GetAngularVelocity(d);
		Eigen::VectorXd x_0(6);
        x_0 << d.x, 0, d.y, 0, d.z, 0;
		kalman_vel_ = std::make_unique<MPU6050_Kalman_Vel>(conf, x_0);
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