#include "joystick.hpp"

void rpicomponents::Joystick::Initialize() const
{
}

rpicomponents::Joystick::Joystick(const int& pcf_address, const int& pin_base, const int& pcf_x_pin, const int& pcf_y_pin, const int& gpio_z, const int& z_pud) : Component(COMPONENT_JOYSTICK)
{
	Initialize();
}

rpicomponents::Joystick::Joystick(int&& pcf_address, int&& pin_base, int&& pcf_x_pin, int&& pcf_y_pin, int&& gpio_z, int&& z_pud) : Component(COMPONENT_JOYSTICK)
{
	Initialize();
}

rpicomponents::Joystick::Joystick(const Joystick& joystick) : Joystick(joystick.GetPcfAddress(), joystick.GetPcfBase(), joystick.GetPcfXPin(), joystick.GetPcfYPin(), 
	joystick.GetGpioZPin(), joystick.GetZPud)
{
}

int rpicomponents::Joystick::ReadXAxis() const
{
	return 0;
}

int rpicomponents::Joystick::ReadYAxis() const
{
	return 0;
}

bool rpicomponents::Joystick::ReadZAxis() const
{
	return false;
}

JoystickAxes rpicomponents::Joystick::ReadAxes() const
{
	return JoystickAxes();
}

const int& rpicomponents::Joystick::GetPcfBase() const
{
	// TODO: insert return statement here
}

const int& rpicomponents::Joystick::GetPcfAddress() const
{
	// TODO: insert return statement here
}

const int& rpicomponents::Joystick::GetPcfXPin() const
{
	// TODO: insert return statement here
}

const int& rpicomponents::Joystick::GetPcfYPin() const
{
	// TODO: insert return statement here
}

const int& rpicomponents::Joystick::GetGpioZPin() const
{
	// TODO: insert return statement here
}

const int& rpicomponents::Joystick::GetZPud() const
{
	// TODO: insert return statement here
}
