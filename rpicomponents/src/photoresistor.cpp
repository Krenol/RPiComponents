#include "photoresistor.hpp"

const std::vector<float> rpicomponents::Photoresistor::allowed_voltages_{ 3.3f, 5.0f };

void rpicomponents::Photoresistor::Initialize() {
	if (pcf_ == nullptr) throw std::invalid_argument("Passed Pcf8591 is nullptr!");
	if (std::find(allowed_voltages_.begin(), allowed_voltages_.end(), voltage_) == allowed_voltages_.end()) {
		throw std::invalid_argument("Voltage must either be 3.3 V or 5.0 V");
	}
	if (!pcf_->CheckIfPcfPin(pcf_pin_)) throw std::invalid_argument("Invalid pcf pin was given!");
	AddPins(pcf_->GetUsedPins());
}

rpicomponents::Photoresistor::Photoresistor(std::shared_ptr <rpicomponents::Pcf8591> pcf, int read_pin, float  voltage) : Component(COMPONENT_PHOTORESISTOR),
voltage_{voltage}, pcf_pin_{ read_pin }, pcf_{ pcf }
{
	Initialize();
}


rpicomponents::Photoresistor::Photoresistor(const Photoresistor& photoresistor) : 
	Photoresistor(photoresistor.GetPcf(), photoresistor.GetPcfPin(), photoresistor.GetVoltage())
{
}

int rpicomponents::Photoresistor::GetPhotoresistorValue() const {
	auto val = pcf_->ReadFromPcfPin(pcf_pin_);;
	return val;
}

float rpicomponents::Photoresistor::GetPhotoresistorVoltage() const {
	auto val = (float)GetPhotoresistorValue();
	auto res = (float)(pcf_->GetResolution() - 1);
	return  val / res * voltage_;
}

const std::shared_ptr <rpicomponents::Pcf8591>& rpicomponents::Photoresistor::GetPcf() const
{
	return pcf_;
}

int rpicomponents::Photoresistor::GetPcfPin() const
{
	return pcf_pin_;
}

float  rpicomponents::Photoresistor::GetVoltage() const
{
	return voltage_;
}
