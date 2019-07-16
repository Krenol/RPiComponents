#include "inputpin.hpp"

rpicomponents::pin::InputPin::InputPin(int8_t pin) : Pin(pin, rpicomponents::pin::utils::INPUT_MODE, rpicomponents::pin::utils::DIGITAL_MODE_MAX_VAL) {
	OutputOff();
}

void rpicomponents::pin::InputPin::WriteToPin(int16_t value) const {
	return;
}

int16_t rpicomponents::pin::InputPin::ReadFromPin() const {
	std::lock_guard<std::mutex> lockGuard(mtx_);
	auto val = digitalRead(pin_);
	return val;
}