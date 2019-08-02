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
			InputPin(int8_t pin);

			/**
			 * Constructor of this class
			 *
			 * @param pin Pointer to the used pin of this object
			 */
			InputPin(int8_t&& pin);

			/**
			 * Copy constructor
			 *
			 * @param pin Reference to pin to be copied
			 */
			InputPin(InputPin& pin);

			/**
			 * Copy constructor
			 *
			 * @param pin RValue to pin to be copied
			 */
			InputPin(InputPin&& pin);

		protected:
			/**
			 * Virtual method implementation of Pin class to write a value to the pin.
			 * Must be implemented by child classes
			 *
			 * @param value Output value that is to be written to the pin
			 */
			void WriteToPin(int16_t value) const;

			/**
			 * Virtual method to read the value of the pin.
			 * Must be implemented by child classes
			 *
			 * @returns the read value of the pin
			 */
			int16_t ReadFromPin() const;
		};
	}
}


#endif