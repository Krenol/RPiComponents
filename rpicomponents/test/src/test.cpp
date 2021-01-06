#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
//#include "../external/doctest/doctest/doctest.h"

#include "rpicomponents/rpicomponents.hpp"
#include "utils/utils.hpp"

//***TEST CASES***

/*TEST_CASE("Creating button and checking it") {
    rpicomponents::Button btn(pin::PinCreator::CreatePin(1, pin::INPUT_MODE), PI_PUD_UP);
    CHECK(btn.ToString().compare(rpicomponents::COMPONENT_BUTTON) == 0);
    CHECK(btn.ToString().compare(rpicomponents::COMPONENT) == 0);
}

TEST_CASE("Address checker") {
    CHECK(pin::AddressChecker::IsI2CAddress(0x42) == 1);
    CHECK(pin::AddressChecker::IsI2CAddress(0x1) == 0);
}

TEST_CASE("Steppermotor checker") {
    rpicomponents::Steppermotor motor(pin::PinCreator::CreatePin(2, pin::DIGITAL_MODE),
                                      pin::PinCreator::CreatePin(3, pin::DIGITAL_MODE),
                                      pin::PinCreator::CreatePin(4, pin::DIGITAL_MODE),
                                      pin::PinCreator::CreatePin(5, pin::DIGITAL_MODE),
                                      2048);
    CHECK(motor.ToString().compare(rpicomponents::COMPONENT_STEPPERMOTOR) == 0);

    CHECK_NOTHROW(motor.Rotate(2,true, 3));
    CHECK_THROWS_WITH_AS(motor.Rotate(2,true, -2), "stepDelay cannot be lower than 1 ms!", std::invalid_argument);
    CHECK_THROWS_WITH_AS(motor.Rotate(-2,true, 5), "steps cannot be negative!", std::invalid_argument);
} */


#include <thread>
#include <cassert>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <nlohmann/json.hpp>
#include <fstream> 
#include <filesystem>
#include <unistd.h>
#include <map>


using json = nlohmann::json;

typedef std::map<std::string, rpicomponents::Esc> esc_map;

void createEscMap(esc_map &map, const json& esc_json) {
    int pwm_max = esc_json.at("pwm");
    int esc_max = esc_json.at("max");
    int esc_min = esc_json.at("min");
    std::cout << "----\tPulse: " << pwm_max << "\tesc_min: " << esc_min << "\tesc_max: " << esc_max << "\t----" << std::endl;
    auto esc_pins = esc_json.at("pins");
    for(auto esc : esc_pins.items()){
        json val = esc.value();
        
        map.insert(std::pair<std::string,rpicomponents::Esc>(val.at("pos"), rpicomponents::Esc(pin::GPIO_MAP.at(val.at("pin")), esc_min, esc_max)));
    }
}

void escStartup(rpicomponents::Esc& esc, int speed, const std::string& m){
    printf("\n\n-------------\n");
    std::cout << "Calibrating & arming ESC of " << m << " motor\n";
    esc.Calibrate(false);
    printf("let motor turn now with %i...\n", speed);
    esc.SetOutputSpeed(speed);
    usleep(100);
    printf("-------------");
}

void gps() {
    rpicomponents::GpsNeo6MV2 gps;
    rpicomponents::GPSCoordinates c;
    while(1) {
        gps.getCoordinates(c, 10);
        printf("\n\n\n-------------\n longitude=%.5f °\tlatitude=%.5f °\taltitude=%.5f m\n-------------\n\n\n", c.longitude, c.latitude, c.altitude);
        sleep(1);
    }
}

void mpu() {
     rpicomponents::MPU6050<std::chrono::milliseconds> mpu;
     auto offset_a = mpu.CalibrateAcceleration();
     printf("\n\n\n-------------\n Ax=%.3f g\tAy=%.3f g\tAz=%.3f g\tdx=%.3f g\tdy=%.3f g\tdz=%.3f g\n-------------\n\n\n",
         offset_a.x, offset_a.y, offset_a.z, offset_a.dx, offset_a.dy, offset_a.dz);
     auto offset_g = mpu.CalibrateGyro();
     printf("\n\n\n-------------\n Gx=%.3f °/s\tGy=%.3f °/s\tGz=%.3f °/s\tdx=%.3f °/s\tdy=%.3f °/s\tdz=%.3f °/s\n-------------\n\n\n",
         offset_g.x, offset_g.y, offset_g.z, offset_g.dx, offset_g.dy, offset_g.dz);
     rpicomponents::mpu_angles a;
     rpicomponents::mpu_data d;
     while(true) {
         mpu.GetKalmanAngles(a, true);
         mpu.GetKalmanVelocity(d);
         printf("\n\n\n-------------\n roll_angle=%.3f °\tpitch_angle=%.3f °\tAx=%.3f °/s\tAy=%.3f °/s\tAz=%.3f °/s\n-------------\n\n\n", a.roll_angle, a.pitch_angle, d.x, d.y, d.z);
         usleep(500000);
     }
}

void bmp() {
    rpicomponents::Bmp180<std::chrono::milliseconds> bmp;
    rpicomponents::BarometricData d;
    while(1){
        bmp.getBarometricData(d);
        printf("\n\n\n-------------\n temperature=%.3f K\tdensity=%.3f kg/m³\taltitude=%.3f m\tpressure=%ld Pa\n-------------\n\n\n", d.temperature, d.density, d.altitude, d.pressure);
        usleep(500000);
    }
}

void bmp_kal() {
    rpicomponents::Bmp180<std::chrono::milliseconds> bmp;
    rpicomponents::BarometricData d;
    

    while(1){
        auto p = bmp.getPressure();
        auto pk = bmp.getPressureKalman();
        auto h = bmp.getAltitude();
        auto hk = bmp.getAltitudeKalman();
        printf("\n\n\n-------------\naltitude=%.3f m\taltitude_kal=%.3f m\tpressure=%ld Pa\tpressure_kal=%ld Pa\n-------------\n\n\n", h, hk, p, pk);
        usleep(500000);
    }
}

template<typename T>
T ROUND(T number, int decimals)
{
    int fac = pow(10, decimals);
    return round(number * fac) / fac;
}

void ahrs() {
    rpicomponents::MPU6050<std::chrono::milliseconds> mpu;
    rpicomponents::Ahrs ahrs(1);
    rpicomponents::EulerAngles angles;
    rpicomponents::Quaternions q;
    rpicomponents::mpu_data a, g, a1, g1;
    mpu.CalibrateAcceleration(2000);
    mpu.CalibrateGyro(2000);
    int i = 2000000000, mean = 5, j;
    while(i > 0) {
        a.x = 0;
        a.y = 0;
        a.z = 0;
        g.x = 0;
        g.y = 0;
        g.z = 0;
        for(j = 0; j < mean; j++) {
            mpu.GetAngularVelocity(g1);
            mpu.GetAcceleration(a1);
            a.x += a1.x;
            a.y += a1.y;
            a.z += a1.z;
            g.x += g1.x;
            g.y += g1.y;
            g.z += g1.z;
        }
        a.x = ROUND<float>(a.x / mean, 1);
        a.y = ROUND<float>(a.y / mean, 1);
        a.z = ROUND<float>(a.z / mean, 1);
        g.x = ROUND<float>(g.x / mean, 1);
        g.y = ROUND<float>(g.y / mean, 1);
        g.z = ROUND<float>(g.z / mean, 1);
        printf("\n\n\n-------------\n ax=%.3f g\tay=%.3f g\taz=%.3f g\tgx=%.3f °/s\tgy=%.3f °/s\tgz=%.3f °/s\n-------------\n", a.x, a.y, a.z, g.x, g.y, g.z);
        ahrs.update(g.x, g.y, g.z, a.x, a.y, a.z);
        ahrs.getQuaternions(q);
        printf("\n-------------\n qw=%.3f \tqx=%.3f \tqy=%.3f \tqz=%.3f\n-------------\n", q.qw, q.qx, q.qy, q.qz);
        ahrs.getEulerAngles(angles);
        printf("\n-------------\n roll_angle=%.3f °\tpitch_angle=%.3f °\tyaw_angle=%.3f °\n-------------\n\n\n", angles.roll, angles.pitch, angles.yaw);
        usleep(50000);
        --i;
     }
}

int main() {

    pin::initGPIOs();
    //gps();
    ahrs();
    //bmp_kal();
    pin::terminateGPIOs();
}
