#include "motor.hpp"

bool rpicomponents::Motor::ValidEnablePin(int pin) const
{
	auto pins = l293d_->GetEnablePins();

	return (pins.enable_pin1_ == pin || pins.enable_pin2_ == pin);
}

bool rpicomponents::Motor::ValidInPin(int pin) const
{
	auto pins = l293d_->GetInPins();

	return (pins.in_pin1_ == pin || pins.in_pin1_ == pin || pins.in_pin3_ == pin || pins.in_pin4_ == pin);
}

const rpicomponents::EnablePinStruct& rpicomponents::Motor::GetEnablePins() const
{
    return l293d_->GetEnablePins();
}

const rpicomponents::InPinStruct& rpicomponents::Motor::GetInPins() const
{
    return l293d_->GetInPins();
}

rpicomponents::Motor::Motor(const EnablePinStruct& enablePins, const InPinStruct& in_pins) : Component(COMPONENT_MOTOR), l293d_{ std::unique_ptr<rpicomponents::L293D>(new L293D(enablePins, in_pins))}
{
}

rpicomponents::Motor::Motor(int enable_pin1, int enable_pin2, rpicomponents::pin::PIN_MODE enable_pin1_mode, rpicomponents::pin::PIN_MODE enable_pin2_mode, 
    int max_output_enable_pin1, int max_output_enable_pin2, int in_pin1, int in_pin2, int in_pin3, int in_pin4) : Component(COMPONENT_MOTOR),
    l293d_{ std::unique_ptr<rpicomponents::L293D>(new L293D(enable_pin1, enable_pin2, enable_pin1_mode, enable_pin2_mode,
	max_output_enable_pin1, max_output_enable_pin2, in_pin1, in_pin2, in_pin3, in_pin4)) }
{
}
