#ifndef RPICOMPONENTS_COMPONENT_H
#define RPICOMPONENTS_COMPONENT_H
#pragma once

#include <algorithm>
#include <vector>
#include "../pin/include/rpicomponents/pin/pins.hpp"
#include "../pin/utils/include/rpicomponents/pin/utils/pinutils.hpp"
#include "../utils/include/rpicomponents/utils/rpicomponents_utils.hpp"

namespace rpicomponents {
	class Component {
	private:
		//necessary compoennt values
		mutable std::vector<int8_t> used_pins_{ };
		const std::string component_name_{ "component" };

		/**
		* Method to get the vector iterator to find a certain pin
		* This methid is not thread safe
		*
		* @param pin the Pin object to be found
		* @return std::vector<int>::iterator pointing to the location the pin is stored inside the vector
		*/
		std::vector<int8_t>::iterator GetPinIterator(int8_t pin) const;

	protected:
		virtual ~Component() = 0; //virtual protected destructor to make class abstract
		mutable std::mutex mtx_;
		/**
		* Method to add a pin to the component
		* This methid is thread safe and locks the protected mtx_
		*
		* @param pin The pin to be added
		*/
		void AddPin(int8_t pin) const;

		/**
		* Method to check multiple pins to the component
		* This methid is thread safe and locks the protected mtx_
		*
		* @param pins The vector containing all pins to be added
		*/
		void AddPins(std::vector<int8_t> pins) const;

		/**
		* Method to remove all pins from the pin vector
		* This methid is thread safe and locks the protected mtx_
		*
		* @return true if operation was successfull (vector not empty), else false
		*/
		bool RemoveAllPins() const;

		/**
		* Method to check if the current component uses a certain Pin
		* This methid is thread safe and locks the protected mtx_
		*
		* @param pin The pin to be removed from the vector
		* @return true if operation was successfull (pin was stored in the vector), else false
		*/
		bool RemovePin(int8_t pin) const;

		/**
		* Method to check if the current component uses a certain Pin
		*
		* @param componentName The name of the component as std::string. Is returned by the ToString method
		*/
		Component(std::string componentName);

		/**
		* Method to check if the passed pin is not null of the passed PIN_MODE
		* Throws errors on detected error
		* BLOCKING
		*
		* @param pin The to be checked pin
		* @param mode The expected pin mode
		*/
		void CheckPinStatus(const pin::Pin* pin, rpicomponents::pin::utils::PIN_MODE mode) const;

		/**
		* Method to check if the passed pin is not null of the passed PIN_MODE
		* Throws errors on detected error
		* BLOCKING
		*
		* @param pin The to be checked pin
		* @param mode The expected pin modes as a vector
		*/
		void CheckPinStatus(const pin::Pin* pin, std::vector<rpicomponents::pin::utils::PIN_MODE> mode) const;

		/**
		* Method to check if passed pin pointer is valid
		* Throws invalid_argument exception if pin::PinFactory::CheckPin is true
		*
		* @param pin: The pin pointer to be checked
		*/
		void CheckPin(const pin::Pin* pin) const;
			
	public:
		/**
		* Method to check if the current component uses a certain pin
		* This methid is thread safe and locks the protected mtx_
		*
		* @param pin The pin to be checked for usage
		* @return true if pin is used, else false
		*/
		bool UsesPin(int8_t pin) const;

		/**
		* Method to check if the current component uses certain pins
		*
		* @param pins The vector containing all the pins to be checked for usage
		* @return true if all pins are used by the component, else false
		*/
		bool UsesPins(std::vector<int8_t> pins) const;

		/**
		* Method to get the name of the component
		*
		* @return The component name as a std::string as given during initialization
		*/
		std::string ToString() const;
	};
}

#endif