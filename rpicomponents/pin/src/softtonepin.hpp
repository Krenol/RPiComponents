#ifndef RPICOMPONENTS_PIN_SOFTTONE_PIN_H
#define RPICOMPONENTS_PIN_SOFTTONE_PIN_H
#pragma once

#include "pin.hpp"
#include <softTone.h>

namespace rpicomponents {
	namespace pin {
		class SofttonePin : public Pin {
		public:
			/**
			 * Constructor of this class
			 *
			 * @param pin The used pin of this object
			 * @param maxOutputValue The max output value of this pin
			 */
			SofttonePin(const int &pin, const int &maxOutputValue = 100);

			/**
			 * Constructor of this class
			 *
			 * @param pin Pointer to the used pin of this object
			 * @param maxOutputValue The max output value of this pin
			 */
			SofttonePin(int&& pin, int&& maxOutputValue = 100);

			/**
			 * Copy constructor
			 *
			 * @param pin Reference to pin to be copied
			 */
			SofttonePin(const SofttonePin& pin);

		protected:
			/**
			 * Virtual method implementation of Pin class to write a value to the pin.
			 * Must be implemented by child classes
			 *
			 * @param value Output value that is to be written to the pin
			 */
			void WriteToPin(const int& value) const;

			/**
			 * Virtual method to read the value of the pin.
			 * Must be implemented by child classes
			 *
			 * @returns the status_ variable
			 */
			int ReadFromPin() const;
		};
	}
}
#endif