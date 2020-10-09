#include "component.hpp"

#ifndef RPICOMPONENTS_LED_H
#define RPICOMPONENTS_LED_H

namespace rpicomponents {
	constexpr const char* COMPONENT_LED = "led";
	class Led : public Component {
	private:
		std::unique_ptr<pin::Pin> pin_; //the used pin of the LED
		const bool on_mode_{ true }; //the on_mode_ of the pin

		/**
		* Initializer for Constructors; reduce redundancy
		*/
		void Initialize();

	public:

		/**
		* Constructor for creating a LED
		*
		* @param pin: GPIO pin of the LED's pin
		* @param pin_mode: The mode of the pin, e.g. DIGITAL_MODE
		* @param pin_max_val: The max outout value of the pin, e.g. 1
		* @param onIfPinOn: bool if LED light is on if pin output is on
		*/
		Led(int pin, pin::PIN_MODE pin_mode, int pin_max_val, bool onIfPinOn = true);

		/**
		* Constructor for creating a LED
		*
		* @param pin_data: GPIO pin of the LED's pin
		* @param onIfPinOn: bool if LED light is on if pin output is on
		*/
		Led(const pin::pin_data& pindata, bool onIfPinOn = true);

		/**
		* Copy Constructor
		*
		* @param led Led to be copied
		*/
		Led(const Led& led);

		/**
		* Turn the LED on to the maximum output value of the pin's output mode
		*/
		void TurnOn() const;

		/**
		* Turn on the LED pin to a specific value (obsolete if digital pin)
		*
		* @param value: Output value of the pin
		*/
		void TurnOn(int value) const;

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

		/*
		* Method to get the used pin
		*
		* @returns the pin of the component
		*/
		int GetPin() const;

		/*
		* Method to check if led is on if gpio pin has power
		*
		* @returns true if led is on if pin has power else false
		*/
		bool IsOnIfPinHasPower() const;

		/*
		* Method to get the pin mode of the led pin
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

		/*
		* Method to get the pin_data
		*
		* @returns the pin_data struct
		*/
		const pin::pin_data& GetPinData() const;
	};
}

#endif