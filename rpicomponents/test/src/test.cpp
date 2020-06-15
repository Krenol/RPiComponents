#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../external/doctest/doctest/doctest.h"

#include "rpicomponents/rpicomponents.hpp"

//***TEST CASES***

TEST_CASE("Creating button and checking it") {
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
}

/*
#include <thread>
#include <cassert>
#include <iostream>
#include <mutex>

std::mutex mtx;

void On(rpicomponents::Led* led, int no){
	std::lock_guard<std::mutex> lck(mtx);

    for(auto i= 0; i <  no; i++) {
        auto on = led->IsOn();
		std::cout << "thread " << no << " led is " << on<< std::endl;
        on ? led->TurnOff() : led->TurnOn();
    }

    return;
}


int main() {
    rpicomponents::Pcf8574 pcf(0x48);
    rpicomponents::Pcf8591 pcf1(0x49, 124);
    //rpicomponents::Mpu6050 mpu(0x51);
    rpicomponents::Transistor tr(1, rpicomponents::NPN, pin::PWM_MODE);

    //cout << btn->IsPressed()<<endl;
	//auto pin = pin::PinFactory::CreatePin(12);
    rpicomponents::UltrasonicSensor uss (2, 3);

	rpicomponents::Button btn(1);

  
	std::cout << "500 mm are " << uss.UnitConverter(500, rpicomponents::UNIT_MM, rpicomponents::UNIT_M) << " m\n";
    std::cout << pcf.ToString() << std::endl;


	std::cin.get();

}
*/
