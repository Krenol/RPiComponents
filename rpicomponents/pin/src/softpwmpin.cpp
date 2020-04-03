#include "softpwmpin.hpp"


rpicomponents::pin::SoftPWMPin::SoftPWMPin(int pin, int maxOutputValue) : Pin(pin, rpicomponents::pin::SOFTPWM_MODE, maxOutputValue) 
{
	OutputOff();
}

//rpicomponents::pin::SoftPWMPin::SoftPWMPin(int&& pin, int&& maxOutputValue) : Pin(pin, rpicomponents::pin::SOFTPWM_MODE, maxOutputValue)
//{
//	OutputOff();
//}

rpicomponents::pin::SoftPWMPin::SoftPWMPin(const SoftPWMPin& pin) : Pin(pin)
{
	OutputOff();
}

void rpicomponents::pin::SoftPWMPin::WriteToPin(int value) {
	if (!CheckInputValue(value)) return;
	softPwmWrite(pin_, value);
	status_.store(value); 
}

int rpicomponents::pin::SoftPWMPin::ReadFromPin() {
	auto val = status_.load();
	return val;
}
