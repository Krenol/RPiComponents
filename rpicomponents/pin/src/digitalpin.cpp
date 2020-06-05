#include "digitalpin.hpp"


rpicomponents::pin::DigitalPin::DigitalPin(int pin) : Pin(pin, pin::DIGITAL_MODE, pin::DIGITAL_MODE_MAX_VAL) 
{
	OutputOff();
}

rpicomponents::pin::DigitalPin::DigitalPin(const DigitalPin& pin) : Pin(pin)
{
	OutputOff();
}


void rpicomponents::pin::DigitalPin::WriteToPin(int value) {
	if (!CheckInputValue(value)) return;
	digitalWrite(pin_, value);
	status_.store(value); 
}

int rpicomponents::pin::DigitalPin::ReadFromPin() {
	auto val = status_.load();
	return val;
}
