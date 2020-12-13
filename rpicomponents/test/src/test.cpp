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

// for convenience
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

int main() {

    pin::initGPIOs();
    rpicomponents::MPU6050 mpu;
    auto offset_a = mpu.CalibrateAcceleration();
    printf("\n\n\n-------------\n Ax=%.3f g\tAy=%.3f g\tAz=%.3f g\tdx=%.3f g\tdy=%.3f g\tdz=%.3f g\n-------------\n\n\n",
        offset_a.x, offset_a.y, offset_a.z, offset_a.dx, offset_a.dy, offset_a.dz);
    auto offset_g = mpu.CalibrateGyro();
    printf("\n\n\n-------------\n Gx=%.3f °/s\tGy=%.3f °/s\tGz=%.3f °/s\tdx=%.3f °/s\tdy=%.3f °/s\tdz=%.3f °/s\n-------------\n\n\n",
        offset_g.x, offset_g.y, offset_g.z, offset_g.dx, offset_g.dy, offset_g.dz);
    rpicomponents::mpu_angles a;
    rpicomponents::mpu_data d;
    while(true) {
        mpu.GetKalmanAngles(a);
        mpu.GetAcceleration(d);
        printf("\n\n\n-------------\n roll_angle=%.3f °\tpitch_angle=%.3f °\tAx=%.3f g\tAy=%.3f g\tAz=%.3f g\n-------------\n\n\n", a.roll_angle, a.pitch_angle, d.x, d.y, d.z);
        usleep(500000);
    }
    
    pin::terminateGPIOs();
}
