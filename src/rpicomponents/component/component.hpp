#ifndef RPICOMPONENTS_COMPONENT_H
#define RPICOMPONENTS_COMPONENT_H
#pragma once

#include <softPwm.h>
#include <softTone.h>
#include <math.h>
#include <iomanip>
#include <algorithm>
#include "../pin/pin.hpp"


namespace rpicomponents {
	namespace component {

		class Component {
		private:
			//virtual private destructor to make class abstract
			virtual ~Component() = 0; 
			//necessary compoennt values
			std::vector<int> used_pins_{ }; // for RAM optimization we do not store Pin objects here
			const std::string component_name_{ "component" };

			/**
			 * Method to get the vector iterator to find a certain pin
			 * This methid is not thread safe
			 *
			 * @param pin the Pin object to be found
			 * @return std::vector<int>::iterator pointing to the location the pin is stored inside the vector
			 */
			std::vector<int>::iterator GetPinIterator(int pin);

		protected:
			std::mutex mtx_;
			/**
			 * Method to add a pin to the component
			 * This methid is thread safe and locks the protected mtx_
			 *
			 * @param pin The pin to be added
			 */
			void AddPin(int pin);

			/**
			 * Method to check multiple pins to the component
			 * This methid is thread safe and locks the protected mtx_
			 *
			 * @param pins The vector containing all pins to be added
			 */
			void AddPins(std::vector<int> pins);

			/**
			 * Method to remove all pins from the pin vector
			 * This methid is thread safe and locks the protected mtx_
			 *
			 * @return true if operation was successfull (vector not empty), else false
			 */
			bool RemoveAllPins();

			/**
			 * Method to check if the current component uses a certain Pin
			 * This methid is thread safe and locks the protected mtx_
			 *
			 * @param pin The pin to be removed from the vector
			 * @return true if operation was successfull (pin was stored in the vector), else false
			 */
			bool RemovePin(int pin);

			/**
			 * Method to check if the current component uses a certain Pin
			 *
			 * @param componentName The name of the component as string. Is returned by the ToString method
			 */
			Component(std::string componentName);
			
		public:
			/**
			 * Method to check if the current component uses a certain pin
			 * This methid is thread safe and locks the protected mtx_
			 *
			 * @param pin The pin to be checked for usage
			 * @return true if pin is used, else false
			 */
			bool UsesPin(int pin);

			/**
			 * Method to check if the current component uses certain pins
			 *
			 * @param pins The vector containing all the pins to be checked for usage
			 * @return true if all pins are used by the component, else false
			 */
			bool UsesPins(std::vector<int> pins);

			/**
			 * Method to get the name of the component
			 *
			 * @return The component name as a string as given during initialization
			 */
			std::string ToString();
		};
	}
}

#endif