#include "pcf8591.hpp"

using namespace std;
using namespace rpicomponents;

PCF8591::PCF8591(int address, int pin_base) : PCF(address, pin_base, 0, 3, "pcf8591")
{
	pcf8591Setup(pin_base_, address_);
}

void PCF8591::WriteToPcfPin(int pcf_pin_no, int value) const {
	if (pcf_pin_no != 0) return;
	WriteToPcfPin(value);
}

void PCF8591::WriteToPcfPin(int value) const {
	if (value < 0 || value > resolution_) return;
	lock_guard<mutex> grd(mtx_);
	analogWrite(pin_base_, value);
}


int PCF8591::ReadFromPcfPin(int pcf_pin_no) const {
	if (!CheckPcfPin(pcf_pin_no)) return -1;
	lock_guard<mutex> grd(mtx_);
	return analogRead(pin_base_ + pcf_pin_no);
}


int PCF8591::AmountReadPins() const {
	return 4;
}


int PCF8591::AmountWritePins() const {
	return 1;
}