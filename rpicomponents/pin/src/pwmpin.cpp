#include "pwmpin.hpp"

using namespace std;
using namespace rpicomponents;
using namespace rpicomponents::pin;
using namespace rpicomponents::pin::utils;

PWMPin::PWMPin(int8_t pin) : Pin(pin, PWM_MODE, PWM_MODE_MAX_VAL) {
	OutputOff();
}

void PWMPin::WriteToPin(int16_t value) const {
	if (!CheckInputValue(value)) return;
	lock_guard<std::mutex> lockGuard(mtx_);
	pwmWrite(pin_, value);
	status_ = value; //wouldn't need a lock, as it is atomic
}

int16_t PWMPin::ReadFromPin() const {
	return status_;
}