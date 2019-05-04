#ifndef RPICOMPONENTS_PIN_H
#define RPICOMPONENTS_PIN_H
#pragma once

#include "pinchecker.hpp"
#include <wiringPi.h>
#include <atomic>
#include <mutex>

namespace rpicomponents {
	namespace pin {
		class Pin {
		public:
			/**
			 * Method to read the digital value of the pin
			 *
			 * @returns 0 for no read output at pin, 1 if there is an output and -1 if pin is not on INPUT mode
			 */
			int ReadPinValue();

			/**
			 * Get the used pin
			 *
			 * @return used pin of the object as const int
			 */
			int GetPin() const;

			/**
			 * Get the pin output mode 
			 *
			 * @return output mode of this pin as const PIN_MODE
			 */
			PIN_MODE OutputMode() const;

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
			static std::mutex mtx_; //static & const variable, so we cannot write to multiple pins at the same time
			/**
			 * Constructor
			 *
			 * @param pin The pin integer value according to wiringPi pin layout
			 * @param mode The output mode of the pin (digital, pwm, soft pwm or softtone)
			 * @param maxValue The maximum output of this pin (digital must be 1, pwm must be 1023 and always above 0)
			 */
			Pin(int pin, PIN_MODE mode = PIN_MODE::DIGITAL, int maxOutputValue = DIGITAL_MODE_MAX_VAL);

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

			/**
			 * Virtual method to read the value of the pin.
			 * Must be implemented by child classes
			 *
			 * @returns the read value of the pin, or the status_ variable if not in INPUT mode
			 */
			virtual int ReadFromPin() = 0;

			const int pin_{ GPIO17 }, max_value_{ DIGITAL_MODE_MAX_VAL }, min_value_{ 0 };
			const PIN_MODE mode_{ PIN_MODE::DIGITAL };
			mutable std::atomic<int> status_{ 0 };
		};
	}
}


#endif