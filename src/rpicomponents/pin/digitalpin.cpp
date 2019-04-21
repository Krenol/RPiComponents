#include "digitalpin.hpp"

using namespace std;
using namespace rpicomponents;
using namespace rpicomponents::pin;

DigitalPin::DigitalPin(int pin) : Pin(pin, DIGITAL_MODE, DIGITAL_MODE_MAX_VAL) {
	OutputOff();
}

void DigitalPin::WriteToPin(int value) {
	if (!CheckInputValue(value)) return;
	digitalWrite(pin_, value);
	status_ = value;
}