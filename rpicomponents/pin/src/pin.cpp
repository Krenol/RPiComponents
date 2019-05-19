#include "pin.hpp"

using namespace std;
using namespace rpicomponents;
using namespace rpicomponents::pin;
using namespace rpicomponents::pin::utils;

int Pin::GetPin() const {
	return pin_;
}

bool Pin::IsOn() const {
	auto status = ReadFromPin();
	if (status == min_value_) return false;
	return true;
}

void Pin::OutputOn() const {
	if (mode_ == INPUT_MODE) return;
	WriteToPin(max_value_);
}

void Pin::Output(int value) const {
	if (mode_ == INPUT_MODE) return;
	WriteToPin(value);
}

void Pin::OutputOff() const {
	if (mode_ == INPUT_MODE) return;
	WriteToPin(min_value_);
}

int Pin::ReadPinValue() const {
	return ReadFromPin();
}

bool Pin::CheckInputValue(int value) const {
	if (value < min_value_ || value > max_value_) {
		return false;
	}
	return true;
}

PIN_MODE Pin::OutputMode() const {
	return mode_;
}

Pin::Pin(int pin, PIN_MODE mode, int maxOutputValue) : pin_{ pin }, mode_{ mode }, max_value_{ maxOutputValue } {
    try {
        wiringPiSetup();
    }
    catch (exception e) {
        throw e;
    }
	if (!PinChecker::IsValidPinValue(pin)) {
		throw invalid_argument("pin integer cannot be below " + to_string(PIN_MIN_VALUE) + " or above " + to_string(PIN_MAX_VALUE));
	}
	if (maxOutputValue < 1) {
		throw invalid_argument("Max value must be greater than 0");
	}
	if (mode == DIGITAL_MODE && maxOutputValue != DIGITAL_MODE_MAX_VAL) {
		throw invalid_argument("DIGITAL_MODE max value cannot be anything else than 1");
	}
	if (mode == PWM_MODE && maxOutputValue != PWM_MODE_MAX_VAL) {
		throw invalid_argument("PWM_MODE max value cannot be anything else than 1023");
	}
	if (mode == PWM_MODE && !PinChecker::PinIsHardwarePWMCapable(pin)) {
		throw invalid_argument("PWM_MODE cannot be used with input pin! Valid pins are: " + to_string(PWM_CHANNEL0_PIN1) + ", "
			+ to_string(PWM_CHANNEL0_PIN2) + "for channel 0 and " + to_string(PWM_CHANNEL1_PIN1) + ", "
			+ to_string(PWM_CHANNEL1_PIN2) + "for channel 1");
	}
	if (mode == INPUT_MODE) {
		pinMode(pin, INPUT);
	}
	else {
		pinMode(pin, OUTPUT);
	}
}
