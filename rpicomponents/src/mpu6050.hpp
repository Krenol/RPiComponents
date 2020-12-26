#include "component.hpp"
#include <mutex>
#include <nlohmann/json.hpp>
#include "mpu6050_kalman_angles.hpp"
#include "mpu6050_kalman_vel.hpp"

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
		float roll_angle, pitch_angle;
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
		static const int PWR_MGMT_1, SMPLRT_DIV, CONFIG, GYRO_CONFIG, ACCEL_CONFIG, INT_ENABLE,
			ACCEL_XOUT_H, ACCEL_YOUT_H, ACCEL_ZOUT_H, GYRO_XOUT_H, GYRO_YOUT_H, GYRO_ZOUT_H, // collection of needed addresses of the MPU according to data sheet
			CALIBRATION_RUNS, CALIBRATION_SLEEP;

		const int address_{0x68}, fd_; //std address
		const float gyro_scale_, accel_scale_;
		std::mutex mtx_;
		mpu_data offset_acc_, offset_gyro_;
		std::unique_ptr<MPU6050_Kalman_Angles> kalman_angles_;
		std::unique_ptr<MPU6050_Kalman_Vel> kalman_vel_;

		/*
		Method to init component

		@param accel: Acceleration range of the MPU
		@param gyro: Gyro range of MPU
		*/
		void Init(ACCEL_SENSITIVITY accel, GYRO_SENSITIVITY gyro);

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

		/**
		 * Destructor
		 */
		~MPU6050();

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
		Method to get angles of the MPU at all three axis

		@returns struct containing the Kalman angles at all three axis
		*/
		mpu_angles GetKalmanAngles();

		/*
		Method to get the velocity of the MPU at all three axis
		@param out: struct containing the Kalman velocity at all three axis
		@returns struct containing the Kalman velocity at all three axis
		*/
		void GetKalmanVelocity(mpu_data& out);

		/*
		Method to get angles of the MPU at all three axis

		@param out: struct containing the Kalman angles at all three axis
		@param use_kalman_vel: Flag to say if we are to use kalman predicted vel or direct sensor signals
		*/
		void GetKalmanAngles(mpu_angles &out, bool use_kalman_vel=true);


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
		Method to calibrate accelerations. 
		The calibrated values are automatically substracted when retrieving the values via GetAcceleration().
		Note: Keep MPU horizontally and vertically aligned on a flat surface. 
		@param calib_runs: The amount of calibration measurements done for the calibration calculation
		@returns offset of the accelerations
		*/
		const mpu_data &CalibrateAcceleration(int calib_runs = CALIBRATION_RUNS);

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

		@param out: struct containing the angular velocity of all three axis
		*/
		void GetAngularVelocity(mpu_data &out);

		/*
		Method to calibrate gyro. 
		The calibrated values are automatically substracted when retrieving the values via GetAngularVelocity().
		Note: Keep MPU horizontally and vertically aligned on a flat surface. 
		@param calib_runs: The amount of calibration measurements done for the calibration calculation
		@returns offset of the gyro
		*/
		const mpu_data &CalibrateGyro(int calib_runs = CALIBRATION_RUNS);

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

		/*
		Method to get all offsets in a JSON
		@json JSON where both offsets are to be stored
		*/
		void CalibrateFromJson(const nlohmann::json& j);

		/**
		 * Method to set the config values of the kalman angles filters
		 * @param conf the config struct
		 */
		void SetKalmanConfig(const mpu_kalman_angles_conf& conf);

		/**
		 * Method to set the config values of the kalman velocity filters
		 * @param conf the config struct
		 */
		void SetKalmanConfig(const mpu_kalman_vel_conf& conf);
	};
} // namespace rpicomponents

#endif // RPICOMPONENTS_MPU6050_H
