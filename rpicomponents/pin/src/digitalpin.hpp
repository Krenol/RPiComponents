#ifndef RPICOMPONENTS_PIN_DIGITAL_PIN_H
#define RPICOMPONENTS_PIN_DIGITAL_PIN_H
#pragma once

#include "pin.hpp"

namespace rpicomponents {
	namespace pin {
		class DigitalPin : public Pin {
		public:
			/*
			 Constructor of this class
			 
			 @param pin The used pin of this object
			 */
			DigitalPin(int pin);

			/*
			 Constructor of this class
			 
			 @param pin RValue of the used pin of this object
			 */
			//DigitalPin(int&& pin);

			/*
			 Copy constructor
			 
			 @param pin The to be copied pin
			 */
			DigitalPin(const DigitalPin& pin);

		protected:
			/*
			 Method implementation of Pin class to write a value to the pin.
			 
			 @param value Output value that is to be written to the pin
			 */
			void WriteToPin(int value) const;

			/*
			 Method to read the value of the pin.
			 
			 @returns the status_ variable
			 */
			int ReadFromPin() const;
		};
	}
}


#endif