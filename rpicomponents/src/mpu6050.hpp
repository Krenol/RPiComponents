#include "component.hpp"
#include <mutex>
#include <nlohmann/json.hpp>
#include "mpu6050_kalman.hpp"


#ifndef RPICOMPONENTS_MPU6050_H
#define RPICOMPONENTS_MPU6050_H

namespace rpicomponents
{
	constexpr const char *COMPONENT_MPU6050 = "mpu6050";
	constexpr const char *MPU_VEL = "°/s", *MPU_ACC = "g", *MPU_ANGLE = "°";
	constexpr const float RAD_TO_DEG = 57.29578;

	enum GYRO_SENSITIVITY
	{
		DPS_250,
		DPS_500,
		DPS_1000,
		DPS_2000 // available gyro scale ranges; see data sheet
	};

	enum ACCEL_SENSITIVITY
	{
		G_2,
		G_4,
		G_8,
		G_16 // available acceleration scale ranges; see data sheet
	};

	static const std::map<GYRO_SENSITIVITY, int> GYRO_SEL_MAP = {
		{DPS_250, 0b00000000},
		{DPS_500, 0b00001000},
		{DPS_1000, 0b00010000},
		{DPS_2000, 0b00011000}};

	static const std::map<GYRO_SENSITIVITY, float> GYRO_SCALE_FACTOR_MAP = {
		{DPS_250, 131.0},
		{DPS_500, 65.5},
		{DPS_1000, 32.8},
		{DPS_2000, 16.4}};

	static const std::map<ACCEL_SENSITIVITY, int> ACCEL_SEL_MAP = {
		{G_2, 0b00000000},
		{G_4, 0b00001000},
		{G_8, 0b00010000},
		{G_16, 0b00011000}};

	static const std::map<ACCEL_SENSITIVITY, float> ACCEL_SCALE_FACTOR_MAP = {
		{G_2, 16384.0},
		{G_4, 8192.0},
		{G_8, 4096.0},
		{G_16, 2048.0}};

	struct mpu_data
	{
		float x, y, z, dx, dy, dz;
		std::string unit;
	};

	struct mpu_angles
	{
		float beta, gamma;
		std::string unit;
	};

	void to_json(nlohmann::json &j, const mpu_data &d);

	void from_json(const nlohmann::json &j, mpu_data &d);

	void to_json(nlohmann::json &j, const mpu_angles &d);

	void from_json(const nlohmann::json &j, mpu_angles &d);


	class MPU6050 : public Component
	{
		// see https://www.electronicwings.com/raspberry-pi/mpu6050-accelerometergyroscope-interfacing-with-raspberry-pi
	private:
		const int PWR_MGMT_1{0x6B}, SMPLRT_DIV{0x19}, CONFIG{0x1A}, GYRO_CONFIG{0x1B}, ACCEL_CONFIG{0x1C}, INT_ENABLE{0x38},
			ACCEL_XOUT_H{0x3B}, ACCEL_YOUT_H{0x3D}, ACCEL_ZOUT_H{0x3F}, GYRO_XOUT_H{0x43}, GYRO_YOUT_H{0x45}, GYRO_ZOUT_H{0x47}, // collection of needed addresses of the MPU according to data sheet
			OFFSET_RUNS = 100;

		const int address_{0x68}, fd_; //std address
		const float gyro_scale_, accel_scale_;
		std::mutex mtx_;
		mpu_data offset_acc_, offset_gyro_;
		MPU6050_Kalman kalman_beta_, kalman_gamma_;

		/*
		Method to init component

		@param accel: Acceleration range of the MPU
		@param gyro: Gyro range of MPU
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
		 
		 @param address: Address of the MPU
         @param accel: Acceleration range of the MPU
		 @param gyro: Gyro range of the MPU
        */
		MPU6050(int address = 0x68, ACCEL_SENSITIVITY accel = G_2, GYRO_SENSITIVITY gyro = DPS_250);

		/*
         Constructor for this component
		 
		 @param address: Address of the MPU
		 @param offset_acc: Previously retrieved acceleration offset of the MPU
		 @param offset_gyro: Previously retrieved gyro offset of the MPU
         @param accel: Acceleration range of the MPU
		 @param gyro: Gyro range of the MPU
        */
		MPU6050(int address, mpu_data offset_acc, mpu_data offset_gyro, ACCEL_SENSITIVITY accel = G_2, GYRO_SENSITIVITY gyro = DPS_250);

		/*
		Method to read acceleration of the MPU at all three axis

		@returns struct containing the acceleration of all three axis
		*/
		mpu_data GetAcceleration();

		/*
		Method to read acceleration of the MPU at all three axis

		@param out: struct containing the acceleration of all three axis
		*/
		void GetAcceleration(mpu_data &out);

		/*
		Method to read acceleration of the MPU at all three axis

		@param out: json containing the acceleration of all three axis
		*/
		void GetAccelerationJSON(nlohmann::json &out);

		/*
		Method to read acceleration of the MPU at all three axis

		@returns json containing the acceleration of all three axis
		*/
		nlohmann::json GetAccelerationJSON();

		/*
		Method to get angles of the MPU at all three axis

		@returns struct containing the Kalman angles at all three axis
		*/
		mpu_angles GetKalmanAngles();

		/*
		Method to get angles of the MPU at all three axis

		@param out: struct containing the Kalman angles at all three axis
		*/
		void GetKalmanAngles(mpu_angles &out);

		/*
		Method to get angles of the MPU at all three axis

		@param out: json containing the Kalman angles at all three axis
		*/
		void GetKalmanAnglesJSON(nlohmann::json &out);

		/*
		Method to get angles of the MPU at all three axis

		@returns json containing the Kalman angles at all three axis
		*/
		nlohmann::json GetKalmanAnglesJSON();

		/*
		Method to read acceleration of the MPU at all three axis

		@returns struct containing the angles based on accelerations of all three axis
		*/
		mpu_angles GetAccelerationAngles();

		/*
		Method to read acceleration of the MPU at all three axis

		@param out: struct containing the angles based on accelerations of all three axis
		*/
		void GetAccelerationAngles(mpu_angles &out);

		/*
		Method to read acceleration of the MPU at all three axis

		@param out: json containing the angles based on accelerations of all three axis
		*/
		void GetAccelerationAnglesJSON(nlohmann::json &out);

		/*
		Method to read acceleration of the MPU at all three axis

		@returns json containing the angles based on accelerations of all three axis
		*/
		nlohmann::json GetAccelerationAnglesJSON();

		/*
		Method to calibrate accelerations. 
		The calibrated values are automatically substracted when retrieving the values via GetAcceleration().
		Note: Keep MPU horizontally and vertically aligned on a flat surface. Process takes <1s
		@returns offset of the accelerations
		*/
		const mpu_data &CalibrateAcceleration();

		/*
		Method to get acceleration offset
		@returns offset of the acceleration
		*/
		const mpu_data &GetAccelerationOffset() const;

		/*
		Method to read angular velocity of the MPU at all three axis

		@returns struct containing the angular velocity of all three axis
		*/
		mpu_data GetAngularVelocity();

		/*
		Method to read angular velocity of the MPU at all three axis

		@returns json containing the angular velocity of all three axis
		*/
		nlohmann::json GetAngularVelocityJSON();

		/*
		Method to read angular velocity of the MPU at all three axis

		@param out: struct containing the angular velocity of all three axis
		*/
		void GetAngularVelocity(mpu_data &out);

		/*
		Method to read angular velocity of the MPU at all three axis

		@param out: json containing the angular velocity of all three axis
		*/
		void GetAngularVelocityJSON(nlohmann::json &out);

		/*
		Method to calibrate gyro. 
		The calibrated values are automatically substracted when retrieving the values via GetAngularVelocity().
		Note: Keep MPU horizontally and vertically aligned on a flat surface. Process takes < 1s
		@returns offset of the gyro
		*/
		const mpu_data &CalibrateGyro();

		/*
		Method to get gyro offset
		@returns offset of the gyro
		*/
		const mpu_data &GetAngularVelocityOffset() const;

		/*
		Method to get all offsets in a JSON
		@returns JSON containing the offsets of this MPU
		*/
		nlohmann::json GetOffsets();

		/*
		Method to get all offsets in a JSON
		@json JSON where both offsets are to be stored
		*/
		void GetOffsets(nlohmann::json &json);
	};
} // namespace rpicomponents

#endif // RPICOMPONENTS_MPU6050_H
