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

int main() {

    // rpicomponents::MPU6050 mpu;
    // auto offset_a = mpu.CalibrateAcceleration();
    // printf("\n\n\n-------------\n Ax=%.3f g\tAy=%.3f g\tAz=%.3f g\tdx=%.3f g\tdy=%.3f g\tdz=%.3f g\n-------------\n\n\n",
    //     offset_a.x, offset_a.y, offset_a.z, offset_a.dx, offset_a.dy, offset_a.dz);
    // auto offset_g = mpu.CalibrateGyro();
    // printf("\n\n\n-------------\n Gx=%.3f °/s\tGy=%.3f °/s\tGz=%.3f °/s\tdx=%.3f °/s\tdy=%.3f °/s\tdz=%.3f °/s\n-------------\n\n\n",
    //     offset_g.x, offset_g.y, offset_g.z, offset_g.dx, offset_g.dy, offset_g.dz);
    // rpicomponents::mpu_angles a;
    // rpicomponents::mpu_data d;
    // while(true) {
    //     mpu.GetKalmanAngles(a);
    //     mpu.GetAcceleration(d);
    //     printf("\n\n\n-------------\n beta=%.3f °\tgamma=%.3f °\tAx=%.3f g\tAy=%.3f g\tAz=%.3f g\n-------------\n\n\n", a.beta, a.gamma, d.x, d.y, d.z);
    //     utils::Waiter::SleepMillis(500);
    // }
    std::ifstream ifs("/home/pi/mnt/RPiComponents/rpicomponents/test/data.json");
    json j = json::parse(ifs);
    auto jf = j.at("escs");
    int speed = jf.at("turn_speed");
    esc_map map;
    createEscMap(map, jf);
    for(auto& it : map){
        printf("\n\n-------------\n");
        std::cout << "Calibrating ESC of " << it.first << " motor\n";
        it.second.Calibrate();
        printf("let motor turn now with %i...\n", speed);
        it.second.SetOutputSpeed(speed);
        utils::Waiter::SleepSecs(2);
        printf("-------------");
    }
	std::cin.get();
}
