#include "softtonepin.hpp"


using namespace rpicomponents;
using namespace rpicomponents::pin;
using namespace rpicomponents::pin::utils;


SofttonePin::SofttonePin(int8_t pin, int16_t maxOutputValue) : Pin(pin, SOFTTONE_MODE, maxOutputValue) {
	OutputOff();
}

void SofttonePin::WriteToPin(int16_t value) const {
	if (!CheckInputValue(value)) return;
	std::lock_guard<std::mutex> lockGuard(mtx_);
	softToneWrite(pin_, value);
	status_ = value; //wouldn't need a lock, as it is atomic
}

int16_t SofttonePin::ReadFromPin() const {
	return status_;
}