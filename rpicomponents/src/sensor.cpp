#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include "helper_3dmath.h"
#include "inv_mpu_lib/inv_mpu.h"
#include "inv_mpu_lib/inv_mpu_dmp_motion_driver.h"
#include "sensor.hpp"

#define wrap_180(x) (x < -180 ? x + 360 : (x > 180 ? x - 360 : x))
#define delay_ms(a) usleep(a * 1000)

namespace rpicomponents
{

	MPU6::MPU6(int address, ACCEL_SENSITIVITY accel, GYRO_SENSITIVITY gyro, uint8_t readRate) : Component(COMPONENT_MPU6)
	{
		open(readRate, accel, gyro);
	}

	MPU6::~MPU6()
	{
		close();
	}

	int MPU6::open(uint8_t rate, uint8_t accel, int32_t gyro)
	{
		float lastval[3];
		int r;
		int16_t a[3]; 
        int16_t g[3]; 
        int32_t _q[4];
		dmpReady = 1;
		initialized = 0;
		uint8_t fifoCount;      // count of all bytes currently in FIFO

		for (int i = 0; i < DIM; i++)
		{
			lastval[i] = 10;
		}

		// initialize device
		printf("Initializing MPU...\n");
		if (mpu_init(NULL) != 0)
		{
			throw std::runtime_error("MPU init failed!\n");
		}
		printf("Setting MPU sensors...\n");
		if (mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL) != 0)
		{
			throw std::runtime_error("Failed to set sensors!\n");
		}
		printf("Setting GYRO sensitivity...\n");
		if (mpu_set_gyro_fsr(gyro) != 0)
		{
			throw std::runtime_error("Failed to set gyro sensitivity!\n");
		}
		printf("Setting ACCEL sensitivity...\n");
		if (mpu_set_accel_fsr(accel) != 0)
		{
			throw std::runtime_error("Failed to set accel sensitivity!\n");
		}
		// verify connection
		printf("Powering up MPU...\n");
		mpu_get_power_state(&devStatus);
		printf(devStatus ? "MPU6 connection successful\n" : "MPU6 connection failed %u\n", devStatus);

		//fifo config
		printf("Setting MPU fifo...\n");
		if (mpu_configure_fifo(INV_XYZ_GYRO | INV_XYZ_ACCEL) != 0)
		{
			throw std::runtime_error("Failed to initialize MPU fifo!\n");
		}

		// load and configure the DMP
		printf("Loading DMP firmware...\n");
		if (dmp_load_motion_driver_firmware() != 0)
		{
			throw std::runtime_error("Failed to enable DMP!\n");
		}

		printf("Activating DMP...\n");
		if (mpu_set_dmp_state(1) != 0)
		{
			throw std::runtime_error("Failed to enable DMP!\n");
		}

		//dmp_set_orientation()
		//if (dmp_enable_feature(DMP_FEATURE_LP_QUAT|DMP_FEATURE_SEND_RAW_GYRO)!=0) {
		printf("Configuring DMP...\n");
		if (dmp_enable_feature(DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_SEND_RAW_ACCEL | DMP_FEATURE_SEND_CAL_GYRO | DMP_FEATURE_GYRO_CAL) != 0)
		{
			throw std::runtime_error("Failed to enable DMP features!\n");
		}

		printf("Setting DMP fifo rate...\n");
		if (dmp_set_fifo_rate(rate) != 0)
		{
			throw std::runtime_error("Failed to set dmp fifo rate!\n");
		}
		printf("Resetting fifo queue...\n");
		if (mpu_reset_fifo() != 0)
		{
			throw std::runtime_error("Failed to reset fifo!\n");
		}

		printf("Checking... ");
		do
		{
			delay_ms(1000 / rate); //dmp will habve 4 (5-1) packets based on the fifo_rate
			r = dmp_read_fifo(g, a, _q, &sensors, &fifoCount);
		} while (r != 0 || fifoCount < 5); //packtets!!!
		printf("Done.\n");

		initialized = 1;
		return 0;
	}

	int MPU6::getValues(mpu_values &values)
	{
		float ypr[3];
        Quaternion q;
        float temp;
        float gyro[3];
        float accel[3];
		VectorFloat gravity; 
		int32_t t;
		int16_t a[3]; 
        int16_t g[3]; 
        int32_t _q[4];
		uint8_t fifoCount;      // count of all bytes currently in FIFO

		if (!dmpReady)
		{
			printf("Error: DMP not ready!!\n");
			return -1;
		}

		while (dmp_read_fifo(g, a, _q, &sensors, &fifoCount) != 0)
			; //gyro and accel can be null because of being disabled in the efeatures
		q = _q;
		GetGravity(&gravity, &q);
		GetYawPitchRoll(ypr, &q, &gravity);

		mpu_get_temperature(&t);
		temp = (float)t / 65536L;


		//scaling for degrees output
		for (int i = 0; i < DIM; i++)
		{
			ypr[i] *= 180 / M_PI;
		}

		//unwrap yaw when it reaches 180
		ypr[0] = wrap_180(ypr[0]);

		//change sign of Pitch, MPU is attached upside down
		ypr[1] *= -1.0;

		//0=gyroX, 1=gyroY, 2=gyroZ
		//swapped to match Yaw,Pitch,Roll
		//Scaled from deg/s to get tr/s
		for (int i = 0; i < DIM; i++)
		{
			gyro[i] = (float)(g[DIM - i - 1]) / 131.0 / 360.0;
			accel[i] = (float)(a[DIM - i - 1]);
		}
		values.temp = temp;
		values.yaw = ypr[0];
		values.pitch = ypr[1];
		values.roll = ypr[2];
		values.ax = accel[0];
		values.ay = accel[1];
		values.az = accel[2];
		values.gx = gyro[0];
		values.gy = gyro[1];
		values.gz = gyro[2];
		return 0;
	}

	int MPU6::close()
	{
		return 0;
	}

	uint8_t MPU6::GetGravity(VectorFloat *v, Quaternion *q)
	{
		v->x = 2 * (q->x * q->z - q->w * q->y);
		v->y = 2 * (q->w * q->x + q->y * q->z);
		v->z = q->w * q->w - q->x * q->x - q->y * q->y + q->z * q->z;
		return 0;
	}

	uint8_t MPU6::GetYawPitchRoll(float *data, Quaternion *q, VectorFloat *gravity)
	{
		// yaw: (about Z axis)
		data[0] = atan2(2 * q->x * q->y - 2 * q->w * q->z, 2 * q->w * q->w + 2 * q->x * q->x - 1);
		// pitch: (nose up/down, about Y axis)
		data[1] = atan(gravity->x / sqrt(gravity->y * gravity->y + gravity->z * gravity->z));
		// roll: (tilt left/right, about X axis)
		data[2] = atan(gravity->y / sqrt(gravity->x * gravity->x + gravity->z * gravity->z));
		return 0;
	}

}