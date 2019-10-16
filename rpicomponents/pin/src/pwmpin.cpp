#include "pwmpin.hpp"


rpicomponents::pin::PWMPin::PWMPin(const int &pin) : Pin(pin, rpicomponents::pin::PWM_MODE, rpicomponents::pin::PWM_MODE_MAX_VAL) 
{
	OutputOff();
}

rpicomponents::pin::PWMPin::PWMPin(int&& pin) : Pin(pin, rpicomponents::pin::PWM_MODE, rpicomponents::pin::PWM_MODE_MAX_VAL)
{
	OutputOff();
}

rpicomponents::pin::PWMPin::PWMPin(const PWMPin& pin) : Pin(pin)
{
	OutputOff();
}


void rpicomponents::pin::PWMPin::WriteToPin(const int& value) const {
	if (!CheckInputValue(value)) return;
	std::lock_guard<std::mutex> lockGuard(mtx_);
	pwmWrite(pin_, value);
	status_ = value; //wouldn't need a lock, as it is atomic
}

int rpicomponents::pin::PWMPin::ReadFromPin() const {
	return status_;
}