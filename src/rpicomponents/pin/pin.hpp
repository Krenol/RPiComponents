#ifndef RPICOMPONENTS_PIN_H
#define RPICOMPONENTS_PIN_H
#pragma once

#include "pinchecker.hpp"
#include <wiringPi.h>

namespace rpicomponents {
	namespace pin {
		class Pin {
		public:
			int GetPin() const;
			bool IsOn();
			void OutputOn();
			void Output(int value);
			void OutputOff();

		protected:
			Pin(int pin, int mode = DIGITAL_MODE, int maxValue = DIGITAL_MODE_MAX_VAL);
			virtual void WriteToPin(int value) = 0;

		private:
			const int pin_{ GPIO17 }, mode_ = { DIGITAL_MODE }, max_value_{ DIGITAL_MODE_MAX_VAL }, min_value_{ 0 };
			mutable int status_{ 0 };
		};
	}
}


#endif