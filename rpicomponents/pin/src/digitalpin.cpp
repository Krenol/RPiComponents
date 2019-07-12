#include "digitalpin.hpp"



using namespace rpicomponents::pin;
using namespace rpicomponents::pin::utils;


DigitalPin::DigitalPin(int8_t pin) : Pin(pin, DIGITAL_MODE, DIGITAL_MODE_MAX_VAL) {
	OutputOff();
}

void DigitalPin::WriteToPin(int16_t value) const {
	if (!CheckInputValue(value)) return;
	//lock function to not cause any overhead on pin writings
	std::lock_guard<std::mutex> lockGuard(mtx_);
	digitalWrite(pin_, value);
	status_ = value; //wouldn't need a lock, as it is atomic
}

int16_t DigitalPin::ReadFromPin() const {
	return status_;
}