#include "pin.hpp"

using namespace std;
using namespace rpicomponents;
using namespace rpicomponents::pin;


int Pin::GetPin() const {
	return pin_;
}

bool Pin::IsOn() {
	mutex mtx;
	std::lock_guard<std::mutex> lck{ mtx };
	if (status_ == min_value_) return false;
	return true;
}

void Pin::OutputOn() {
	mutex mtx;
	std::lock_guard<std::mutex> lck{ mtx };
	WriteToPin(max_value_);
}

void Pin::Output(int value) {
	mutex mtx;
	std::lock_guard<std::mutex> lck{ mtx };
	WriteToPin(value);
}

void Pin::OutputOff() {
	mutex mtx;
	std::lock_guard<std::mutex> lck{ mtx };
	WriteToPin(min_value_);
}

bool Pin::CheckInputValue(int value) {
	if (value < min_value_ || value > max_value_) {
		return false;
	}
	return true;
}

Pin::Pin(int pin, int mode, int maxValue) : pin_{ pin }, mode_{ mode }, max_value_{ maxValue } {
	if (!PinChecker::IsValidPinValue(pin)) {
		throw invalid_argument("pin integer cannot be below " + to_string(PIN_MIN_VALUE) + " or above " + to_string(PIN_MAX_VALUE));
	}
	if (!PinChecker::IsValidOutputMode(mode)) {
		throw invalid_argument("Output mode must be DIGITAL, PWM, SOFTPWM or SOFTTONE");
	}
	if (maxValue < 1) {
		throw invalid_argument("Max value must be greater than 0");
	}
	if (mode == DIGITAL_MODE && maxValue != DIGITAL_MODE_MAX_VAL) {
		throw invalid_argument("DIGITAL_MODE max value cannot be anything else than 1");
	}
	if (mode == PWM_MODE && maxValue != PWM_MODE_MAX_VAL) {
		throw invalid_argument("PWM_MODE max value cannot be anything else than 1023");
	}
	if (mode == PWM_MODE && !PinChecker::PinIsHardwarePWMCapable(pin)) {
		throw invalid_argument("PWM_MODE cannot be used with input pin! Valid pins are: " + to_string(PWM_CHANNEL0_PIN1) + ", "
			+ to_string(PWM_CHANNEL0_PIN2) + "for channel 0 and " + to_string(PWM_CHANNEL1_PIN1) + ", "
			+ to_string(PWM_CHANNEL1_PIN2) + "for channel 1");
	}
	try {
		wiringPiSetup();
	}
	catch (exception e) {
		throw e;
	}
}
