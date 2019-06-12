#include "pcf.hpp"

using namespace std;
using namespace rpicomponents;

PCF::PCF(int address, int pin_base, int min_pin_offset, int max_pin_offset, string comp_name) : Component(comp_name), address_{ address }, pin_base_{ pin_base },
	min_pin_offset_{min_pin_offset}, max_pin_offset_{ max_pin_offset }
{
	Initialize();
}

PCF::~PCF() {

}

void PCF::Initialize() const {
	if (pin_base_ < 64) throw std::invalid_argument("pin base must be greater than 63!");
	wiringPiSetup();
	if (!pin::utils::PinChecker::IsI2CAddress(address_)) {
		throw std::invalid_argument("given address for PCF8574 is not an i2c address!");
	}
	if (wiringPiI2CSetup(address_) == -1) {
		throw std::invalid_argument("i2c is not set properly!");
	}
	AddPins({ 8,9 }); //pins for i2c
}

bool PCF::CheckPcfPin(int pcf_pin_no) const {
	if (pcf_pin_no < min_pin_offset_ || pcf_pin_no > max_pin_offset_) return false;
	return true;
}

int PCF::GetResolution() const {
	return resolution_;
}