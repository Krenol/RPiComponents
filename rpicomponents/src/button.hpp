#include "component.hpp"

#ifndef RPICOMPONENTS_BUTTON_H
#define RPICOMPONENTS_BUTTON_H

namespace rpicomponents {
	constexpr const char* COMPONENT_BUTTON = "button";
	class Button : public Component {
	private:
		const std::unique_ptr<pin::Pin> pin_; //the used pin of the button
		const int pud_{ PUD_UP }; //the pud mode of the button

		/*
		Initializer for Constructors; reduce redundancy
		*/
        void Initialize();

		/**
		* Method to check if a given PUD value is valid
		*
		* @param pud: the to be checked PUD value
		* @returns true if PUD is valid, else false
		*/
		bool IsPUD(int pud) const;

	public:
		/**
		* Constructor for creating a button
		*
		* @param pin: GPIO pin number of the button
		* @param pud: the to be checked PUD value
		*/
		Button(int pin, int pud = PUD_UP);

		/**
		* Constructor for creating a button
		*
		* @param pin: GPIO pin number of the button
		* @param pud: the to be checked PUD value
		*/
		//Button(int&& pin, int&& pud = PUD_UP);

		/**
		* Copy Constructor
		*
		* @param button: The button to be copied
		*/
		Button(const Button &button);

		/**
		* Method to check if the button is currently pressed
		*
		* @returns true if button is pressed according to the pin's output value & PUD value, else false
		*/
		bool IsPressed() const;

		/**
		* Method to get the  PUD of the button
		*
		* @returns the int of the defined PUD by the wiringPi library
		*/
		int GetPUD() const;

		/*
		* Method to get the used pin
		*
		* @returns the used pin of the component
		*/
		int GetPin() const;
	};
}

#endif
