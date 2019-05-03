#include "component.hpp"

#ifndef RPICOMPONENTS_COMPONENT_LED_H
#define RPICOMPONENTS_COMPONENT_LED_H

namespace rpicomponents {
	namespace component {
		class Led : public Component {
		private:
			pin::Pin* pin_; //the used pin of the LED
			bool on_mode_{ true }; //the on_mode_ of the pin

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
			Led(pin::Pin* pin, bool onIfPinOn = true);

			/**
			 * Constructor for creating a LED
			 *
			 * @param pin: GPIO pin number to the LED's pin
			 * @param outputMode: The output mode of the LED pin
			 * @param onIfPinOn: bool if LED light is on if pin output is on
			 */
			Led(int pin, pin::PIN_MODE outputMode, bool onIfPinOn = true);

			/**
			 * Turn the LED on to the maximum output value of the pin's output mode
			 */
			void TurnOn();

			/**
			 * Turn on the LED pin to a specific value (obsolete if digital pin)
			 *
			 * @param value: Output value of the pin
			 */
			void TurnOn(int value);

			/**
			 * Turn the led off
			 */
			void TurnOff();

			/**
			 * Method to find out if LED is on or off
			 *
			 * @return true if LED is on else false
			 */
			bool IsOn();
		};
	}
}

#endif