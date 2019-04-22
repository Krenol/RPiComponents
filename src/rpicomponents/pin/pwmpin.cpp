#include "pwmpin.hpp"

using namespace std;
using namespace rpicomponents;
using namespace rpicomponents::pin;

PWMPin::PWMPin(int pin) : Pin(pin, PWM, PWM_MODE_MAX_VAL) {
	OutputOff();
}

void PWMPin::WriteToPin(int value) {
	if (!CheckInputValue(value)) return;
	lock_guard<mutex> lockGuard(mtx_);
	pwmWrite(pin_, value);
	status_ = value; //wouldn't need a lock, as it is atomic
}