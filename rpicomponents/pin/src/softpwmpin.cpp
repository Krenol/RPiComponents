#include "softpwmpin.hpp"


rpicomponents::pin::SoftPWMPin::SoftPWMPin(int8_t pin, int16_t maxOutputValue) : Pin(pin, rpicomponents::pin::SOFTPWM_MODE, maxOutputValue) {
	OutputOff();
}

void rpicomponents::pin::SoftPWMPin::WriteToPin(int16_t value) const {
	if (!CheckInputValue(value)) return;
	std::lock_guard<std::mutex> lockGuard(mtx_);
	softPwmWrite(pin_, value);
	status_ = value; //wouldn't need a lock, as it is atomic
}

int16_t rpicomponents::pin::SoftPWMPin::ReadFromPin() const {
	return status_;
}