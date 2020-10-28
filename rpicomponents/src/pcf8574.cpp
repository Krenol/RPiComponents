#include "pcf8574.hpp"


void rpicomponents::Pcf8574::SetPinMode(int pcf_pin_no, int pin_mode) {
	if (pin_mode != PI_INPUT && pin_mode != PI_OUTPUT) return;
	int old = data_, bit;
	bit = 1 << (pcf_pin_no & 7);
	pin_mode == PI_OUTPUT ? (old &= (~bit)) : (old |= bit);
	i2cWriteByte(handle_, old);
	data_ = old;
}

rpicomponents::Pcf8574::Pcf8574(int address, int pin_base) : Pcf(address, pin_base, COMPONENT_PCF8574_READ_PINS,
	COMPONENT_PCF8574_WRITE_PINS, COMPONENT_PCF8574_MIN_PIN_OFFSET, COMPONENT_PCF8574_MAX_PIN_OFFSET, COMPONENT_PCF8574)
{
	data_ = i2cReadByte(handle_);
}


rpicomponents::Pcf8574::Pcf8574(const Pcf8574& pcf) : Pcf8574(pcf.GetPcfAddress(), pcf.GetPinBase()) {

}

void rpicomponents::Pcf8574::WriteToPcfPin(int pcf_pin_no, unsigned int value) {
	if (!CheckIfPcfPin(pcf_pin_no)) return;
	if (value < 0 || value > resolution_) return; 
	int old = data_, bit;
	bit = 1 << (pcf_pin_no & 7);
	SetPinMode(pcf_pin_no, PI_OUTPUT);
	value == 0 ? (old &= (~bit)) : (old |= bit);
	i2cWriteByte(handle_, old);
	data_ = old;
}

int rpicomponents::Pcf8574::ReadFromPcfPin(int pcf_pin_no) {
	if (!CheckIfPcfPin(pcf_pin_no)) return -1;
	unsigned int value, bit;
	bit = 1 << (pcf_pin_no & 7);
	SetPinMode(pcf_pin_no, PI_INPUT);
	value = i2cReadByte(handle_);
	if((bit & value) == 0) {
		return 0;
	} 
	return 1;
}
