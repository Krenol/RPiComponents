#include "component.hpp"

#ifndef RPICOMPONENTS_SENSOR_H
#define RPICOMPONENTS_SENSOR_H

namespace rpicomponents
{

    constexpr const char *COMPONENT_MPU6 = "MPU6";
    constexpr const char *MPU_VEL = "°/s", *MPU_ACC = "g", *MPU_ANGLE = "°";
    constexpr const float RAD_TO_DEG = 57.29578;

    enum GYRO_SENSITIVITY
	{
		DPS_250 = 250,
		DPS_500 = 500,
		DPS_1000 = 1000,
		DPS_2000 = 2000 // available gyro scale ranges; see data sheet
	};

	enum ACCEL_SENSITIVITY
	{
		G_2 = 2,
		G_4 = 4,
		G_8 = 8,
		G_16 = 16 // available acceleration scale ranges; see data sheet
	};

    struct mpu_values{
        float yaw, pitch, roll, ax, ay, az, gx, gy, gz, temp;
    };

    class MPU6 : public Component
    {
    private:
        // MPU control/status vars
        uint8_t devStatus; // return status after each device operation
        int initialized = 0;
        int dmpReady = 0;
        int16_t sensors;
        uint8_t DIM = 3;

        
        int open(uint8_t rate, uint8_t accel, int32_t gyro);
        int close();
        uint8_t GetGravity(VectorFloat *v, Quaternion *q);
        uint8_t GetYawPitchRoll(float *data, Quaternion *q, VectorFloat *gravity);
        uint8_t GetGyro(int32_t *data, const uint8_t *packet);
    public:
        /*
            Constructor for this component
            
            @param address: Address of the MPU
            @param accel: Acceleration range of the MPU
		    @param gyro: Gyro range of the MPU
            @param readRate The read rate of the DMP in Hz
        */
        MPU6(int address = 0x68, ACCEL_SENSITIVITY accel = G_2, GYRO_SENSITIVITY gyro = DPS_2000, uint8_t readRate = 20);
        ~MPU6();

        int getValues(mpu_values &values);
    
        
    };

}
#endif
