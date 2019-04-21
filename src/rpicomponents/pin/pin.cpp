#include "pin.hpp"

using namespace std;
using namespace rpicomponents;
using namespace rpicomponents::pin;

int Pin::GetPin() const {

}

bool Pin::IsOn() {
	if (status_ == min_value_) return false;
	return true;
}

void Pin::OutputOn() {
	WriteToPin(max_value_);
	status_ = max_value_;
}

void Pin::Output(int value) {
	if (value < min_value_) {
		printf("invalid input detected. Given value was below min value. Setting input value to min value!");
		value = min_value_;
	}
	else if (value > max_value_) {
		printf("invalid input detected. Given value was above max value. Setting input value to max value!");
		value = max_value_;
	}

	WriteToPin(value);
	status_ = value;
}

void Pin::OutputOff() {
	WriteToPin(min_value_);
	status_ = min_value_;
}


Pin::Pin(int pin, int mode, int maxValue) : pin_{ pin }, mode_{ mode }, max_value_{ maxValue } {
	if (PinChecker::IsValidPinValue(pin)) {
		invalid_argument("pin integer cannot be below " + to_string(PIN_MIN_VALUE) + " or above " + to_string(PIN_MAX_VALUE));
	}
	if (PinChecker::IsValidOutputMode(mode)) {
		invalid_argument("Output mode must be DIGITAL, PWM, SOFTPWM or SOFTTONE");
	}
	if (maxValue < 1) {
		invalid_argument("Max value must be greater than 0");
	}
	if (mode == DIGITAL_MODE && maxValue != DIGITAL_MODE_MAX_VAL) {
		invalid_argument("DIGITAL_MODE max value cannot be anything else than 1");
	}
	if (mode == PWM_MODE && maxValue != PWM_MODE_MAX_VAL) {
		invalid_argument("PWM_MODE max value cannot be anything else than 1023");
	}
	if (mode == PWM_MODE && !PinChecker::PinIsHardwarePWMCapable(pin)) {
		invalid_argument("PWM_MODE cannot be used with input pin! Valid pins are: " + to_string(PWM_CHANNEL0_PIN1) + ", "
			+ to_string(PWM_CHANNEL0_PIN2) + "for channel 0 and " + to_string(PWM_CHANNEL1_PIN1) + ", "
			+ to_string(PWM_CHANNEL1_PIN2) + "for channel 1");
	}
}
