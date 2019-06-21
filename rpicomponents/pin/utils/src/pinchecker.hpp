#ifndef RPICOMPONENTS_UTILS_PINCHECKER_H
#define RPICOMPONENTS_UTILS_PINCHECKER_H
#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include "pindefinitions.hpp"

namespace rpicomponents {
	namespace pin {
		namespace utils {

			class PinChecker {
			public:
				/**
				 * Static method to check whether a pin is hardware pwm capable or not
				 *
				 * @param pin The pin that should be checked for hardware pwm capability
				 * @return true if pin is hardware pwm capable, else false
				 */
				static bool PinIsHardwarePWMCapable(int8_t pin);

				/**
				 * Static method to check whether an address is a valid I2C address or not
				 *
				 * @param address The i2c address to be checked
				 * @return true if hardware is a valid I2C address capable, else false
				 */
				static bool IsI2CAddress(int16_t address);

				/**
				 * Static method to transform an integer & decimal I2C addres into a string hex value
				 *
				 * @param address The decimal i2c address to be transformed
				 * @return String with the transformed hex i2c address
				 */
				static std::string GetHexAddress(int16_t address);

				/**
				 * Static method to check whether a pin is inside the GPIO pin range of the RPi 3
				 *
				 * @param pin The pin integer to be checked
				 * @return true if pin is inside the RPi 3 gpio pin range ( 0 <= pin <= 31), else false
				 */
				static bool IsValidPinValue(int8_t pin);


			private:
				/**
				 * Private constructor to make class static
				 */
				PinChecker() {}
			};
		}
	}
}


#endif
