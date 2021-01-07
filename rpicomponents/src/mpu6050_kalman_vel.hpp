#include "utils/utils.hpp"

#ifndef RPICOMPONENTS_MPU6050_KALMAN_VEL_H
#define RPICOMPONENTS_MPU6050_KALMAN_VEL_H

namespace rpicomponents
{
    
    struct mpu_kalman_vel_conf {
        double r, q11, q22, q33, q44, q55, q66;

        mpu_kalman_vel_conf() {
            this->r = 0.03;
            this->q11 = 0.02;
            this->q22 = 0.02;
            this->q33 = 0.02;
            this->q44 = 0.02;
            this->q55 = 0.02;
            this->q66 = 0.02;
        }

        mpu_kalman_vel_conf(double r, double q11, double q22, double q33, double q44, double q55, double q66){
            this->r = r;
            this->q11 = q11;
            this->q22 = q22;
            this->q33 = q33;
            this->q44 = q44;
            this->q55 = q55;
            this->q66 = q66;
        }

        mpu_kalman_vel_conf(const mpu_kalman_vel_conf& conf) {
            r = conf.r;
            q11 = conf.q11;
            q22 = conf.q22;
            q33 = conf.q33;
            q44 = conf.q44;
            q55 = conf.q55;
            q66 = conf.q66;
        }
    };

    template <typename T = std::chrono::milliseconds>
    class MPU6050_Kalman_Vel : public utils::Kalman<T> {
    private:
        Eigen::MatrixXd getA() {
            Eigen::MatrixXd A(6, 6);
            A.setIdentity();
            return A;
        }

        Eigen::MatrixXd getQ(const mpu_kalman_vel_conf& conf) {
            Eigen::MatrixXd q(6,6);
            q << conf.q11, 0, 0, 0, 0, 0, 
                0, conf.q22, 0, 0, 0, 0,
                0, 0, conf.q33, 0, 0, 0,
                0, 0, 0, conf.q44, 0, 0,
                0, 0, 0, 0, conf.q55, 0,
                0, 0, 0, 0, 0, conf.q66;
            return q;   
        }

        Eigen::MatrixXd getC() {
            Eigen::MatrixXd c(3,6);
            c << 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0;
            return c;   
        }

        Eigen::MatrixXd getR(const mpu_kalman_vel_conf& conf) {
            Eigen::MatrixXd r(3,3);
            r << conf.r, 0, 0, 0, conf.r, 0, 0, 0, conf.r;
            return r;   
        }

    protected:
        mpu_kalman_vel_conf conf_;

    public:
        MPU6050_Kalman_Vel() : MPU6050_Kalman_Vel(mpu_kalman_vel_conf())
        {

        }

        MPU6050_Kalman_Vel(const MPU6050_Kalman_Vel& v) : MPU6050_Kalman_Vel(v.conf_) {

        }

        MPU6050_Kalman_Vel(const mpu_kalman_vel_conf& conf) : utils::Kalman<T>(getA(), Eigen::MatrixXd::Zero(3,6), getC(), Eigen::MatrixXd::Zero(6,6), getQ(conf), getR(conf)), conf_{conf}
        {

        }

        MPU6050_Kalman_Vel(const mpu_kalman_vel_conf& conf, const Eigen::VectorXd& x_0) : utils::Kalman<T>(getA(), Eigen::MatrixXd::Zero(3,6), getC(), Eigen::MatrixXd::Zero(6,6), getQ(conf), getR(conf), x_0), conf_{conf}
        {

        }
    };
}
#endif