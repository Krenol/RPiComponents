#include "digitalpin.hpp"

using namespace std;
using namespace rpicomponents;
using namespace rpicomponents::pin;


DigitalPin::DigitalPin(int pin) : Pin(pin, DIGITAL, DIGITAL_MODE_MAX_VAL) {
	OutputOff();
}

void DigitalPin::WriteToPin(int value) const {
	if (!CheckInputValue(value)) return;
	//lock function to not cause any overhead on pin writings
	lock_guard<std::mutex> lockGuard(mtx_);
	digitalWrite(pin_, value);
	status_ = value; //wouldn't need a lock, as it is atomic
}

int DigitalPin::ReadFromPin() const {
	return status_;
}