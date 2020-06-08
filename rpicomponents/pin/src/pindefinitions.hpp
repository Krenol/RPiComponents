#ifndef RPICOMPONENTS_PIN_PINDEFINITIONS_H
#define RPICOMPONENTS_PIN_PINDEFINITIONS_H
#pragma once

#include <cstdint>
#include <map>
#include <string>
#include <algorithm>

namespace rpicomponents {
	namespace pin {
		enum PIN_MODE {
			DIGITAL_MODE, PWM_MODE, SOFTPWM_MODE, SOFTTONE_MODE, INPUT_MODE, IN_OUT_MODE
		};
		//define gpio pins for pi 3b and 3b+
		constexpr int GPIO17 = 0, GPIO18 = 1, GPIO27 = 2, GPIO22 = 3, GPIO23 = 4, GPIO24 = 5, GPIO25 = 6, GPIO4 = 7, SDA1 = 8,
			GPIO2 = 8, SCL1 = 9, GPIO3 = 9, CE0 = 10, GPIO8 = 10, CE1 = 11, GPIO7 = 11, MOSI = 12, GPIO10 = 12, MISO = 13,
			GPIO9 = 13, SCLK = 14, GPIO11 = 14, TXD0 = 15, GPIO14 = 15, RXD0 = 16, GPIO15 = 16, GPIO5 = 21, GPIO6 = 22, GPIO13 = 23,
			GPIO19 = 24, GPIO26 = 25, GPIO12 = 26, GPIO16 = 27, CE2 = 27, GPIO20 = 28, GPIO21 = 29, GPIO0 = 30, SDA0 = 30, ID_SD = 30,
			GPIO1 = 31, SCL0 = 31, ID_SC = 31, PIN_MIN_VALUE = 0, PIN_MAX_VALUE = 31;
		//the HW PWM channel pins (channel 0 and channel 1)
		constexpr int PWM_CHANNEL0_PIN1 = 1, PWM_CHANNEL0_PIN2 = 26, PWM_CHANNEL1_PIN1 = 23, PWM_CHANNEL1_PIN2 = 24;
		constexpr int DIGITAL_MODE_MAX_VAL = 1, PWM_MODE_MAX_VAL = 1023;

		static const std::map<std::string, int> GPIO_MAP = { 
			{"GPIO17", GPIO17}, 
			{"GPIO18", GPIO18}, 
			{"GPIO27", GPIO27},  
			{"GPIO22", GPIO22},
			{"GPIO23", GPIO23},
			{"GPIO24", GPIO24},
			{"GPIO25", GPIO25},
			{"GPIO4", GPIO4},
			{"SDA1", SDA1},
			{"GPIO2", GPIO2},
			{"SCL1", SCL1},
			{"GPIO3", GPIO3},
			{"CE0", CE0},
			{"GPIO8", GPIO8},
			{"CE1", CE1},
			{"GPIO7", GPIO7},
			{"MOSI", MOSI},
			{"GPIO10", GPIO10},
			{"MISO", MISO},
			{"GPIO9", GPIO9},
			{"SCLK", SCLK},
			{"GPIO11", GPIO11},
			{"TXD0", TXD0},
			{"GPIO14", GPIO14},
			{"RXD0", RXD0},
			{"GPIO15", GPIO15},
			{"GPIO5", GPIO5},
			{"GPIO6", GPIO6},
			{"GPIO13", GPIO13},
			{"GPIO19", GPIO19},
			{"GPIO26", GPIO26},
			{"GPIO12", GPIO12},
			{"GPIO16", GPIO16},
			{"CE2", CE2},
			{"GPIO20", GPIO20},
			{"GPIO21", GPIO21},
			{"GPIO0", GPIO0},
			{"SDA0", SDA0},
			{"ID_SD", ID_SD},
			{"GPIO1", GPIO1},
			{"SCL0", SCL0},
			{"ID_SC", ID_SC},
			{"GPIO14", GPIO14}
		};
		
		/*
		Method to load the pin number from the GPIO_MAP
		Transforms input string to upper case

		@param name: The pin name for which id is to be found
		@returns -1 if pin name not found; else pin id between 0 and 31 matching the given name
		*/
		static int getPinId(const std::string &name) {
			std::string str;
			std::transform(name.begin(), name.end(), str.begin(), ::toupper);
			int id;
			try{
				id = GPIO_MAP.at(str);
			} catch(...) {
				id = -1;
			}
			return id;
		}
	}
	
}

#endif
