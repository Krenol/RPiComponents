#include <mutex>
#include <chrono>

#ifndef RPICOMPONENTS_AHRS_H
#define RPICOMPONENTS_AHRS_H

namespace rpicomponents
{
    struct Quaternions
    {
        float qx = 0, qy = 0, qz = 0, qw = 1;

        Quaternions(float qx = 0, float qy = 0, float qz = 0, float qw = 1)
        {
            this->qx = qx;
            this->qy = qy;
            this->qz = qz;
            this->qw = qw;
        }

        Quaternions(const Quaternions &q)
        {
            this->qx = q.qx;
            this->qy = q.qy;
            this->qz = q.qz;
            this->qw = q.qw;
        }
    };

    struct EulerAngles
    {
        float roll, pitch, yaw;

        EulerAngles(float roll = 0, float pitch = 0, double yaw = 0)
        {
            this->roll = roll;
            this->pitch = pitch;
            this->yaw = yaw;
        }

        EulerAngles(const EulerAngles &q)
        {
            this->roll = q.roll;
            this->pitch = q.pitch;
            this->yaw = q.yaw;
        }

    };

    // https://x-io.co.uk/open-source-imu-and-ahrs-algorithms/
    class Ahrs
    {
    private:
        float qx_{0.0f}, qy_{0.0f}, qz_{0.0f}, qw_{1.0f};
        const float beta_{0.1f};
        bool first_call_{false};
        std::mutex mtx_;
        std::chrono::steady_clock::time_point last_call_;

        float invSqrt(float x);

        float getDt();
    public:
        /**
         * Constructor for AHRS
         * @param beta kp gain
         */
        Ahrs(float beta = 0.1f);

        void update(float gx, float gy, float gz, float ax, float ay, float az);

        void getQuaternions(Quaternions &q);

        void getEulerAngles(EulerAngles &angles);
    };
} // namespace rpicomponents

#endif // RPICOMPONENTS_AHRS_H
