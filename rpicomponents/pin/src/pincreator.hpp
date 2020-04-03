#ifndef RPICOMPONENTS_PIN_PINCREATOR_H
#define RPICOMPONENTS_PIN_PINCREATOR_H
#pragma once

#include "pin.hpp"
#include <memory>
#include <map>

typedef std::shared_ptr<rpicomponents::pin::Pin> (*pinfun_t) (int, int);
typedef std::map<rpicomponents::pin::PIN_MODE, pinfun_t> pinmap_t;

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
			static std::shared_ptr<Pin> CreatePin(int pin, PIN_MODE mode = DIGITAL_MODE, int maxOutputValue = DIGITAL_MODE_MAX_VAL);

			/*
			Static method to check whether a pin has the passed PIN_MODE
			
			@param pin The pin to be checked
			@param mode The expected PIN_MODE
			@return true if pin has passed PIN_MODE else false
			*/
			static bool CheckPinMode(std::shared_ptr<Pin> const& pin, rpicomponents::pin::PIN_MODE mode);

            /*
             Method to create a digital pin shared ptr
             @param pin: the GPIO pin number
             @param maxOutputValue: the maximum output of a pin, is depending on the pin mode
             @returns shared ptr to a digital pin
            */
			static std::shared_ptr<Pin> CreateDigitalPin(int pin, int maxOutputValue);

            /*
             Method to create an input pin shared ptr
             @param pin: the GPIO pin number
             @param maxOutputValue: the maximum output of a pin, is depending on the pin mode
             @returns shared ptr to an input pin
            */
            static std::shared_ptr<Pin> CreateInputPin(int pin, int maxOutputValue);

            /*
             Method to create an input/output pin shared ptr
             @param pin: the GPIO pin number
             @param maxOutputValue: the maximum output of a pin, is depending on the pin mode
             @returns shared ptr to an input/output pin
            */
            static std::shared_ptr<Pin> CreateInOutPin(int pin, int maxOutputValue);

            /*
             Method to create an pwm pin shared ptr
             @param pin: the GPIO pin number
             @param maxOutputValue: the maximum output of a pin, is depending on the pin mode
             @returns shared ptr to a pwm pin
            */
            static std::shared_ptr<Pin> CreatePwmPin(int pin, int maxOutputValue);

            /*
             Method to create an software pwm pin shared ptr
             @param pin: the GPIO pin number
             @param maxOutputValue: the maximum output of a pin, is depending on the pin mode
             @returns shared ptr to a software pwm pin
            */
            static std::shared_ptr<Pin> CreateSoftPwmPin(int pin, int maxOutputValue);

            /*
             Method to create an softtone pin shared ptr
             @param pin: the GPIO pin number
             @param maxOutputValue: the maximum output of a pin, is depending on the pin mode
             @returns shared ptr to a softtone pin
            */
            static std::shared_ptr<Pin> CreateSofttonePin(int pin, int maxOutputValue);

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

			static pinmap_t func_map_; //map to pin creation functions
		};
	}
}


#endif
