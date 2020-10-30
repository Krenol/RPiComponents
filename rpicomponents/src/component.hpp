#ifndef RPICOMPONENTS_COMPONENT_H
#define RPICOMPONENTS_COMPONENT_H
#pragma once

#include <algorithm>
#include <vector>
#include <memory>
#include "pin/pins.hpp"
#include <functional>


namespace rpicomponents {
	constexpr const char* COMPONENT = "component";
	constexpr const int I2C_BUS_CHANNEL  = 1;
	typedef std::function<void(int, int, const std::string&)> gpio_cb;

	class Component {
	private:
		//necessary Component values
        std::vector<int> used_pins_{ };
		const std::string component_name_{ COMPONENT };

		/*
		Method to get the vector iterator to find a certain pin

		
		@param pin the Pin object to be found
		@return std::vector<int>::iterator pointing to the location the pin is stored inside the vector
		*/
        std::vector<int>::iterator GetPinIterator( int pin);

	protected:
		virtual ~Component() = 0; //virtual protected destructor to make class abstract

		/*
		Method to add a pin to the component
		
		@param pin The pin to be added
		*/
        void AddPin(int pin);

		/*
		Method to check multiple pins to the component
		
		@param pins The vector containing all pins to be added
		*/
        void AddPins(const std::vector<int>& pins);

		/*
		Method to remove all pins from the pin vector
		
		@return true if operation was successfull (vector not empty), else false
		*/
        bool RemoveAllPins();

		/*
		Method to check if the current component uses a certain Pin
		
		@param pin The pin to be removed from the vector
		@return true if operation was successfull (pin was stored in the vector), else false
		*/
        bool RemovePin(int pin);

		/*
		Constructor
		
		@param componentName The name of the component as std::string. Is returned by the ToString method
		*/
		Component(const std::string &componentName);

		/*
		Constructor
		
		@param componentName The name of the component as std::string. Is returned by the ToString method
		*/
		Component(std::string&& componentName);

		/*
		Constructor
		
		@param component The component to be copied
		*/
		Component(const Component &component);
			
	public:
		/*
		Method to check if the current component uses a certain pin
		
		@param pin The pin to be checked for usage
		@return true if pin is used, else false
		*/
        bool UsesPin(int pin);

		/*
		Method to check if the current component uses certain pins
		
		@param pins The vector containing all the pins to be checked for usage
		@return true if all pins are used by the component, else false
		*/
        bool UsesPins(std::vector<int>& pins);

		/*
		Method to get all used pin of the component

		@return all used pins in a vector
		*/
        const std::vector<int>& GetUsedPins();

		/*
		Method to get the name of the component
		
		@return The component name as a std::string as given during initialization
		*/
		const std::string& ToString() const;
	};
}

#endif
