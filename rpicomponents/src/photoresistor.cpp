#include "photoresistor.hpp"

const std::vector<float> rpicomponents::Photoresistor::allowed_voltages_{ 3.3f, 5.0f };

rpicomponents::Photoresistor::Photoresistor(const rpicomponents::Pcf8591* pcf, int pcf_pin, float voltage) : Component("photoresistor"),
pcf_{ pcf }, pcf_pin_{ pcf_pin }, voltage_{ voltage }
{
	Initialize();
}

void rpicomponents::Photoresistor::Initialize() const {
	if (pcf_ == nullptr) throw std::invalid_argument("Passed Pcf8591 is nullptr!");
	if (std::find(allowed_voltages_.begin(), allowed_voltages_.end(), voltage_) == allowed_voltages_.end()) {
		throw std::invalid_argument("Voltage must either be 3.3 V or 5.0 V");
	}
	if (!pcf_->CheckIfPcfPin(pcf_pin_)) throw std::invalid_argument("Invalid pcf pin was given!");
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