#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
//#include "../external/doctest/doctest/doctest.h"

#include "rpicomponents/rpicomponents.hpp"

//***TEST CASES***

/*TEST_CASE("Creating button and checking it") {
    rpicomponents::Button btn(pin::PinCreator::CreatePin(1, pin::INPUT_MODE), PUD_UP);
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

// for convenience
using json = nlohmann::json;

int main() {
    auto j3 = json::parse("{ \"happy\": true, \"pi\": 3.141 }");
    json j;
    // add a number that is stored as double (note the implicit conversion of j to an object)
    j["pi"] = 3.141;

    // add a Boolean that is stored as bool
    j["happy"] = true;

    std::cout << "json: " << j.dump() << std::endl;
    
    rpicomponents::MPU6050 mpu;
    auto offset_a = mpu.CalibrateAcceleration();
    printf("\n\n\n-------------\n Ax=%.3f g\tAy=%.3f g\tAz=%.3f g\tdx=%.3f g\tdy=%.3f g\tdz=%.3f g\n-------------\n\n\n",
        offset_a.a_x, offset_a.a_y, offset_a.a_z, offset_a.d_x, offset_a.d_y, offset_a.d_z);
    auto offset_g = mpu.CalibrateGyro();
    printf("\n\n\n-------------\n Gx=%.3f °/s\tGy=%.3f °/s\tGz=%.3f °/s\tdx=%.3f °/s\tdy=%.3f °/s\tdz=%.3f °/s\n-------------\n\n\n",
        offset_g.g_x, offset_g.g_y, offset_g.g_z, offset_g.d_x, offset_g.d_y, offset_g.d_z);
    while(1){
        auto g = mpu.GetGyro();
        auto a = mpu.GetAcceleration();
        printf("\n Gx=%.3f °/s\tGy=%.3f °/s\tGz=%.3f °/s\tAx=%.3f g\tAy=%.3f g\tAz=%.3f g\n",g.g_x, g.g_y, g.g_z, a.a_x, a.a_y, a.a_z);
		delay(500);
    }
    

	std::cin.get();

}

