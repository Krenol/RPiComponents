#include "esc.hpp"

void rpicomponents::Esc::Initialize()
{
	if (escData_.esc_min_value > escData_.esc_max_value) throw std::invalid_argument("ESC min value cannot be greater than ESC max value!");
	if (escData_.esc_min_value < 0) throw std::invalid_argument("ESC min value cannot be lower than 0!");
	if (escData_.esc_max_value < 0) throw std::invalid_argument("ESC max value cannot be lower than 0!");
	pin_->OutputOff();
}

rpicomponents::Esc::Esc(int pin, int esc_min_value, int esc_max_value) : Component(COMPONENT_ESC), pin_{pin::PinCreator::CreatePin(pin, pin::SOFTPWM_MODE, esc_max_value)}, 
	escData_{EscData(pin, esc_min_value, esc_max_value)}
{
}

rpicomponents::Esc::Esc(const EscData& escData_) : Component(COMPONENT_ESC), pin_{ pin::PinCreator::CreatePin(escData_.pin, pin::SOFTPWM_MODE, escData_.esc_max_value) },
escData_{ EscData(escData_) }
{
}

rpicomponents::Esc::Esc(const Esc& esc) : Esc(esc.GetEscData())
{
}

void rpicomponents::Esc::Calibrate()
{
}

void rpicomponents::Esc::SetOutputSpeed(int speed)
{
	pin_->Output(speed);
}

int rpicomponents::Esc::GetEscSpeed() const
{
	return pin_->ReadPinValue();
}

void rpicomponents::Esc::TurnOff()
{
	pin_->OutputOff();
}

const rpicomponents::EscData& rpicomponents::Esc::GetEscData()
{
	return escData_;
}
