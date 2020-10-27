#include "pcf.hpp"

rpicomponents::Pcf::Pcf(int address, int pin_base, int read_pin_count, int write_pin_count, 
	int min_pin_offset, int max_pin_offset, const std::string& comp_name) : Component(comp_name), address_{address}, 
	pin_base_{pin_base}, read_pin_count_{read_pin_count}, write_pin_count_{write_pin_count}, min_pin_offset_{min_pin_offset},
	max_pin_offset_{max_pin_offset}, handle_ {i2cOpen(I2C_BUS_CHANNEL, address_, 0)}
{
	Initialize();
}

void rpicomponents::Pcf::Initialize() {
	if (pin_base_ < 0) {
		throw std::invalid_argument("pin base must be greater/equals 0!");
	}
	else if (pin_base_ > 255) {
		throw std::invalid_argument("pin base must be less than 256!");
	}
	if(handle_ < 0) throw std::runtime_error("couldn't open i2c for PCF");
	AddPins({ 8,9 }); //pins for i2c
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

int rpicomponents::Pcf::GetResolution() const {
	return resolution_;
}

int rpicomponents::Pcf::AmountReadPins() const
{
	return read_pin_count_;
}

int rpicomponents::Pcf::AmountWritePins() const
{
	return write_pin_count_;
}

int rpicomponents::Pcf::GetPcfAddress() const
{
	return address_;
}

int rpicomponents::Pcf::GetPinBase() const
{
	return pin_base_;
}

int rpicomponents::Pcf::GetMinPinOffset() const
{
	return min_pin_offset_;
}

int rpicomponents::Pcf::GetMaxPinOffset() const
{
	return max_pin_offset_;
}

rpicomponents::Pcf::~Pcf() 
{
	try{
		i2cClose(handle_);
	} catch(...) {

	}
}
