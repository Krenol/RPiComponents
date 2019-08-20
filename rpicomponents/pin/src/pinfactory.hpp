#ifndef RPICOMPONENTS_PIN_PIN_FACTORY_H
#define RPICOMPONENTS_PIN_PIN_FACTORY_H
#pragma once

#include "pin.hpp"
//#include <memory>
#include <map>


namespace rpicomponents {
	namespace pin {

		class PinFactory {
		public:
			/**
			* Static method to check whether a pin has the passed PIN_MODE
			*
			* @param pin The pin to be checked
			* @param mode The expected PIN_MODE
			* @return true if pin has passed PIN_MODE else false
			*/
			static bool CheckPinMode(const pin::Pin& pin, rpicomponents::pin::PIN_MODE mode);

			/**
			 * Method to create a new pin pointer
			 *
			 * @param pin: the GPIO pin number
			 * @param mode: the pin mode
			 * @param maxOutputValue: the maximum output of a pin, is depending on the pin mode
			 * @return the pointer to the pin; if pin already created, pointer to existing pin is returned
			 */
			static const Pin& CreatePin(const int8_t& pin, PIN_MODE mode = DIGITAL_MODE, const int16_t &maxOutputValue = DIGITAL_MODE_MAX_VAL);
			
			/**
			 * Method to remove a pin pointer from the factory and the memory
			 * BLOCKING
			 *
			 * @param pin: Pointer to the pin to be removed
			 * @return true if removal was successful, else false
			 */
			static bool RemovePin(const Pin& pin);

			/**
			 * Method to remove a pin pointer from the factory and the memory
			 * BLOCKING
			 *
			 * @param pin: GPIO pin number of the pin to be removed
			 * @return true if removal was successful, else false
			 */
			static bool RemovePin(const int8_t &pin); 

			/**
			 * Method to load a pin pointer from the factory
			 * BLOCKING
			 *
			 * @param pin: GPIO pin number of the pin to be loaded
			 * @return the pin pointer
			 */
			static const Pin& LoadPin(const int8_t &pin); 


		private: //no private method is thread safe!
			/**
			 * Method to load a pin pointer from the factory
			 * NON BLOCKING
			 *
			 * @param pin: GPIO pin number of the pin to be loaded
			 * @return Pin pointer to the created pin
			 */
			static const Pin* PinLoader(const int8_t &pin);

			/**
			 * Method to create a pin pointer 
			 * NON BLOCKING
			 *
			 * @param pin: GPIO pin number of the pin to be created
			 * @param outputMode: output mode of the pin, according to the defined enum
			 * @param maxOutputValue: The maximum pin output value; only needed for SOFTPWM and SOFTTONE
			 * @return pin pointer to created pin
			 */
			static const Pin* PinCreator(const int8_t &pin, PIN_MODE outputMode = DIGITAL_MODE, const int16_t &maxOutputValue = DIGITAL_MODE_MAX_VAL);

			/**
			 * Method to check if a pin pointer exists in the factory
			 * NON BLOCKING
			 *
			 * @param pin: GPIO pin number of the pin that existence should be checked
			 * @return true if pin exists, else false
			 */
			static bool PinExists(const int8_t &pin); 

			/**
			 * Method to add a pin pointer to the factory map
			 * NON BLOCKING
			 *
			 * @param pin: pin pointer of the pin to be added
			 */
			static void AddPinToMap(const Pin* pin); 

			/**
			 * Constructor; static class by private Constructor
			 */
            PinFactory();

			/**
			 * Destructor; can be used for deleting all the pin pointers
			 * BLOCKING
			 */
			~PinFactory();

			static std::map<int8_t,const Pin*> created_pins_; //map for the storage of the pins
			static std::mutex mtx_; //mutex for lock_guard
		};
	}
}


#endif
