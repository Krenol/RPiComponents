#include "component.hpp"

#ifndef RPICOMPONENTS_TRANSISTOR_H
#define RPICOMPONENTS_TRANSISTOR_H

namespace rpicomponents {
	/**
	* Enumeration holding all possible transistor types
	*/
	enum TRANSISTOR_TYPE {
		NPN, PNP
	};
    constexpr const char* COMPONENT_TRANSISTOR = "transistor";
	class Transistor : public Component {
	private:
        std::unique_ptr<pin::Pin> pin_; //the used pin of the transistor
		const TRANSISTOR_TYPE type_{ NPN }; //the transistor type

	public:	
		
		/**
		* Constructor for creating a transistor
		*
		* @param pin: GPIO pin of the transistor
		* @param pin_mode: The mode of the pin, e.g. DIGITAL_MODE
		* @param pin_max_val: The max outout value of the pin, e.g. 1
		* @param pud: the to be checked PUD value
		*/
		Transistor(int pin, pin::PIN_MODE pin_mode, int pin_max_val, TRANSISTOR_TYPE type);


		/**
		* Copy Constructor 
		*
		* @param transistor: The transistor to be copied
		*/
		Transistor(const Transistor& transistor);

		/**
		* Method to get the transistor type
		*
		* @returns The transistor type of this object
		*/
		TRANSISTOR_TYPE GetType() const;

		/**
		* Turn the transistor on to the maximum output value of the pin's output mode
		*/
		void TurnOn() const;

		/**
		* Turn on the transistor pin to a specific value (obsolete if digital pin)
		*
		* @param value: Output value of the pin
		*/
		void TurnOn(int value) const;

		/**
		* Turn the transistor off
		*/
		void TurnOff() const;

		/**
		* Method to find out if transistor is on or off
		*
		* @return true if transistor is on else false
		*/
		bool IsOn() const;

		/*
		* Method to get the used pin
		*
		* @returns the used pin of the component
		*/
		int GetPin() const;

		/*
		* Method to get the pin mode
		*
		* @returns the pin mode
		*/
		pin::PIN_MODE GetPinMode() const;

		/*
		* Method to get the pin max value
		*
		* @returns the pin max value
		*/
		int GetMaxOutValue() const;
	};
}

#endif
