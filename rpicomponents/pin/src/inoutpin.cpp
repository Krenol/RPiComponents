#include "inoutpin.hpp"


rpicomponents::pin::InOutPin::InOutPin(const int &pin) : Pin(pin, rpicomponents::pin::IN_OUT_MODE, rpicomponents::pin::DIGITAL_MODE_MAX_VAL)
{
	OutputOff();
}

rpicomponents::pin::InOutPin::InOutPin(int&& pin) : Pin(pin, rpicomponents::pin::IN_OUT_MODE, rpicomponents::pin::DIGITAL_MODE_MAX_VAL)
{
	OutputOff();
}

rpicomponents::pin::InOutPin::InOutPin(InOutPin& pin) : Pin(pin.GetPin(), rpicomponents::pin::IN_OUT_MODE, rpicomponents::pin::DIGITAL_MODE_MAX_VAL)
{
	OutputOff();
}

void rpicomponents::pin::InOutPin::WriteToPin(const int& value) const
{
	if (!CheckInputValue(value)) return;
	//lock function to not cause any overhead on pin writings
	std::lock_guard<std::mutex> lockGuard(mtx_);
	pinMode(pin_, OUTPUT);
	digitalWrite(pin_, value);
	status_ = value; //wouldn't need a lock, as it is atomic
}

int rpicomponents::pin::InOutPin::ReadFromPin() const
{
	std::lock_guard<std::mutex> lockGuard(mtx_);
	pinMode(pin_, INPUT);
	auto value = digitalRead(pin_);
	return value;
}
