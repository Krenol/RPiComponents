#include "softpwmpin.hpp"


rpicomponents::pin::SoftPWMPin::SoftPWMPin(const int &pin, const int &maxOutputValue) : Pin(pin, rpicomponents::pin::SOFTPWM_MODE, maxOutputValue) 
{
	OutputOff();
}

rpicomponents::pin::SoftPWMPin::SoftPWMPin(int&& pin, int&& maxOutputValue) : Pin(pin, rpicomponents::pin::SOFTPWM_MODE, maxOutputValue)
{
	OutputOff();
}

rpicomponents::pin::SoftPWMPin::SoftPWMPin(const SoftPWMPin& pin) : Pin(pin)
{
	OutputOff();
}

void rpicomponents::pin::SoftPWMPin::WriteToPin(const int& value) const {
	if (!CheckInputValue(value)) return;
	std::lock_guard<std::mutex> lockGuard(mtx_);
	softPwmWrite(pin_, value);
	status_ = value; //wouldn't need a lock, as it is atomic
}

int rpicomponents::pin::SoftPWMPin::ReadFromPin() const {
	return status_;
}