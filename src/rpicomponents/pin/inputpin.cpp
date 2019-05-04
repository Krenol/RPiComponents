#include "inputpin.hpp"

using namespace std;
using namespace rpicomponents;
using namespace rpicomponents::pin;

InputPin::InputPin(int pin) : Pin(pin, INPUT_MODE, DIGITAL_MODE_MAX_VAL) {

}

void InputPin::WriteToPin(int value) {
	return;
}

int InputPin::ReadFromPin() {
	lock_guard<mutex> lockGuard(mtx_);
	auto val = digitalRead(pin_);
	return val;
}