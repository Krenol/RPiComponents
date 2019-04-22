#include "softpwmpin.hpp"

using namespace std;
using namespace rpicomponents;
using namespace rpicomponents::pin;

SoftPWMPin::SoftPWMPin(int pin, int maxOutputValue) : Pin(pin, SOFTPWM, maxOutputValue) {
	OutputOff();
}

void SoftPWMPin::WriteToPin(int value) {
	if (!CheckInputValue(value)) return;
	lock_guard<mutex> lockGuard(mtx_);
	softPwmWrite(pin_, value);
	status_ = value; //wouldn't need a lock, as it is atomic
}