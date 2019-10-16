#include "pcf8591.hpp"
#include <pcf8591.h>


rpicomponents::Pcf8591::Pcf8591(int address, int pin_base) : Pcf(address, pin_base, 0, 3, "pcf8591")
{
	pcf8591Setup(pin_base_, address_);
}

void rpicomponents::Pcf8591::WriteToPcfPin(int pcf_pin_no, const int& value) const {
	if (pcf_pin_no != 0) return;
	WriteToPcfPin(value);
}

void rpicomponents::Pcf8591::WriteToPcfPin(const int& value) const {
	if (value < 0 || value > resolution_) return;
	std::lock_guard<std::mutex> grd(mtx_);
	analogWrite(pin_base_, value);
}


int rpicomponents::Pcf8591::ReadFromPcfPin(int pcf_pin_no) const {
	if (!CheckIfPcfPin(pcf_pin_no)) return -1;
	std::lock_guard<std::mutex> grd(mtx_);
	return analogRead(pin_base_ + pcf_pin_no);
}


int rpicomponents::Pcf8591::AmountReadPins() const {
	return 4;
}


int rpicomponents::Pcf8591::AmountWritePins() const {
	return 1;
}