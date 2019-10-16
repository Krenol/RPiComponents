#include "digitalpin.hpp"


rpicomponents::pin::DigitalPin::DigitalPin(const int &pin) : Pin(pin, pin::DIGITAL_MODE, pin::DIGITAL_MODE_MAX_VAL) 
{
	OutputOff();
}

rpicomponents::pin::DigitalPin::DigitalPin(int&& pin) : Pin(pin, pin::DIGITAL_MODE, pin::DIGITAL_MODE_MAX_VAL)
{
	OutputOff();
}

rpicomponents::pin::DigitalPin::DigitalPin(const DigitalPin& pin) : Pin(pin)
{
	OutputOff();
}


void rpicomponents::pin::DigitalPin::WriteToPin(const int& value) const {
	if (!CheckInputValue(value)) return;
	//lock function to not cause any overhead on pin writings
	std::lock_guard<std::mutex> lockGuard(mtx_);
	digitalWrite(pin_, value);
	status_ = value; //wouldn't need a lock, as it is atomic
}

int rpicomponents::pin::DigitalPin::ReadFromPin() const {
	return status_;
}