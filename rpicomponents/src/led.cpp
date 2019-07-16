#include "led.hpp"






rpicomponents::Led::Led(const rpicomponents::pin::Pin* pin, bool onIfPinOn) : Component("led"), pin_{ pin }, on_mode_{ onIfPinOn }
{
	Initialize();
}

rpicomponents::Led::Led(int8_t pin, rpicomponents::pin::utils::PIN_MODE mode, bool onIfPinOn) : Component("led"), on_mode_{ onIfPinOn }, pin_{ rpicomponents::pin::PinFactory::CreatePin(pin, mode) }
{
	Initialize();
}

void rpicomponents::Led::Initialize() {
	CheckPin(pin_);
	const auto mode = pin_->OutputMode();
	if (mode == rpicomponents::pin::utils::INPUT_MODE) throw new std::invalid_argument("pin for led cannot be on input mode");
	AddPin(pin_->GetPin());
}

void rpicomponents::Led::TurnOn() const {
	CheckPin(pin_);
	on_mode_ ? pin_->OutputOn() : pin_->OutputOff();
}

void rpicomponents::Led::TurnOn(int16_t value) const {
	CheckPin(pin_);
	pin_->Output(value);
}

void rpicomponents::Led::TurnOff() const {
	CheckPin(pin_);
	on_mode_ ? pin_->OutputOff() : pin_->OutputOn();
}

bool rpicomponents::Led::IsOn() const {
	CheckPin(pin_);
	return on_mode_ ? pin_->IsOn() : !pin_->IsOn();
}