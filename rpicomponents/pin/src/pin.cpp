#include "pin.hpp"
#include "pinchecker.hpp"


const int8_t& rpicomponents::pin::Pin::GetPin() const {
	return pin_;
}

bool rpicomponents::pin::Pin::IsOn() const {
	auto status = ReadFromPin();
	if (status == min_value_) return false;
	return true;
}

void rpicomponents::pin::Pin::OutputOn() const {
	if (mode_ == rpicomponents::pin::INPUT_MODE) return;
	WriteToPin(max_value_);
}

void rpicomponents::pin::Pin::Output(int value) const {
	if (mode_ == rpicomponents::pin::INPUT_MODE) return;
	WriteToPin(value);
}

void rpicomponents::pin::Pin::OutputOff() const {
	if (mode_ == rpicomponents::pin::INPUT_MODE) return;
	WriteToPin(min_value_);
}

int16_t rpicomponents::pin::Pin::GetMaxOutValue() const
{
	return max_value_;
}

int16_t rpicomponents::pin::Pin::ReadPinValue() const {
	return ReadFromPin();
}

rpicomponents::pin::Pin::Pin(int8_t&& pin, const PIN_MODE&& mode, const int16_t&& maxOutputValue) : pin_{ pin }, mode_{ mode }, max_value_{ maxOutputValue }
{
	Initialize();
}



rpicomponents::pin::Pin::Pin(const Pin& pin) : pin_{ pin.GetPin() }, mode_{ pin.mode_ }, max_value_{ pin.max_value_ }
{
	Initialize();
}

bool rpicomponents::pin::Pin::CheckInputValue(int16_t value) const {
	if (value < min_value_ || value > max_value_) {
		return false;
	}
	return true;
}

void rpicomponents::pin::Pin::Initialize() const
{
	try {
		wiringPiSetup();
	}
	catch (std::exception e) {
		throw e;
	}
	if (!rpicomponents::pin::PinChecker::IsValidPinValue(pin_)) {
		throw std::invalid_argument("pin integer cannot be below " + std::to_string(rpicomponents::pin::PIN_MIN_VALUE) + " or above " +
			std::to_string(rpicomponents::pin::PIN_MAX_VALUE));
	}
	if (max_value_ < 1) {
		throw std::invalid_argument("Max value must be greater than 0");
	}
	if (mode_ == rpicomponents::pin::DIGITAL_MODE && max_value_ != rpicomponents::pin::DIGITAL_MODE_MAX_VAL) {
		throw std::invalid_argument("DIGITAL_MODE max value cannot be anything else than 1");
	}
	if (mode_ == rpicomponents::pin::PWM_MODE && max_value_ != rpicomponents::pin::PWM_MODE_MAX_VAL) {
		throw std::invalid_argument("PWM_MODE max value cannot be anything else than 1023");
	}
	if (mode_ == rpicomponents::pin::PWM_MODE && !rpicomponents::pin::PinChecker::PinIsHardwarePWMCapable(pin_)) {
		throw std::invalid_argument("PWM_MODE cannot be used with input pin! Valid pins are: " + std::to_string(rpicomponents::pin::PWM_CHANNEL0_PIN1) + ", "
			+ std::to_string(rpicomponents::pin::PWM_CHANNEL0_PIN2) + "for channel 0 and " + std::to_string(rpicomponents::pin::PWM_CHANNEL1_PIN1) + ", "
			+ std::to_string(rpicomponents::pin::PWM_CHANNEL1_PIN2) + "for channel 1");
	}
	if (mode_ == rpicomponents::pin::IN_OUT_MODE && max_value_ != rpicomponents::pin::DIGITAL_MODE_MAX_VAL) {
		throw std::invalid_argument("IN_OUT_MODE max value cannot be anything else than 1");
		return; //no need to set the pin as in or output
	}
	if (mode_ == rpicomponents::pin::INPUT_MODE) {
		pinMode(pin_, INPUT);
	}
	else {
		pinMode(pin_, OUTPUT);
	}
}

const rpicomponents::pin::PIN_MODE& rpicomponents::pin::Pin::OutputMode() const {
	return mode_;
}

/*rpicomponents::pin::Pin::Pin(int8_t pin, rpicomponents::pin::PIN_MODE mode, int16_t maxOutputValue) : pin_{ pin }, mode_{ mode }, max_value_{ maxOutputValue } 
{
	Initialize();
}*/

rpicomponents::pin::Pin::Pin(const int8_t& pin, const PIN_MODE& mode, const int16_t& maxOutputValue) : pin_{ pin }, mode_{ mode }, max_value_{ maxOutputValue }
{
	Initialize();
}
