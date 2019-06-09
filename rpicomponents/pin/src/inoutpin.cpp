#include "inoutpin.hpp"

using namespace std;
using namespace rpicomponents;
using namespace rpicomponents::pin;
using namespace rpicomponents::pin::utils;

InOutPin::InOutPin(int pin) : Pin(pin, IN_OUT_MODE, DIGITAL_MODE_MAX_VAL)
{
	OutputOff();
}

void InOutPin::WriteToPin(int value) const
{
	if (!CheckInputValue(value)) return;
	//lock function to not cause any overhead on pin writings
	lock_guard<std::mutex> lockGuard(mtx_);
	pinMode(pin_, OUTPUT);
	digitalWrite(pin_, value);
	status_ = value; //wouldn't need a lock, as it is atomic
}

int InOutPin::ReadFromPin() const
{
	lock_guard<std::mutex> lockGuard(mtx_);
	pinMode(pin_, INPUT);
	auto value = digitalRead(pin_);
	return value;
}
