#include "q74hc595.hpp"

void rpicomponents::Q74HC595::Initialize() const
{
}

bool rpicomponents::Q74HC595::ValidQPin(Q_Pin q_pin) const
{
	return false;
}

rpicomponents::Q_Pin rpicomponents::Q74HC595::GetQPin(const int& pin_no)
{
	return Q_Pin();
}

void rpicomponents::Q74HC595::SetQPin(const int& pin_no, bool is_on)
{
}

void rpicomponents::Q74HC595::WriteToQPin(const Q_Pin& q_pin)
{
}


void rpicomponents::Q74HC595::WriteToPins(const std::vector<Q_Pin>& q_values) const
{
}

rpicomponents::Q74HC595::Q74HC595(const int& ds_pin, const int& stcp_pin, const int& shcp_pin)
{
}

rpicomponents::Q74HC595::Q74HC595(int&& ds_pin, int&& stcp_pin, int&& shcp_pin)
{
}

rpicomponents::Q74HC595::Q74HC595(const Q74HC595& q74hc595)
{
}

rpicomponents::Q_Pin rpicomponents::Q74HC595::CreateQPin(const int& pin_no, bool turn_on)
{
	return Q_Pin();
}


void rpicomponents::Q74HC595::SetQPinOutput(const std::vector<Q_Pin>& q_values) const
{
}

void rpicomponents::Q74HC595::SetQPinOutput(const Q_Pin& q_pin) const
{
}

void rpicomponents::Q74HC595::TurnOn() const
{
}

void rpicomponents::Q74HC595::TurnOff() const
{
}
