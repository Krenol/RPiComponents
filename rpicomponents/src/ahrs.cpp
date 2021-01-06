#include "ahrs.hpp"
#include <cmath>

namespace rpicomponents
{
    float Ahrs::invSqrt(float x) 
    {
        float halfx = 0.5f * x;
        float y = x;
        long i = *(long*)&y;
        i = 0x5f3759df - (i>>1);
        y = *(float*)&i;
        y = y * (1.5f - (halfx * y * y));
        return y;
    }
    
    float Ahrs::getDt() 
    {
        float dt = 0;
        auto now = std::chrono::steady_clock::now();
        if(first_call_){
            first_call_ = false;
        } else {
            dt = std::chrono::duration_cast<std::chrono::microseconds>(now - last_call_).count();
        }
        last_call_ = now;
        return dt * 1e-6; //convert to seconds
    }

    Ahrs::Ahrs(float beta) : beta_{beta}
    {
        
    }

    void Ahrs::update(float gx, float gy, float gz, float ax, float ay, float az) 
    {
        float recipNorm, sampleFreq;
        float s0, s1, s2, s3;
        float qDot1, qDot2, qDot3, qDot4;
        float _2q0, _2q1, _2q2, _2q3, _4q0, _4q1, _4q2 ,_8q1, _8q2, q0q0, q1q1, q2q2, q3q3;
        std::lock_guard<std::mutex> guard(mtx_);
        // Rate of change of quaternion from gyroscope
        sampleFreq = getDt();
        qDot1 = 0.5f * (-qx_ * gx - qy_ * gy - qz_ * gz);
        qDot2 = 0.5f * (qw_ * gx + qy_ * gz - qz_ * gy);
        qDot3 = 0.5f * (qw_ * gy - qx_ * gz + qz_ * gx);
        qDot4 = 0.5f * (qw_ * gz + qx_ * gy - qy_ * gx);

        // Compute feedback only if accelerometer measurement valid (avoids NaN in accelerometer normalisation)
        if(!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f))) {

            // Normalise accelerometer measurement
            recipNorm = invSqrt(ax * ax + ay * ay + az * az);
            ax *= recipNorm;
            ay *= recipNorm;
            az *= recipNorm;   

            // Auxiliary variables to avoid repeated arithmetic
            _2q0 = 2.0f * qw_;
            _2q1 = 2.0f * qx_;
            _2q2 = 2.0f * qy_;
            _2q3 = 2.0f * qz_;
            _4q0 = 4.0f * qw_;
            _4q1 = 4.0f * qx_;
            _4q2 = 4.0f * qy_;
            _8q1 = 8.0f * qx_;
            _8q2 = 8.0f * qy_;
            q0q0 = qw_ * qw_;
            q1q1 = qx_ * qx_;
            q2q2 = qy_ * qy_;
            q3q3 = qz_ * qz_;

            // Gradient decent algorithm corrective step
            s0 = _4q0 * q2q2 + _2q2 * ax + _4q0 * q1q1 - _2q1 * ay;
            s1 = _4q1 * q3q3 - _2q3 * ax + 4.0f * q0q0 * qx_ - _2q0 * ay - _4q1 + _8q1 * q1q1 + _8q1 * q2q2 + _4q1 * az;
            s2 = 4.0f * q0q0 * qy_ + _2q0 * ax + _4q2 * q3q3 - _2q3 * ay - _4q2 + _8q2 * q1q1 + _8q2 * q2q2 + _4q2 * az;
            s3 = 4.0f * q1q1 * qz_ - _2q1 * ax + 4.0f * q2q2 * qz_ - _2q2 * ay;
            recipNorm = invSqrt(s0 * s0 + s1 * s1 + s2 * s2 + s3 * s3); // normalise step magnitude
            s0 *= recipNorm;
            s1 *= recipNorm;
            s2 *= recipNorm;
            s3 *= recipNorm;

            // Apply feedback step
            qDot1 -= beta_ * s0;
            qDot2 -= beta_ * s1;
            qDot3 -= beta_ * s2;
            qDot4 -= beta_ * s3;
        }

        // Integrate rate of change of quaternion to yield quaternion
        qw_ += qDot1 * sampleFreq;
        qx_ += qDot2 * sampleFreq;
        qy_ += qDot3 * sampleFreq;
        qz_ += qDot4 * sampleFreq;

        // Normalise quaternion
        recipNorm = invSqrt(qw_ * qw_ + qx_ * qx_ + qy_ * qy_ + qz_ * qz_);
        qw_ *= recipNorm;
        qx_ *= recipNorm;
        qy_ *= recipNorm;
        qz_ *= recipNorm;
    }
    
    void Ahrs::getQuaternions(Quaternions &q) 
    {
        std::lock_guard<std::mutex> guard(mtx_);
        q = Quaternions(qx_, qy_, qz_, qw_);
    }
    
    void Ahrs::getEulerAngles(EulerAngles &angles) 
    {
        std::lock_guard<std::mutex> guard(mtx_);
        // roll (x-axis rotation)
        double sinr_cosp = 2 * (qw_ * qx_ + qy_ * qz_);
        double cosr_cosp = 1 - 2 * (qx_ * qx_ + qy_ * qy_);
        angles.roll = atan2(sinr_cosp, cosr_cosp);

        // pitch (y-axis rotation)
        double sinp = 2 * (qw_ * qy_ - qz_ * qx_);
        if (abs(sinp) >= 1)
            angles.pitch = copysign(M_PI / 2, sinp); // use 90 degrees if out of range
        else
            angles.pitch = asin(sinp);

        // yaw (z-axis rotation)
        double siny_cosp = 2 * (qw_ * qz_ + qx_ * qy_);
        double cosy_cosp = 1 - 2 * (qy_ * qy_ + qz_ * qz_);
        angles.yaw = atan2(siny_cosp, cosy_cosp);
    }
}