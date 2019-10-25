#ifndef RPICOMPONENTS_PINCHECKER_H
#define RPICOMPONENTS_PINCHECKER_H
#pragma once

#include <string>
#include "pindefinitions.hpp"
#include "pin.hpp"

namespace rpicomponents {
    namespace pin {
        class PinChecker {
        public:

            /*
            Static method to check whether a pin is inside the GPIO pin range of the RPi 3
            
            @param pin The pin integer to be checked
            @return true if pin is inside the RPi 3 gpio pin range ( 0 <= pin <= 31), else false
            */
            static bool IsValidPinValue(const int &pin);

            /*
            Static method to check whether a pin is hardware pwm capable or not
            
            @param pin The pin that should be checked for hardware pwm capability
            @return true if pin is hardware pwm capable, else false
            */
            static bool PinIsHardwarePWMCapable(const int &pin);

        private:
            /*
            Private constructor to make class static
            */
            PinChecker() {}

			PinChecker(const PinChecker&) = delete;
			PinChecker& operator=(const PinChecker&) = delete;
        };
    }
}


#endif
