#include "pcf8574.hpp"
#include <pcf8574.h>



rpicomponents::Pcf8574::Pcf8574(int address, int pin_base) : Pcf(address, pin_base, COMPONENT_PCF8574_READ_PINS, 
	COMPONENT_PCF8574_WRITE_PINS, COMPONENT_PCF8574_MIN_PIN_OFFSET, COMPONENT_PCF8574_MAX_PIN_OFFSET, COMPONENT_PCF8574)
{
	pcf8574Setup(pin_base_, address_);
}


void rpicomponents::Pcf8574::SetPinMode(int pcf_pin_no, int pin_mode) const {
	if (!CheckIfPcfPin(pcf_pin_no)) return;
	if (pin_mode != INPUT && pin_mode != OUTPUT) return;
	pinMode(pin_base_ + pcf_pin_no, pin_mode);
}

void rpicomponents::Pcf8574::WriteToPcfPin(int pcf_pin_no, const int& value) const {
	if (!CheckIfPcfPin(pcf_pin_no)) return;
	if (value < 0 || value > resolution_) return; 
	SetPinMode(pcf_pin_no, OUTPUT);
	digitalWrite(pin_base_ + pcf_pin_no, value);
}

int rpicomponents::Pcf8574::ReadFromPcfPin(int pcf_pin_no) const {
	if (!CheckIfPcfPin(pcf_pin_no)) return -1;
	SetPinMode(pcf_pin_no, INPUT);
	auto val = digitalRead(pin_base_ + pcf_pin_no);
	return val;
}
