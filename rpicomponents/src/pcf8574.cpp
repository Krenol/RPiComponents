#include "pcf8574.hpp"

using namespace std;
using namespace rpicomponents;

PCF8574::PCF8574(int address, int pin_base) : PCF(address, pin_base, 0, 7, "pcf8574")
{
	pcf8574Setup(pin_base_, address_);
}


void PCF8574::SetPinMode(int pcf_pin_no, int pin_mode) const {
	if (!CheckPcfPin(pcf_pin_no)) return;
	if (pin_mode != INPUT && pin_mode != OUTPUT) return;
	pinMode(pin_base_ + pcf_pin_no, pin_mode);
}

void PCF8574::WriteToPcfPin(int pcf_pin_no, int value) const {
	if (!CheckPcfPin(pcf_pin_no)) return;
	if (value < 0 || value > resolution_) return; 
	lock_guard<mutex> grd(mtx_);
	SetPinMode(pcf_pin_no, OUTPUT);
	digitalWrite(pin_base_ + pcf_pin_no, value);
}

int PCF8574::ReadFromPcfPin(int pcf_pin_no) const {
	if (!CheckPcfPin(pcf_pin_no)) return -1;
	lock_guard<mutex> grd(mtx_);
	SetPinMode(pcf_pin_no, INPUT);
	auto val = digitalRead(pin_base_ + pcf_pin_no);
	return val;
}

int PCF8574::AmountReadPins() const {
	return 8;
}


int PCF8574::AmountWritePins() const {
	return 8;
}
