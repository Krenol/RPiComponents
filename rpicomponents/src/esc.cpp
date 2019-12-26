#include "esc.hpp"

void rpicomponents::Esc::Initialize()
{
	if (escData_.esc_min_value > escData_.esc_max_value) throw std::invalid_argument("ESC min value cannot be greater than ESC max value!");
	if (escData_.esc_min_value < 0) throw std::invalid_argument("ESC min value cannot be lower than 0!");
	if (escData_.esc_max_value < 0) throw std::invalid_argument("ESC max value cannot be lower than 0!");
    Arm();
}


void rpicomponents::Esc::Arm() const
{
    pin_->OutputOff();
    utils::Waiter::SleepMillis(ESC_ARM_SLEEP_TIME_MS);
    pin_->Output(escData_.esc_max_value);
    utils::Waiter::SleepMillis(ESC_ARM_SLEEP_TIME_MS);
    pin_->Output(escData_.esc_min_value);
    utils::Waiter::SleepMillis(ESC_ARM_SLEEP_TIME_MS);
}

rpicomponents::Esc::Esc(int pin, int esc_min_value, int esc_max_value) : Component(COMPONENT_ESC), pin_{pin::PinCreator::CreatePin(pin, pin::SOFTPWM_MODE, esc_max_value)}, 
	escData_{EscData(pin, esc_min_value, esc_max_value)}
{
    Initialize();
}

rpicomponents::Esc::Esc(const EscData& escData) : Component(COMPONENT_ESC), pin_{ pin::PinCreator::CreatePin(escData.pin, pin::SOFTPWM_MODE, escData.esc_max_value) },
escData_{ EscData(escData) }
{
    Initialize();
}

rpicomponents::Esc::Esc(const Esc& esc) : Esc(esc.GetEscData())
{
}


void rpicomponents::Esc::SetOutputSpeed(int speed) const
{
	pin_->Output(speed);
}

int rpicomponents::Esc::GetEscSpeed() const
{
	return pin_->ReadPinValue();
}

void rpicomponents::Esc::TurnOff() const
{
	pin_->OutputOff();
}

const rpicomponents::EscData& rpicomponents::Esc::GetEscData() const
{
	return escData_;
}
