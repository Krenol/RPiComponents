#ifndef RPICOMPONENTS_PIN_INOUT_PIN_H
#define RPICOMPONENTS_PIN_INOUT_PIN_H
#pragma once

#include "pin.hpp"

namespace rpicomponents {
	namespace pin {
		class InOutPin : public Pin {
		public:
			/**
			 * Constructor of this class
			 *
			 * @param pin The used pin of this object
			 */
			InOutPin(const int &pin);

			/**
			 * Constructor of this class
			 *
			 * @param pin Pointer to the used pin of this object
			 */
			InOutPin(int&& pin);

			/**
			 * Copy constructor
			 *
			 * @param pin Reference to pin to be copied
			 */
			InOutPin(InOutPin& pin);

		protected:
			/**
			 * Virtual method implementation of Pin class to write a value to the pin.
			 * Must be implemented by child classes
			 * BLOCKING
			 * @param value Output value that is to be written to the pin
			 */
			void WriteToPin(const int& value) const;

			/**
			 * Virtual method to read the value of the pin.
			 * Must be implemented by child classes
			 * BLOCKING
			 * @returns the status_ variable
			 */
			int ReadFromPin() const;
		};
	}
}


#endif