#include "inputpin.hpp"

using namespace std;
using namespace rpicomponents;
using namespace rpicomponents::pin;
using namespace rpicomponents::pin::utils;

InputPin::InputPin(int8_t pin) : Pin(pin, INPUT_MODE, DIGITAL_MODE_MAX_VAL) {
	OutputOff();
}

void InputPin::WriteToPin(int16_t value) const {
	return;
}

int16_t InputPin::ReadFromPin() const {
	lock_guard<mutex> lockGuard(mtx_);
	auto val = digitalRead(pin_);
	return val;
}