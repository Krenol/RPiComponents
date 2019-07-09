#include "softpwmpin.hpp"


using namespace rpicomponents;
using namespace rpicomponents::pin;
using namespace rpicomponents::pin::utils;

SoftPWMPin::SoftPWMPin(int8_t pin, int16_t maxOutputValue) : Pin(pin, SOFTPWM_MODE, maxOutputValue) {
	OutputOff();
}

void SoftPWMPin::WriteToPin(int16_t value) const {
	if (!CheckInputValue(value)) return;
	std::lock_guard<std::mutex> lockGuard(mtx_);
	softPwmWrite(pin_, value);
	status_ = value; //wouldn't need a lock, as it is atomic
}

int16_t SoftPWMPin::ReadFromPin() const {
	return status_;
}