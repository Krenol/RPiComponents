#ifndef RPICOMPONENTS_PIN_H
#define RPICOMPONENTS_PIN_H
#pragma once

#include "pinchecker.hpp"
#include <wiringPi.h>
#include <mutex>
#include <thread>

namespace rpicomponents {
	namespace pin {
		class Pin {
		public:

			/**
			 * Get the used pin
			 *
			 * @return used pin of the object as const int
			 */
			int GetPin() const;

			/**
			 * Check if pin is on or off
			 * Note: this method call is thread safe
			 * @return true if pin output is on, else false
			 */
			bool IsOn();

			/**
			 * Turn the pin output on
			 * Note: this method call is thread safe
			 */
			void OutputOn();

			/**
			 * Set the output value of a pin to a certain value.
			 * Needed for PWM, SOFTPWM or SOFTTONE
			 * Note: this method call is thread safe
			 *
			 * @param value: set output value of pin
			 */
			void Output(int value);

			/**
			 * Turn the pin output off
			 *  Note: this method call is thread safe
			 */
			void OutputOff();

		protected:
			/**
			 * Constructor
			 *
			 * @param pin The pin integer value according to wiringPi pin layout
			 * @param mode The output mode of the pin (digital, pwm, soft pwm or softtone)
			 * @param maxValue The maximum output of this pin (digital must be 1, pwm must be 1023 and always above 0)
			 */
			Pin(int pin, int mode = DIGITAL_MODE, int maxValue = DIGITAL_MODE_MAX_VAL);

			/**
			 * Checks whether given value for the pin output is inside the valid range of this object
			 *
			 *  Note: this method call is thread safe without using mutex and locks
			 * @return true if value is inside the 0 and given max_value_, else false
			 */
			bool CheckInputValue(int value);

			/**
			 * Virtual method to write a value to the pin. 
			 * Must be implemented by child classes
			 *
			 * @param value Output value that is to be written to the pin
			 */
			virtual void WriteToPin(int value) = 0;

			const int pin_{ GPIO17 }, mode_ = { DIGITAL_MODE }, max_value_{ DIGITAL_MODE_MAX_VAL }, min_value_{ 0 };
			mutable int status_{ 0 };
		};
	}
}


#endif