#ifndef RPICOMPONENTS_PIN_H
#define RPICOMPONENTS_PIN_H
#pragma once

#include "pindefinitions.hpp"
#include <wiringPi.h>
#include <atomic>

namespace rpicomponents {
	namespace pin {
		class Pin {
		public:
			/*
			 Method to read the digital value of the pin
			 
			 @returns 0 for no read output at pin, 1 if there is an output and -1 if pin is not on INPUT mode
			 */
			int ReadPinValue() const;

			/*
			 Get the used pin
			 
			 @return used pin of the object as const int
			 */
			int GetPin() const;

			/*
			 Get the pin output mode 
			 
			 @return output mode of this pin as const PIN_MODE
			 */
			PIN_MODE OutputMode() const;

			/*
			 Check if pin is on or off

			 @return true if pin output is on, else false
			 */
			bool IsOn() const;

			/*
			 Turn the pin output on
			 */
			void OutputOn() const;

			/*
			 Set the output value of a pin to a certain value.
			 Needed for PWM, SOFTPWM or SOFTTONE
			 
			 @param value: set output value of pin
			 */
			void Output(int value) const;

			/*
			 Turn the pin output off
			 */
			void OutputOff() const;

			/*
			Method to get the max output value of this pin

			@returns an int representing the maxoutput value of the pin
			*/
			int GetMaxOutValue() const;

		protected:
			/*
			 Constructor
			 
			 @param pin The pin integer value according to wiringPi pin layout
			 @param mode The output mode of the pin (digital, pwm, soft pwm, input, inputoutput or softtone)
			 @param maxValue The maximum output of this pin (digital must be 1, pwm must be 1023 and always above 0)
			 */
			//Pin(int pin, PIN_MODE mode = PIN_MODE::DIGITAL_MODE, int maxOutputValue = DIGITAL_MODE_MAX_VAL);

			/*
			 Constructor
			 
			 @param pin The pin integer value according to wiringPi pin layout
			 @param mode The output mode of the pin (digital, pwm, soft pwm, input, inputoutput or softtone)
			 @param maxValue The maximum output of this pin (digital must be 1, pwm must be 1023 and always above 0)
			 */
			Pin(int pin, PIN_MODE mode = PIN_MODE::DIGITAL_MODE, int maxOutputValue = DIGITAL_MODE_MAX_VAL);

			/*
			 Constructor
			 
			 @param pin The pin integer value according to wiringPi pin layout
			 @param mode The output mode of the pin (digital, pwm, soft pwm, input, inputoutput or softtone)
			 @param maxValue The maximum output of this pin (digital must be 1, pwm must be 1023 and always above 0)
			 */
			//Pin(int&& pin, PIN_MODE&& mode = PIN_MODE::DIGITAL_MODE, int&& maxOutputValue = 1);

			/*
			 Constructor
			 
			 @param pin The pin integer value according to wiringPi pin layout
			 @param mode The output mode of the pin (digital, pwm, soft pwm, input, inputoutput or softtone)
			 @param maxValue The maximum output of this pin (digital must be 1, pwm must be 1023 and always above 0)
			 */
			Pin(const Pin &pin);

			/*
			 Checks whether given value for the pin output is inside the valid range of this object
			 
			 Note: this method call is thread safe without using mutex and locks
			 @return true if value is inside the 0 and given max_value_, else false
			 */
			bool CheckInputValue(int value) const;

			/*
			 Virtual method to write a value to the pin. 
			 Must be implemented by child classes
			 
			 @param value Output value that is to be written to the pin
			 */
			virtual void WriteToPin(int value) const  = 0;

			/*
			 Virtual method to read the value of the pin.
			 Must be implemented by child classes
			 
			 @returns the read value of the pin, or the status_ variable if not in INPUT mode
			 */
			virtual int ReadFromPin() const = 0;

			const int pin_{ GPIO17 };
			const int max_value_{ DIGITAL_MODE_MAX_VAL }, min_value_{ 0 };
			const PIN_MODE mode_{ PIN_MODE::DIGITAL_MODE };
			mutable std::atomic<int> status_{ 0 };

		private:
			/*
			Initializer for Constructors; reduce redundancy
			*/
			void Initialize() const;
		};
	}
}


#endif