#include "utils/utils.hpp"


#ifndef RPICOMPONENTS_BMP180_KALMAN_H
#define RPICOMPONENTS_BMP180_KALMAN_H


namespace rpicomponents
{
    struct bmp_kalman_conf {
        double c1, c2, r, q11, q12, q21, q22;
        int res;

        void res_map(){
            switch (res)
            {
            case 1:
                r = 0.05;
                break;
            case 2:
                r = 0.04;
                break;
            case 3:
                r = 0.03;
                break;
            default:
                r = 0.06;
                break;
            }
        }

        bmp_kalman_conf() {
            this->c1 = 1;
            this->c2 = 0;
            this->q11 = 0.001;
            this->q12 = 0;
            this->q21 = 0;
            this->q22 = 0.001;
            res = 1;
            res_map();
        }

        bmp_kalman_conf(double c1, double c2, double q11, double q12, double q21, double q22, int res){
            this->c1 = c1;
            this->c2 = c2;
            this->q11 = q11;
            this->q12 = q12;
            this->q21 = q21;
            this->q22 = q22;
            this->res = res;
            res_map();
        }

        bmp_kalman_conf(const bmp_kalman_conf& conf) {
            c1 = conf.c1;
            c2 = conf.c2;
            q11 = conf.q11;
            q12 = conf.q12;
            q21 = conf.q21;
            q22 = conf.q22;
            res = conf.res;
            res_map();
        }
    };

    template <typename T = std::chrono::milliseconds>
    class Bmp180_Kalman : public utils::Kalman<T> {  
    protected:
        bmp_kalman_conf conf_;


    public:
        Bmp180_Kalman() : Bmp180_Kalman(bmp_kalman_conf())
        {

        }

        Bmp180_Kalman(const Bmp180_Kalman& b) : Bmp180_Kalman(b.conf_) {

        }


        Bmp180_Kalman(const bmp_kalman_conf& conf) : utils::Kalman<T>((Eigen::MatrixXd(2,2) << 1, 0, 0, 1).finished(), Eigen::MatrixXd::Zero(2,1),(Eigen::MatrixXd(1,2) << conf.c1, conf.c2).finished(), Eigen::MatrixXd::Zero(2,2), (Eigen::MatrixXd(2,2) << conf_.q11, conf_.q12, conf_.q21, conf_.q22).finished(),(Eigen::MatrixXd(1,1) << conf.r).finished()), conf_{conf}
        {

        }

        Bmp180_Kalman(const bmp_kalman_conf& conf, const Eigen::VectorXd& x_0) : utils::Kalman<T>((Eigen::MatrixXd(2,2) << 1, 0, 0, 1).finished(), Eigen::MatrixXd::Zero(2,1),(Eigen::MatrixXd(1,2) << conf.c1, conf.c2).finished(), Eigen::MatrixXd::Zero(2,2), (Eigen::MatrixXd(2,2) << conf_.q11, conf_.q12, conf_.q21, conf_.q22).finished(),(Eigen::MatrixXd(1,1) << conf.r).finished(), x_0), conf_{conf}
        {

        }
    };
}
#endif