#include "inoutpin.hpp"



using namespace rpicomponents::pin;
using namespace rpicomponents::pin::utils;

InOutPin::InOutPin(int8_t pin) : Pin(pin, IN_OUT_MODE, DIGITAL_MODE_MAX_VAL)
{
	OutputOff();
}

void InOutPin::WriteToPin(int16_t value) const
{
	if (!CheckInputValue(value)) return;
	//lock function to not cause any overhead on pin writings
	std::lock_guard<std::mutex> lockGuard(mtx_);
	pinMode(pin_, OUTPUT);
	digitalWrite(pin_, value);
	status_ = value; //wouldn't need a lock, as it is atomic
}

int16_t InOutPin::ReadFromPin() const
{
	std::lock_guard<std::mutex> lockGuard(mtx_);
	pinMode(pin_, INPUT);
	auto value = digitalRead(pin_);
	return value;
}
