#include "softtonepin.hpp"

using namespace std;
using namespace rpicomponents;
using namespace rpicomponents::pin;
using namespace rpicomponents::pin::utils;


SofttonePin::SofttonePin(int pin, int maxOutputValue) : Pin(pin, SOFTTONE_MODE, maxOutputValue) {
	OutputOff();
}

void SofttonePin::WriteToPin(int value) const {
	if (!CheckInputValue(value)) return;
	lock_guard<std::mutex> lockGuard(mtx_);
	softToneWrite(pin_, value);
	status_ = value; //wouldn't need a lock, as it is atomic
}

int SofttonePin::ReadFromPin() const {
	return status_;
}