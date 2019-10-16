#include "component.hpp"

#ifndef RPICOMPONENTS_LED_H
#define RPICOMPONENTS_LED_H

namespace rpicomponents {
	constexpr const char* COMPONENT_LED = "led";
	class Led : public Component {
	private:
		const std::unique_ptr<pin::Pin> pin_; //the used pin of the LED
		const bool on_mode_{ true }; //the on_mode_ of the pin

		/**
		* Initializer for Constructors; reduce redundancy
		*/
		void Initialize();

	public:

		/**
		* Constructor for creating a LED
		*
		* @param pin: GPIO pin number to the LED's pin
		* @param outputMode: The output mode of the LED pin
		* @param onIfPinOn: bool if LED light is on if pin output is on
		*/
		Led(const int& pin, const rpicomponents::pin::PIN_MODE& mode, const bool& onIfPinOn = true);

		/**
		* Constructor for creating a LED
		*
		* @param pin: GPIO pin number to the LED's pin
		* @param outputMode: The output mode of the LED pin
		* @param onIfPinOn: bool if LED light is on if pin output is on
		*/
		Led(int&& pin, rpicomponents::pin::PIN_MODE&& mode, bool&& onIfPinOn = true);

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
		void TurnOn(const int& value) const;

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
		* @returns the used pin of the component
		*/
		const int& GetPin() const;

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
		const rpicomponents::pin::PIN_MODE& GetPinMode() const;
	};
}

#endif