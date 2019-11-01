#include "joystick.hpp"

void rpicomponents::Joystick::Initialize() const
{
	if (pcfXPin_ < 0) throw new std::invalid_argument("joystick pcf x pin cannot be lower than 0");
	if (pcfYPin_ < 0) throw new std::invalid_argument("joystick pcf y pin cannot be lower than 0");

	if (pcfXPin_ > pcf_->GetMaxPinOffset()) throw new std::invalid_argument("joystick pcf x pin must be < " + std::to_string(pcf_->GetMaxPinOffset()));
	if (pcfYPin_ > pcf_->GetMaxPinOffset()) throw new std::invalid_argument("joystick pcf y pin must be < " + std::to_string(pcf_->GetMaxPinOffset()));
}

rpicomponents::Joystick::Joystick(const int& pcf_address, const int& pin_base, const int& pcf_x_pin, const int& pcf_y_pin, const int& gpio_z, const int& z_pud) : Component(COMPONENT_JOYSTICK), 
	zBtn_{std::unique_ptr<Button>(new Button(gpio_z, z_pud))}, pcf_{std::unique_ptr<Pcf8591>(new Pcf8591(pcf_address, pin_base))}, pcfXPin_{ pcf_x_pin }, pcfYPin_{pcf_y_pin}
{
	Initialize();
}

rpicomponents::Joystick::Joystick(int&& pcf_address, int&& pin_base, int&& pcf_x_pin, int&& pcf_y_pin, int&& gpio_z, int&& z_pud) : Component(COMPONENT_JOYSTICK),
	zBtn_{ std::unique_ptr<Button>(new Button(gpio_z, z_pud)) }, pcf_{ std::unique_ptr<Pcf8591>(new Pcf8591(pcf_address, pin_base)) }, pcfXPin_{ pcf_x_pin }, pcfYPin_{ pcf_y_pin }
{
	Initialize();
}

rpicomponents::Joystick::Joystick(const Joystick& joystick) : Joystick(joystick.GetPcfAddress(), joystick.GetPcfBase(), joystick.GetPcfXPin(), joystick.GetPcfYPin(), 
    joystick.GetGpioZPin(), joystick.GetZPud())
{
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

const int& rpicomponents::Joystick::GetPcfBase() const
{
	return pcf_->GetPinBase();
}

const int& rpicomponents::Joystick::GetPcfAddress() const
{
	return pcf_->GetPcfAddress();
}

const int& rpicomponents::Joystick::GetPcfXPin() const
{
	return pcfXPin_;
}

const int& rpicomponents::Joystick::GetPcfYPin() const
{
	return pcfYPin_;
}

const int& rpicomponents::Joystick::GetGpioZPin() const
{
	return zBtn_->GetPin();
}

const int& rpicomponents::Joystick::GetZPud() const
{
	return zBtn_->GetPUD();
}
