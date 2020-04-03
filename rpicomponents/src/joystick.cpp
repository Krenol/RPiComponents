#include "joystick.hpp"

void rpicomponents::Joystick::Initialize()
{
	if (pcfXPin_ < 0) throw new std::invalid_argument("joystick pcf x pin cannot be lower than 0");
	if (pcfYPin_ < 0) throw new std::invalid_argument("joystick pcf y pin cannot be lower than 0");

	if (pcfXPin_ > pcf_->GetMaxPinOffset()) throw new std::invalid_argument("joystick pcf x pin must be < " + std::to_string(pcf_->GetMaxPinOffset()));
	if (pcfYPin_ > pcf_->GetMaxPinOffset()) throw new std::invalid_argument("joystick pcf y pin must be < " + std::to_string(pcf_->GetMaxPinOffset()));
	AddPins(pcf_->GetUsedPins());
	AddPins(zBtn_->GetUsedPins());
}

rpicomponents::Joystick::Joystick(std::shared_ptr<rpicomponents::Pcf8591> pcf, int pcf_x_pin, int pcf_y_pin, std::shared_ptr<rpicomponents::Button> zBtn) : 
	Component(COMPONENT_JOYSTICK), pcf_{ pcf }, zBtn_{ zBtn }, pcfXPin_{ pcf_x_pin }, pcfYPin_{ pcf_y_pin }
{
	Initialize();
}

rpicomponents::Joystick::Joystick(const Joystick& joystick) : Joystick(joystick.GetPcf(), joystick.GetPcfXPin(), joystick.GetPcfYPin(), joystick.GetZBtn())
{
	Initialize();
}


int rpicomponents::Joystick::ReadXAxis() const
{
	return pcf_->ReadFromPcfPin(pcfXPin_);
}

int rpicomponents::Joystick::ReadYAxis() const
{
	return pcf_->ReadFromPcfPin(pcfYPin_);
}

bool rpicomponents::Joystick::ReadZAxis() const
{
	return zBtn_->IsPressed();
}

rpicomponents::JoystickAxes rpicomponents::Joystick::ReadAxes() const
{
	return JoystickAxes(ReadXAxis(), ReadYAxis(), ReadZAxis());
}

const std::shared_ptr<rpicomponents::Pcf8591>& rpicomponents::Joystick::GetPcf() const
{
	return pcf_;
}

const std::shared_ptr<rpicomponents::Button>& rpicomponents::Joystick::GetZBtn() const
{
	return zBtn_;
}


int rpicomponents::Joystick::GetPcfXPin() const
{
	return pcfXPin_;
}

int rpicomponents::Joystick::GetPcfYPin() const
{
	return pcfYPin_;
}

