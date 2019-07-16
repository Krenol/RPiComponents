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

	class Transistor : public Component {
	private:
		const pin::Pin* pin_; //the used pin of the transistor
		const TRANSISTOR_TYPE type_{ NPN }; //the transistor type

		/**
		* Initializer for Constructors; reduce redundancy
		*/
		void Initialize();

	public:	
		/**
		* Constructor for creating a transistor
		*
		* @param pin: Pointer to the pin of the transistor
		* @param pud: the to be checked PUD value
		*/
		Transistor(const pin::Pin* pin, TRANSISTOR_TYPE type);

		/**
		* Constructor for creating a transistor
		*
		* @param pin: GPIO pin number of the transistor
		* @param pud: the to be checked PUD value
		*/
		Transistor(int8_t pin, TRANSISTOR_TYPE type, rpicomponents::pin::utils::PIN_MODE mode);

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
		void TurnOn(int16_t value) const;

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
	};
}

#endif