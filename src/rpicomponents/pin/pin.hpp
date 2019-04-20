#ifndef RPICOMPONENTS_PIN_H
#define RPICOMPONENTS_PIN_H
#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include <iomanip>

namespace rpicomponents {
	namespace pin {
		//define the a pin can have
		constexpr auto DIGITAL_MODE = 0, PWM_MODE = 1, SOFTPWM_MODE = 2, SOFTTONE_MODE = 3;
		//define gpio pins for pi 3b and 3b+
		constexpr auto GPIO17 = 0, GPIO18 = 1, GPIO27 = 2, GPIO22 = 3, GPIO23 = 4, GPIO24 = 5, GPIO25 = 6, GPIO4 = 7, SDA1 = 8,
			GPIO2 = 8, SCL1 = 9, GPIO3 = 9, CE0 = 10, GPIO8 = 10, CE1 = 11, GPIO7 = 11, MOSI = 12, PIO10 = 12, MISO = 13,
			GPIO9 = 13, SCLK = 14, GPIO11 = 14, TXD0 = 15, GPIO14 = 15, RXD0 = 16, GPIO15 = 16, GPIO5 = 21, GPIO6 = 22, GPIO13 = 23,
			GPIO19 = 24, GPIO26 = 25, GPIO12 = 26, GPIO16 = 27, CE2 = 27, GPIO20 = 28, GPIO21 = 29, GPIO0 = 30, SDA0 = 30, ID_SD = 30,
			GPIO1 = 31, SCL0 = 31, ID_SC = 31;
		//the HW PWM channel pins (channel 0 and channel 1)
		constexpr auto PWM_CHANNEL0_PIN1 = 1, PWM_CHANNEL0_PIN2 = 26, PWM_CHANNEL1_PIN1 = 23, PWM_CHANNEL1_PIN2 = 24;

		class Pin {
		public:
			static bool PinIsHardwarePWMCapable(int pin);
			static bool ValidOutputMode(int outMode);
			static bool IsI2CAddress(int address);
			static std::string GetHexAddress(int address);

		private:
			Pin() {}
		};
	}
}


#endif