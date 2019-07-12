#include "pcf.hpp"
#include <wiringPiI2C.h>


rpicomponents::Pcf::Pcf(int16_t address, int16_t pin_base, int8_t min_pin_offset, int8_t max_pin_offset, std::string comp_name) : Component(comp_name), address_{ address }, pin_base_{ pin_base },
	min_pin_offset_{min_pin_offset}, max_pin_offset_{ max_pin_offset }
{
	Initialize();
}

rpicomponents::Pcf::~Pcf() {

}

void rpicomponents::Pcf::Initialize() const {
	if (pin_base_ < 64) throw std::invalid_argument("pin base must be greater than 63!");
	wiringPiSetup();
	if (!pin::utils::PinChecker::IsI2CAddress(address_)) {
		throw std::invalid_argument("given address for pcf is not an i2c address!");
	}
	if (wiringPiI2CSetup(address_) == -1) {
		throw std::invalid_argument("i2c is not set properly!");
	}
	AddPins({ 8,9 }); //pins for i2c
}

bool rpicomponents::Pcf::CheckIfPcfPin(int8_t pcf_pin_no) const {
	if (pcf_pin_no < min_pin_offset_ || pcf_pin_no > max_pin_offset_) return false;
	return true;
}

int16_t rpicomponents::Pcf::GetResolution() const {
	return resolution_;
}