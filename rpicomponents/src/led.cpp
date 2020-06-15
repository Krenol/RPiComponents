#include "led.hpp"
#include <stdexcept>



void rpicomponents::Led::Initialize() {
	const auto mode = pin_->OutputMode();
	if (mode == pin::INPUT_MODE) throw new std::invalid_argument("pin for led cannot be on input mode");
	AddPin(pin_->GetPin());
}

rpicomponents::Led::Led(std::shared_ptr<pin::Pin> pin, const bool& onIfPinOn) : Component(COMPONENT_LED), on_mode_{ onIfPinOn }, pin_{ pin }
{
	Initialize();
}

rpicomponents::Led::Led(const Led& led) : Led(led.GetPin(), led.IsOnIfPinHasPower())
{

}

void rpicomponents::Led::TurnOn() const {
	on_mode_ ? pin_->OutputOn() : pin_->OutputOff();
}

void rpicomponents::Led::TurnOn(int value) const {
	pin_->Output(value);
}

void rpicomponents::Led::TurnOff() const {
	on_mode_ ? pin_->OutputOff() : pin_->OutputOn();
}

bool rpicomponents::Led::IsOn() const {
	return on_mode_ ? pin_->IsOn() : !pin_->IsOn();
}

const std::shared_ptr<pin::Pin>& rpicomponents::Led::GetPin() const
{
	return pin_;
}

bool rpicomponents::Led::IsOnIfPinHasPower() const
{
	return on_mode_;
}

pin::PIN_MODE rpicomponents::Led::GetPinMode() const
{
	return pin_->OutputMode();
}
