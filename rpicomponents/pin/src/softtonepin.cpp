#include "softtonepin.hpp"



rpicomponents::pin::SofttonePin::SofttonePin(int pin, int maxOutputValue) : Pin(pin, rpicomponents::pin::SOFTTONE_MODE, maxOutputValue) 
{
	OutputOff();
}

//rpicomponents::pin::SofttonePin::SofttonePin(int&& pin, int&& maxOutputValue) : Pin(pin, rpicomponents::pin::SOFTTONE_MODE, maxOutputValue)
//{
//	OutputOff();
//}

rpicomponents::pin::SofttonePin::SofttonePin(const SofttonePin& pin) : Pin(pin.GetPin())
{
	OutputOff();
}


void rpicomponents::pin::SofttonePin::WriteToPin(int value) const {
	if (!CheckInputValue(value)) return;
	softToneWrite(pin_, value);
	status_.store(value);
}

int rpicomponents::pin::SofttonePin::ReadFromPin() const {
	auto val = status_.load();
	return val;
}