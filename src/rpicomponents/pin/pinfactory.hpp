#ifndef RPICOMPONENTS_PIN_PIN_FACTORY_H
#define RPICOMPONENTS_PIN_PIN_FACTORY_H
#pragma once

#include "digitalpin.hpp"
#include "pwmpin.hpp"
#include "softpwmpin.hpp"
#include "softtonepin.hpp"
#include "pin.hpp"
#include <map>

namespace rpicomponents {
	namespace pin {
		class PinFactory {
		public:
			static Pin* CreatePin(int pin, OUTPUT_MODE outputMode = DIGITAL, int maxOutputValue = DIGITAL_MODE_MAX_VAL);
			static bool RemovePin(Pin* pin); //thread safe
			static bool RemovePin(int pin); //thread safe
			static Pin* LoadPin(int pin); //thread safe
			~PinFactory();

		private:
			static bool PinExists(int pin); //not thread safe
			static void AddPinToMap(Pin* pin); //not thread safe
			PinFactory() {} //make class static by private Constructor

			static std::map<int, Pin*> created_pins_;
			static std::mutex mtx_;
		};
	}
}


#endif