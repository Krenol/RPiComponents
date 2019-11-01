#include "pcf8591.hpp"
#include <pcf8591.h>


void rpicomponents::Pcf8591::WriteToPcfPin(const int& pcf_pin_no, const int& value) const {
	WriteToPcfPin(value);
}

rpicomponents::Pcf8591::Pcf8591(const int& address, const int& pin_base) : Pcf(address, pin_base, COMPONENT_PCF8591_READ_PINS, COMPONENT_PCF8591_WRITE_PINS,
	COMPONENT_PCF8591_MIN_PIN_OFFSET, COMPONENT_PCF8591_MAX_PIN_OFFSET, COMPONENT_PCF8591)
{
	pcf8591Setup(pin_base_, address_);
}

rpicomponents::Pcf8591::Pcf8591(int&& address, int&& pin_base) : Pcf(address, pin_base, COMPONENT_PCF8591_READ_PINS, COMPONENT_PCF8591_WRITE_PINS,
	COMPONENT_PCF8591_MIN_PIN_OFFSET, COMPONENT_PCF8591_MAX_PIN_OFFSET, COMPONENT_PCF8591)
{
	pcf8591Setup(pin_base_, address_);
}

rpicomponents::Pcf8591::Pcf8591(const Pcf8591& pcf) : Pcf8591(pcf.GetPcfAddress(), pcf.GetPinBase())
{
}

void rpicomponents::Pcf8591::WriteToPcfPin(const int& value) const {
	if (value < 0 || value > resolution_) return;
	analogWrite(pin_base_, value);
}


int rpicomponents::Pcf8591::ReadFromPcfPin(const int& pcf_pin_no) const {
	if (!CheckIfPcfPin(pcf_pin_no)) return -1;
	return analogRead(pin_base_ + pcf_pin_no);
}