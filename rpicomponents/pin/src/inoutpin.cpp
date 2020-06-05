#include "inoutpin.hpp"


rpicomponents::pin::InOutPin::InOutPin(int pin) : Pin(pin, rpicomponents::pin::IN_OUT_MODE, rpicomponents::pin::DIGITAL_MODE_MAX_VAL)
{
	OutputOff();
}

rpicomponents::pin::InOutPin::InOutPin(InOutPin& pin) : Pin(pin.GetPin(), rpicomponents::pin::IN_OUT_MODE, rpicomponents::pin::DIGITAL_MODE_MAX_VAL)
{
	OutputOff();
}

void rpicomponents::pin::InOutPin::WriteToPin(int value)
{
	if (!CheckInputValue(value)) return;
	pinMode(pin_, OUTPUT);
	digitalWrite(pin_, value);
	status_.store(value); 
}

int rpicomponents::pin::InOutPin::ReadFromPin()
{
	pinMode(pin_, INPUT);
	auto value = digitalRead(pin_);
	return value;
}
