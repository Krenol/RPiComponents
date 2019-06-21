#include "component.hpp"

#ifndef RPICOMPONENTS_LED_H
#define RPICOMPONENTS_LED_H

namespace rpicomponents {
	class Led : public Component {
	private:
		const pin::Pin* pin_; //the used pin of the LED
		const bool on_mode_{ true }; //the on_mode_ of the pin

		/**
		* Initializer for Constructors; reduce redundancy
		*/
		void Initialize();

	public:
		/**
		* Constructor for creating a LED
		*
		* @param pin: pin pointer to the LED's pin
		* @param onIfPinOn: bool if LED light is on if pin output is on
		*/
		Led(const pin::Pin* pin, bool onIfPinOn = true);

		/**
		* Constructor for creating a LED
		*
		* @param pin: GPIO pin number to the LED's pin
		* @param outputMode: The output mode of the LED pin
		* @param onIfPinOn: bool if LED light is on if pin output is on
		*/
		Led(int8_t pin, pin::utils::PIN_MODE mode, bool onIfPinOn = true);

		/**
		* Turn the LED on to the maximum output value of the pin's output mode
		*/
		void TurnOn() const;

		/**
		* Turn on the LED pin to a specific value (obsolete if digital pin)
		*
		* @param value: Output value of the pin
		*/
		void TurnOn(int16_t value) const;

		/**
		* Turn the led off
		*/
		void TurnOff() const;

		/**
		* Method to find out if LED is on or off
		*
		* @return true if LED is on else false
		*/
		bool IsOn() const;
	};
}

#endif