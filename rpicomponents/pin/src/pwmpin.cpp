#include "pwmpin.hpp"


rpicomponents::pin::PWMPin::PWMPin(int pin) : Pin(pin, rpicomponents::pin::PWM_MODE, rpicomponents::pin::PWM_MODE_MAX_VAL) 
{
	OutputOff();
}

//rpicomponents::pin::PWMPin::PWMPin(int&& pin) : Pin(pin, rpicomponents::pin::PWM_MODE, rpicomponents::pin::PWM_MODE_MAX_VAL)
//{
//	OutputOff();
//}

rpicomponents::pin::PWMPin::PWMPin(const PWMPin& pin) : Pin(pin)
{
	OutputOff();
}


void rpicomponents::pin::PWMPin::WriteToPin(int value) {
	if (!CheckInputValue(value)) return;
	pwmWrite(pin_, value);
	status_.store(value); 
}

int rpicomponents::pin::PWMPin::ReadFromPin() {
	auto val = status_.load();
	return val;
}
