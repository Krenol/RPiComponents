#include "utils/utils.hpp"
#include <iostream>

#ifndef RPICOMPONENTS_MPU6050_KALMAN_H
#define RPICOMPONENTS_MPU6050_KALMAN_H

class MPU6050_Kalman : public utils::Kalman {
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
        Q_ << 0.001 * dt, 0, 0, 0.003 * dt;
    }

public:
    MPU6050_Kalman() : Kalman((Eigen::MatrixXd(1,2) << 1, 0).finished(), Eigen::MatrixXd::Zero(2,2), (Eigen::MatrixXd(1,1) << 0.03).finished())
    {

    }
};

#endif