#include "utils/utils.hpp"

#ifndef RPICOMPONENTS_MPU6050_KALMAN_ANGLES_H
#define RPICOMPONENTS_MPU6050_KALMAN_ANGLES_H
namespace rpicomponents
{
    struct mpu_kalman_angles_conf {
        double c1, c2, r, q11, q12, q21, q22;

        mpu_kalman_angles_conf() {
            this->c1 = 1;
            this->c2 = 0;
            this->r = 0.03;
            this->q11 = 0.001;
            this->q12 = 0;
            this->q21 = 0;
            this->q22 = 0.003;
        }

        mpu_kalman_angles_conf(double c1, double c2, double r, double q11, double q12, double q21, double q22){
            this->c1 = c1;
            this->c2 = c2;
            this->r = r;
            this->q11 = q11;
            this->q12 = q12;
            this->q21 = q21;
            this->q22 = q22;
        }

        mpu_kalman_angles_conf(const mpu_kalman_angles_conf& conf) {
            c1 = conf.c1;
            c2 = conf.c2;
            r = conf.r;
            q11 = conf.q11;
            q12 = conf.q12;
            q21 = conf.q21;
            q22 = conf.q22;
        }
    };

    template <typename T = std::chrono::milliseconds>
    class MPU6050_Kalman_Angles : public utils::Kalman<T> {
    private:
        mpu_kalman_angles_conf conf_;
    protected:
        void updateA() {
            auto dt = utils::Kalman<T>::getDt();
            utils::Kalman<T>::A_ << 1, -dt, 0, 0, 
                0, 1, 0, 0, 
                0, 0, 1, -dt,
                0, 0, 0, 1;
        }

        void updateB() {
            auto dt = utils::Kalman<T>::getDt();
            utils::Kalman<T>::B_ << dt, 0,
                0, 0,
                0, dt, 
                0, 0;
        }

        void updateQ() {
            auto dt = utils::Kalman<T>::getDt();
            utils::Kalman<T>::Q_ << conf_.q11 * dt, conf_.q12, 0, 0, 
                conf_.q21, conf_.q22 * dt, 0, 0,
                0, 0, conf_.q11 * dt, conf_.q12,
                0, 0, conf_.q21, conf_.q22 * dt;
        }

    public:
        MPU6050_Kalman_Angles() : MPU6050_Kalman_Angles(mpu_kalman_angles_conf())
        {

        }

        MPU6050_Kalman_Angles(const MPU6050_Kalman_Angles&) : MPU6050_Kalman_Angles() {

        }

        MPU6050_Kalman_Angles(const mpu_kalman_angles_conf& conf) : utils::Kalman<T>((Eigen::MatrixXd(2,4) << conf.c1, conf.c2, 0, 0, 0, 0 , conf.c1, conf.c2).finished(), Eigen::MatrixXd::Zero(4,4), (Eigen::MatrixXd(2,2) << conf.r, 0, 0, conf.r).finished()), conf_{conf}
        {

        }

        MPU6050_Kalman_Angles(const mpu_kalman_angles_conf& conf, const Eigen::VectorXd& x_0) : utils::Kalman<T>((Eigen::MatrixXd(2,4) << conf.c1, conf.c2, 0, 0, 0, 0 , conf.c1, conf.c2).finished(), Eigen::MatrixXd::Zero(4,4), (Eigen::MatrixXd(2,2) << conf.r, 0, 0, conf.r).finished(), x_0), conf_{conf}
        {

        }
    };
}
#endif