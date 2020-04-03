#include "inputpin.hpp"

rpicomponents::pin::InputPin::InputPin(int pin) : Pin(pin, rpicomponents::pin::INPUT_MODE, rpicomponents::pin::DIGITAL_MODE_MAX_VAL) 
{
	OutputOff();
}

//rpicomponents::pin::InputPin::InputPin(int&& pin) : Pin(pin, rpicomponents::pin::INPUT_MODE, rpicomponents::pin::DIGITAL_MODE_MAX_VAL)
//{
//	OutputOff();
//}

rpicomponents::pin::InputPin::InputPin(const InputPin& pin) : Pin(pin.GetPin(), rpicomponents::pin::INPUT_MODE, rpicomponents::pin::DIGITAL_MODE_MAX_VAL)
{
	OutputOff();
}

void rpicomponents::pin::InputPin::WriteToPin(int value) {
	return;
}

int rpicomponents::pin::InputPin::ReadFromPin() {
	auto val = digitalRead(pin_);
	return val;
}
