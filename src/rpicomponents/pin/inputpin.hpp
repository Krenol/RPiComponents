#ifndef RPICOMPONENTS_PIN_INPUT_PIN_H
#define RPICOMPONENTS_PIN_INPUT_PIN_H
#pragma once

#include "pin.hpp"

namespace rpicomponents {
	namespace pin {
		class InputPin : public Pin {
		public:
			/**
			 * Constructor of this class
			 *
			 * @param pin The used pin of this object
			 */
			InputPin(int pin);

		protected:
			/**
			 * Virtual method implementation of Pin class to write a value to the pin.
			 * Must be implemented by child classes
			 *
			 * @param value Output value that is to be written to the pin
			 */
			void WriteToPin(int value);

			/**
			 * Virtual method to read the value of the pin.
			 * Must be implemented by child classes
			 *
			 * @returns the read value of the pin
			 */
			int ReadFromPin();
		};
	}
}


#endif