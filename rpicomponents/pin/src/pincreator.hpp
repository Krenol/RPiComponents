#ifndef RPICOMPONENTS_PIN_PINCREATOR_H
#define RPICOMPONENTS_PIN_PINCREATOR_H
#pragma once

#include "pin.hpp"
#include <memory>

namespace rpicomponents {
	namespace pin {
		class PinCreator {
		public:
			/*
			 Method to get an instance of this
			 
			 @return reference to the static instance of this
			 */
			static PinCreator& GetInstance();
			/*
			 Method to create a new pin pointer
			 
			 @param pin: the GPIO pin number
			 @param mode: the pin mode
			 @param maxOutputValue: the maximum output of a pin, is depending on the pin mode
			 @return the pointer to the pin; if pin already created, pointer to existing pin is returned
			 */
			static std::unique_ptr<Pin> CreatePin(int pin, PIN_MODE mode = DIGITAL_MODE, int maxOutputValue = DIGITAL_MODE_MAX_VAL);

			/*
			Static method to check whether a pin has the passed PIN_MODE
			
			@param pin The pin to be checked
			@param mode The expected PIN_MODE
			@return true if pin has passed PIN_MODE else false
			*/
			static bool CheckPinMode(std::unique_ptr<Pin> const& pin, rpicomponents::pin::PIN_MODE mode);

		private:
			/*
			 Constructor; static class by private constructor
			 */
			PinCreator() = default;
			/*
			 Deconstructor
			 */
			~PinCreator() = default;

			PinCreator(const PinCreator&) = delete;
			PinCreator& operator=(const PinCreator&) = delete;
		};
	}
}


#endif