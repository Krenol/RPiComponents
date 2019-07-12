#include "led.hpp"



using namespace rpicomponents::pin;
using namespace rpicomponents::pin::utils;

rpicomponents::Led::Led(const Pin* pin, bool onIfPinOn) : Component("led"), pin_{ pin }, on_mode_{ onIfPinOn }
{
	Initialize();
}

rpicomponents::Led::Led(int8_t pin, PIN_MODE mode, bool onIfPinOn) : Component("led"), on_mode_{ onIfPinOn }, pin_{ PinFactory::CreatePin(pin, mode) }
{
	Initialize();
}

void rpicomponents::Led::Initialize() {
	if (pin_ == nullptr) throw new std::invalid_argument("pin is a nullptr! some internal error occured..");
	const auto mode = pin_->OutputMode();
	if (mode == INPUT_MODE) throw new std::invalid_argument("pin for led cannot be on input mode");
	AddPin(pin_->GetPin());
}

void rpicomponents::Led::TurnOn() const {
	if (pin_ == nullptr) return;
	on_mode_ ? pin_->OutputOn() : pin_->OutputOff();
}

void rpicomponents::Led::TurnOn(int16_t value) const {
	if (pin_ == nullptr) return;
	pin_->Output(value);
}

void rpicomponents::Led::TurnOff() const {
	if (pin_ == nullptr) return;
	on_mode_ ? pin_->OutputOff() : pin_->OutputOn();
}

bool rpicomponents::Led::IsOn() const {
	if (pin_ == nullptr) return false;
	return on_mode_ ? pin_->IsOn() : !pin_->IsOn();
}