#include "utils/utils.hpp"
#include <iostream>

#ifndef RPICOMPONENTS_MPU6050_KALMAN_H
#define RPICOMPONENTS_MPU6050_KALMAN_H

struct mpu_kalman_conf {
    double c1, c2, r, q11, q12, q21, q22;

    mpu_kalman_conf() {
        this->c1 = 1;
        this->c2 = 0;
        this->r = 0.03;
        this->q11 = 0.001;
        this->q12 = 0;
        this->q21 = 0;
        this->q22 = 0.003;
    }

    mpu_kalman_conf(double c1, double c2, double r, double q11, double q12, double q21, double q22){
        this->c1 = c1;
        this->c2 = c2;
        this->r = r;
        this->q11 = q11;
        this->q12 = q12;
        this->q21 = q21;
        this->q22 = q22;
    }

    mpu_kalman_conf(const mpu_kalman_conf& conf) {
        c1 = conf.c1;
        c2 = conf.c2;
        q11 = conf.q11;
        q12 = conf.q12;
        q21 = conf.q21;
        q22 = conf.q22;
    }
};

class MPU6050_Kalman : public utils::Kalman {
private:
    mpu_kalman_conf conf_;
protected:
    void updateA() {
        auto dt = getDt();
        A_ << 1, -dt, 0, 1;
    }

    void updateB() {
        auto dt = getDt();
        B_ << dt, 0;
    }

    void updateQ() {
        auto dt = getDt();
        Q_ << conf_.q11 * dt, conf_.q12, conf_.q21, conf_.q22 * dt;
    }

public:
    MPU6050_Kalman() : MPU6050_Kalman(mpu_kalman_conf())
    {

    }

    MPU6050_Kalman(const MPU6050_Kalman&) : MPU6050_Kalman() {

    }

    MPU6050_Kalman(const mpu_kalman_conf& conf) : Kalman((Eigen::MatrixXd(1,2) << conf.c1, conf.c2).finished(), Eigen::MatrixXd::Zero(2,2), (Eigen::MatrixXd(1,1) << conf.r).finished()), conf_{conf}
    {

    }
};

#endif