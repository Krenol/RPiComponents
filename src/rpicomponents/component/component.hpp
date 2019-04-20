#ifndef RPICOMPONENTS_COMPONENT_H
#define RPICOMPONENTS_COMPONENT_H
#pragma once

#include <wiringPi.h>
#include <string>
#include <vector>
#include <stdexcept>
#include <softPwm.h>
#include <softTone.h>
#include <math.h>
#include <iomanip>
#include <algorithm>
#include "../pin/pin.hpp"


namespace rpicomponents {
	namespace component {
		class Component {
		private:
			virtual ~Component() = 0; //virtual private destructor to make class abstract
			std::vector<int> used_pins_{ };
			const std::string component_name_{ "component" };
			std::vector<int>::iterator GetPinIterator(int pin);
			bool UsesPin(std::vector<int>::iterator pinIterator);

		protected:
			void AddPin(int pin);
			void AddPins(std::vector<int> pins);
			bool RemoveAllPins();
			bool RemovePin(int pin);
			Component(std::string componentName) : component_name_{ componentName }
			{
			}
			
		public:
			bool UsesPin(int pin);
			bool UsesPins(vector<int> pins);
			std::string ToString();
		};
	}
}

#endif