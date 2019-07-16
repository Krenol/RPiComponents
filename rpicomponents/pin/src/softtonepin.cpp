#include "softtonepin.hpp"



rpicomponents::pin::SofttonePin::SofttonePin(int8_t pin, int16_t maxOutputValue) : Pin(pin, rpicomponents::pin::utils::SOFTTONE_MODE, maxOutputValue) {
	OutputOff();
}

void rpicomponents::pin::SofttonePin::WriteToPin(int16_t value) const {
	if (!CheckInputValue(value)) return;
	std::lock_guard<std::mutex> lockGuard(mtx_);
	softToneWrite(pin_, value);
	status_ = value; //wouldn't need a lock, as it is atomic
}

int16_t rpicomponents::pin::SofttonePin::ReadFromPin() const {
	return status_;
}