#ifndef RPICOMPONENTS_PIN_PIN_FACTORY_H
#define RPICOMPONENTS_PIN_PIN_FACTORY_H
#pragma once

#include "digitalpin.hpp"
#include "pwmpin.hpp"
#include "softpwmpin.hpp"
#include "softtonepin.hpp"
#include "inputpin.hpp"
#include <memory>
#include <map>
#include <iostream>

namespace rpicomponents {
	namespace pin {
		class PinFactory {
		public:
			/**
			 * Method to create a new pin pointer
			 *
			 * @param pin: the GPIO pin number
			 * @param mode: the pin mode
			 * @param maxOutputValue: the maximum output of a pin, is depending on the pin mode
			 * @return the pointer to the pin; if pin already created, pointer to existing pin is returned
			 */
			static const Pin* CreatePin(int pin, PIN_MODE mode = DIGITAL_MODE, int maxOutputValue = DIGITAL_MODE_MAX_VAL);
			
			/**
			 * Method to remove a pin pointer from the factory and the memory
			 * This method is thread safe!
			 *
			 * @param pin: Pointer to the pin to be removed
			 * @return true if removal was successful, else false
			 */
			static bool RemovePin(const Pin* pin); //thread safe

			/**
			 * Method to remove a pin pointer from the factory and the memory
			 * This method is thread safe!
			 *
			 * @param pin: GPIO pin number of the pin to be removed
			 * @return true if removal was successful, else false
			 */
			static bool RemovePin(int pin); //thread safe

			/**
			 * Method to load a pin pointer from the factory
			 * This method is thread safe!
			 *
			 * @param pin: GPIO pin number of the pin to be loaded
			 * @return the pin pointer
			 */
			static const Pin* LoadPin(int pin); //thread safe

			/**
			 * Destructor; can be used for deleting all the pin pointers
			 * This method is thread safe!
			 */
			~PinFactory();

		private: //no private method is thread safe!
			/**
			 * Method to load a pin pointer from the factory
			 * This method is NOT thread safe!
			 *
			 * @param pin: GPIO pin number of the pin to be loaded
			 * @return Pin pointer to the created pin
			 */
			static const Pin* PinLoader(int pin);

			/**
			 * Method to create a pin pointer 
			 * This method is NOT thread safe!
			 *
			 * @param pin: GPIO pin number of the pin to be created
			 * @param outputMode: output mode of the pin, according to the defined enum
			 * @param maxOutputValue: The maximum pin output value; only needed for SOFTPWM and SOFTTONE
			 * @return pin pointer to created pin
			 */
			static const Pin* PinCreator(int pin, PIN_MODE outputMode = DIGITAL_MODE, int maxOutputValue = DIGITAL_MODE_MAX_VAL);

			/**
			 * Method to check if a pin pointer exists in the factory
			 * This method is NOT thread safe!
			 *
			 * @param pin: GPIO pin number of the pin that existence should be checked
			 * @return true if pin exists, else false
			 */
			static bool PinExists(int pin); 

			/**
			 * Method to add a pin pointer to the factory map
			 * This method is NOT thread safe!
			 *
			 * @param pin: pin pointer of the pin to be added
			 */
			static void AddPinToMap(const Pin* pin); 

			/**
			 * Constructor; static class by private Constructor
			 */
            PinFactory();

			static std::map<int,const Pin*> created_pins_; //map for the storage of the pins
			static std::mutex mtx_; //mutex for lock_guard
		};
	}
}


#endif
