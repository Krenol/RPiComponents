#include "component.hpp"

#ifndef RPICOMPONENTS_BUTTON_H
#define RPICOMPONENTS_BUTTON_H

namespace rpicomponents {
	constexpr const char* COMPONENT_BUTTON = "button";
	class Button : public Component {
	private:
		std::unique_ptr<pin::Pin> pin_; //the used pin of the button
		const int pud_{ PI_PUD_UP }; //the pud mode of the button
		gpio_cb cb_;

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

		/**
		 * Alert function for gpioSetAlertFunc; 
		 * must be static to work
		 * @param gpio gpio pin nr
		 * @param level level at pin (0 for LOW, 1 for HIGH, 2 no change)
		 * @param tick ms since boot
		 * @param btn pointer to this button
		 */
		static void AlertFunction(int gpio, int level, uint32_t tick, void *btn);

	public:
		/**
		* Constructor for creating a button
		*
		* @param pin: GPIO pin number of the button
		* @param pud: the to be checked PUD value
		*/
		Button(int pin, int pud = PI_PUD_UP);

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

		/**
		 * Method to registera callback function to this component
		 * @param cb_func The callback function
		 */
		void RegisterCallback(const gpio_cb& cb_func);
	};
}

#endif
