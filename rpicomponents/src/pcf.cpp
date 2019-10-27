#include "pcf.hpp"
#include <wiringPiI2C.h>

rpicomponents::Pcf::~Pcf() {

}

rpicomponents::Pcf::Pcf(const int& address, const int& pin_base, const int& read_pin_count, const int& write_pin_count, 
	const int& min_pin_offset, const int& max_pin_offset, const std::string& comp_name) : Component(comp_name), address_{address}, 
	pin_base_{pin_base}, read_pin_count_{read_pin_count}, write_pin_count_{write_pin_count}, min_pin_offset_{min_pin_offset},
	max_pin_offset_{max_pin_offset}
{
	Initialize();
}

void rpicomponents::Pcf::Initialize() const {
	if (pin_base_ < 64) throw std::invalid_argument("pin base must be greater than 63!");
	wiringPiSetup();
	if (!rpicomponents::pin::AddressChecker::IsI2CAddress(address_)) {
		throw std::invalid_argument("given address for pcf is not an i2c address!");
	}
	if (wiringPiI2CSetup(address_) == -1) {
		throw std::invalid_argument("i2c is not set properly!");
	}
	AddPins({ 8,9 }); //pins for i2c
}

rpicomponents::Pcf::Pcf(int&& address, int&& pin_base, int&& read_pin_count, int&& write_pin_count, 
	int&& min_pin_offset, int&& max_pin_offset, std::string&& comp_name) : Component(comp_name), address_{ address },
	pin_base_{ pin_base }, read_pin_count_{ read_pin_count }, write_pin_count_{ write_pin_count }, min_pin_offset_{ min_pin_offset },
	max_pin_offset_{ max_pin_offset }
{
	Initialize();
}

rpicomponents::Pcf::Pcf(const Pcf& pcf) : 
	Pcf(pcf.GetPcfAddress(), pcf.GetPinBase(), pcf.AmountReadPins(), pcf.AmountWritePins(),pcf.GetMinPinOffset(),
		pcf.GetMaxPinOffset(), pcf.ToString())
{
}

bool rpicomponents::Pcf::CheckIfPcfPin(int pcf_pin_no) const {
	if (pcf_pin_no < min_pin_offset_ || pcf_pin_no > max_pin_offset_) return false;
	return true;
}

const int& rpicomponents::Pcf::GetResolution() const {
	return resolution_;
}

const int& rpicomponents::Pcf::AmountReadPins() const
{
	return read_pin_count_;
}

const int& rpicomponents::Pcf::AmountWritePins() const
{
	return write_pin_count_;
}

const int& rpicomponents::Pcf::GetPcfAddress() const
{
	return address_;
}

const int& rpicomponents::Pcf::GetPinBase() const
{
	return pin_base_;
}

const int& rpicomponents::Pcf::GetMinPinOffset() const
{
	return min_pin_offset_;
}

const int& rpicomponents::Pcf::GetMaxPinOffset() const
{
	return max_pin_offset_;
}
