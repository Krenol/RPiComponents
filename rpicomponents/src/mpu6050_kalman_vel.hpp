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

    class MPU6050_Kalman_Vel : public utils::Kalman {
    private:
        mpu_kalman_vel_conf conf_;
    protected:
        void updateA() {
            A_ << 1, 0, 0, 0, 0, 0, 
                0, 1, 0, 0, 0, 0,
                0, 0, 1, 0, 0, 0,
                0, 0, 0, 1, 0, 0,
                0, 0, 0, 0, 1, 0,
                0, 0, 0, 0, 0, 1;
        }

        void updateQ() {
            Q_ << conf_.q11, 0, 0, 0, 0, 0, 
                0, conf_.q22, 0, 0, 0, 0,
                0, 0, conf_.q33, 0, 0, 0,
                0, 0, 0, conf_.q44, 0, 0,
                0, 0, 0, 0, conf_.q55, 0,
                0, 0, 0, 0, 0, conf_.q66;
                
        }

    public:
        MPU6050_Kalman_Vel() : MPU6050_Kalman_Vel(mpu_kalman_vel_conf())
        {

        }

        MPU6050_Kalman_Vel(const MPU6050_Kalman_Vel&) : MPU6050_Kalman_Vel() {

        }

        MPU6050_Kalman_Vel(const mpu_kalman_vel_conf& conf) : Kalman((Eigen::MatrixXd(3, 6) << 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0).finished(), Eigen::MatrixXd::Zero(6,6), (Eigen::MatrixXd(3,3) << conf.r, 0, 0, 0, conf.r, 0, 0, 0, conf.r).finished()), conf_{conf}
        {

        }

        MPU6050_Kalman_Vel(const mpu_kalman_vel_conf& conf, const Eigen::VectorXd& x_0) : Kalman((Eigen::MatrixXd(3, 6) << 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0).finished(), Eigen::MatrixXd::Zero(6,6), (Eigen::MatrixXd(3,3) << conf.r, 0, 0, 0, conf.r, 0, 0, 0, conf.r).finished(), x_0), conf_{conf}
        {

        }
    };
}
#endif