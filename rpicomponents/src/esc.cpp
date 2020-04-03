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

rpicomponents::Esc::Esc(std::shared_ptr<pin::Pin> pin, int esc_min_value, int esc_max_value) : Component(COMPONENT_ESC), pin_{pin},
	escData_{EscData(esc_min_value, esc_max_value)}
{
    Initialize();
}

rpicomponents::Esc::Esc(std::shared_ptr<pin::Pin> pin, const EscData& escData) : Component(COMPONENT_ESC), pin_{ pin },
escData_{ EscData(escData) }
{
    Initialize();
}

rpicomponents::Esc::Esc(const Esc& esc) : Esc(esc.GetPin(), esc.GetEscData())
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

const std::shared_ptr<rpicomponents::pin::Pin>& rpicomponents::Esc::GetPin() const {
	return pin_;
}