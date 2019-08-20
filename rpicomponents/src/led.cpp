#include "led.hpp"

rpicomponents::Led::Led(const int8_t& pin, const rpicomponents::pin::PIN_MODE& mode, bool onIfPinOn) : Component("led"), on_mode_{ onIfPinOn }, pin_{ rpicomponents::pin::PinFactory::CreatePin(pin, mode) }
{
	Initialize();
}

rpicomponents::Led::Led(int8_t&& pin, rpicomponents::pin::PIN_MODE&& mode, bool onIfPinOn) : Component("led"), on_mode_{ onIfPinOn }, pin_{ rpicomponents::pin::PinFactory::CreatePin(pin, mode) }
{
	Initialize();
}

void rpicomponents::Led::Initialize() {
	const auto mode = pin_.OutputMode();
	if (mode == rpicomponents::pin::INPUT_MODE) throw new std::invalid_argument("pin for led cannot be on input mode");
	AddPin(pin_.GetPin());
}

rpicomponents::Led::Led(const Led& led) : Component(led.ToString()), pin_{ rpicomponents::pin::PinFactory::CreatePin(led.GetPin(), led.GetPinMode()) }
{
	Initialize();
}

void rpicomponents::Led::TurnOn() const {
	on_mode_ ? pin_.OutputOn() : pin_.OutputOff();
}

void rpicomponents::Led::TurnOn(int16_t value) const {
	pin_.Output(value);
}

void rpicomponents::Led::TurnOff() const {
	on_mode_ ? pin_.OutputOff() : pin_.OutputOn();
}

bool rpicomponents::Led::IsOn() const {
	return on_mode_ ? pin_.IsOn() : !pin_.IsOn();
}

const int8_t& rpicomponents::Led::GetPin() const
{
	return pin_.GetPin();
}

bool rpicomponents::Led::IsOnIfPinHasPower() const
{
	return on_mode_;
}

const rpicomponents::pin::PIN_MODE& rpicomponents::Led::GetPinMode() const
{
	return pin_.OutputMode();
}
