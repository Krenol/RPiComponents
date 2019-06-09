#include "pcf8574.hpp"

using namespace std;
using namespace rpicomponents;

PCF8574::PCF8574(int address, int pin_base) : Component("pcf8574"), address_{ address }, pin_base_{ pin_base }
{
	Initialize();
}

bool PCF8574::CheckPcfPin(int pcf_pin_no) const {
	if (pcf_pin_no < min_pin_offset_ || pcf_pin_no > max_pin_offset_) return false;
	return true;
}

void PCF8574::Initialize() const{
	if (pin_base_ < 64) throw std::invalid_argument("pin base must be greater than 63!");
	wiringPiSetup();
	if (!pin::utils::PinChecker::IsI2CAddress(address_) || wiringPiI2CSetup(address_) == -1) {
		throw std::invalid_argument("given address is not an i2c address or i2c is not set properly!\n");
	}
	AddPins({ 8,9 }); //pins for i2c
	pcf8574Setup(pin_base_, address_);
}

void PCF8574::SetPinMode(int pcf_pin_no, int pin_mode) const {
	if (!CheckPcfPin(pcf_pin_no)) return;
	if (pin_mode != INPUT && pin_mode != OUTPUT) return;
	pinMode(pin_base_ + pcf_pin_no, pin_mode);
}

void PCF8574::WriteToPcfPin(int pcf_pin_no, int value) const {
	if (!CheckPcfPin(pcf_pin_no)) return;
	if (value < 0 || value > 1) return; // only digital supported
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