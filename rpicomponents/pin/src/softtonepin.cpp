#include "softtonepin.hpp"



rpicomponents::pin::SofttonePin::SofttonePin(const int &pin, const int &maxOutputValue) : Pin(pin, rpicomponents::pin::SOFTTONE_MODE, maxOutputValue) 
{
	OutputOff();
}

rpicomponents::pin::SofttonePin::SofttonePin(int&& pin, int&& maxOutputValue) : Pin(pin, rpicomponents::pin::SOFTTONE_MODE, maxOutputValue)
{
	OutputOff();
}

rpicomponents::pin::SofttonePin::SofttonePin(const SofttonePin& pin) : Pin(pin.GetPin())
{
	OutputOff();
}


void rpicomponents::pin::SofttonePin::WriteToPin(const int& value) const {
	if (!CheckInputValue(value)) return;
	std::lock_guard<std::mutex> lockGuard(mtx_);
	softToneWrite(pin_, value);
	status_ = value; //wouldn't need a lock, as it is atomic
}

int rpicomponents::pin::SofttonePin::ReadFromPin() const {
	return status_;
}