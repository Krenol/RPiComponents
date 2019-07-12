#include "pcf8591.hpp"
#include <pcf8591.h>


rpicomponents::Pcf8591::Pcf8591(int16_t address, int16_t pin_base) : Pcf(address, pin_base, 0, 3, "pcf8591")
{
	pcf8591Setup(pin_base_, address_);
}

void rpicomponents::Pcf8591::WriteToPcfPin(int8_t pcf_pin_no, int16_t value) const {
	if (pcf_pin_no != 0) return;
	WriteToPcfPin(value);
}

void rpicomponents::Pcf8591::WriteToPcfPin(int16_t value) const {
	if (value < 0 || value > resolution_) return;
	std::lock_guard<std::mutex> grd(mtx_);
	analogWrite(pin_base_, value);
}


int16_t rpicomponents::Pcf8591::ReadFromPcfPin(int8_t pcf_pin_no) const {
	if (!CheckIfPcfPin(pcf_pin_no)) return -1;
	std::lock_guard<std::mutex> grd(mtx_);
	return analogRead(pin_base_ + pcf_pin_no);
}


int8_t rpicomponents::Pcf8591::AmountReadPins() const {
	return 4;
}


int8_t rpicomponents::Pcf8591::AmountWritePins() const {
	return 1;
}