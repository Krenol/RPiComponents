#include "pin.hpp"



int8_t rpicomponents::pin::Pin::GetPin() const {
	return pin_;
}

bool rpicomponents::pin::Pin::IsOn() const {
	auto status = ReadFromPin();
	if (status == min_value_) return false;
	return true;
}

void rpicomponents::pin::Pin::OutputOn() const {
	if (mode_ == rpicomponents::pin::utils::INPUT_MODE) return;
	WriteToPin(max_value_);
}

void rpicomponents::pin::Pin::Output(int value) const {
	if (mode_ == rpicomponents::pin::utils::INPUT_MODE) return;
	WriteToPin(value);
}

void rpicomponents::pin::Pin::OutputOff() const {
	if (mode_ == rpicomponents::pin::utils::INPUT_MODE) return;
	WriteToPin(min_value_);
}

int16_t rpicomponents::pin::Pin::ReadPinValue() const {
	return ReadFromPin();
}

bool rpicomponents::pin::Pin::CheckInputValue(int16_t value) const {
	if (value < min_value_ || value > max_value_) {
		return false;
	}
	return true;
}

rpicomponents::pin::utils::PIN_MODE rpicomponents::pin::Pin::OutputMode() const {
	return mode_;
}

rpicomponents::pin::Pin::Pin(int8_t pin, rpicomponents::pin::utils::PIN_MODE mode, int16_t maxOutputValue) : pin_{ pin }, mode_{ mode }, max_value_{ maxOutputValue } {
    try {
        wiringPiSetup();
    }
    catch (std::exception e) {
        throw e;
    }
	if (!rpicomponents::pin::utils::PinChecker::IsValidPinValue(pin)) {
		throw std::invalid_argument("pin integer cannot be below " + std::to_string(rpicomponents::pin::utils::PIN_MIN_VALUE) + " or above " + 
			std::to_string(rpicomponents::pin::utils::PIN_MAX_VALUE));
	}
	if (maxOutputValue < 1) {
		throw std::invalid_argument("Max value must be greater than 0");
	}
	if (mode == rpicomponents::pin::utils::DIGITAL_MODE && maxOutputValue != rpicomponents::pin::utils::DIGITAL_MODE_MAX_VAL) {
		throw std::invalid_argument("DIGITAL_MODE max value cannot be anything else than 1");
	}
	if (mode == rpicomponents::pin::utils::PWM_MODE && maxOutputValue != rpicomponents::pin::utils::PWM_MODE_MAX_VAL) {
		throw std::invalid_argument("PWM_MODE max value cannot be anything else than 1023");
	}
	if (mode == rpicomponents::pin::utils::PWM_MODE && !rpicomponents::pin::utils::PinChecker::PinIsHardwarePWMCapable(pin)) {
		throw std::invalid_argument("PWM_MODE cannot be used with input pin! Valid pins are: " + std::to_string(rpicomponents::pin::utils::PWM_CHANNEL0_PIN1) + ", "
			+ std::to_string(rpicomponents::pin::utils::PWM_CHANNEL0_PIN2) + "for channel 0 and " + std::to_string(rpicomponents::pin::utils::PWM_CHANNEL1_PIN1) + ", "
			+ std::to_string(rpicomponents::pin::utils::PWM_CHANNEL1_PIN2) + "for channel 1");
	}
	if (mode == rpicomponents::pin::utils::IN_OUT_MODE && maxOutputValue != rpicomponents::pin::utils::DIGITAL_MODE_MAX_VAL) {
		throw std::invalid_argument("IN_OUT_MODE max value cannot be anything else than 1");
		return; //no need to set the pin as in or output
	}
	if (mode == rpicomponents::pin::utils::INPUT_MODE) {
		pinMode(pin, INPUT);
	}
	else {
		pinMode(pin, OUTPUT);
	}
}
