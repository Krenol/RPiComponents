#include "pcf8591.hpp"


void rpicomponents::Pcf8591::WriteToPcfPin(int pcf_pin_no, unsigned int value) {
	if (!CheckIfPcfPin(pcf_pin_no)) return;
	i2cWriteByteData(handle_, pin_base_ + pcf_pin_no, value);
}

rpicomponents::Pcf8591::Pcf8591(int address, int pin_base) : Pcf(address, pin_base, COMPONENT_PCF8591_READ_PINS, COMPONENT_PCF8591_WRITE_PINS,
	COMPONENT_PCF8591_MIN_PIN_OFFSET, COMPONENT_PCF8591_MAX_PIN_OFFSET, COMPONENT_PCF8591)
{

}

rpicomponents::Pcf8591::Pcf8591(const Pcf8591& pcf) : Pcf8591(pcf.GetPcfAddress(), pcf.GetPinBase())
{
}


int rpicomponents::Pcf8591::ReadFromPcfPin(int pcf_pin_no) {
	if (!CheckIfPcfPin(pcf_pin_no)) return -1;
	auto value = i2cReadByteData(handle_, pin_base_ + pcf_pin_no);
	return value;
}