#include "pwmpin.hpp"


rpicomponents::pin::PWMPin::PWMPin(int8_t pin) : Pin(pin, rpicomponents::pin::PWM_MODE, rpicomponents::pin::PWM_MODE_MAX_VAL) 
{
	OutputOff();
}

rpicomponents::pin::PWMPin::PWMPin(int8_t&& pin) : Pin(pin, rpicomponents::pin::PWM_MODE, rpicomponents::pin::PWM_MODE_MAX_VAL)
{
	OutputOff();
}

rpicomponents::pin::PWMPin::PWMPin(PWMPin& pin) : Pin(pin.GetPin(), rpicomponents::pin::PWM_MODE,pin.max_value_)
{
	OutputOff();
}

rpicomponents::pin::PWMPin::PWMPin(PWMPin&& pin) : Pin(pin.GetPin(), rpicomponents::pin::PWM_MODE, pin.max_value_)
{
	OutputOff();
}

void rpicomponents::pin::PWMPin::WriteToPin(int16_t value) const {
	if (!CheckInputValue(value)) return;
	std::lock_guard<std::mutex> lockGuard(mtx_);
	pwmWrite(pin_, value);
	status_ = value; //wouldn't need a lock, as it is atomic
}

int16_t rpicomponents::pin::PWMPin::ReadFromPin() const {
	return status_;
}