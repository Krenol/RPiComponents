#include "led.hpp"

using namespace std;
using namespace rpicomponents;
using namespace rpicomponents::component;
using namespace rpicomponents::pin;

Led::Led(Pin* pin, bool onIfPinOn) : Component("led"), pin_{ pin }, on_mode_{ onIfPinOn }
{
	Initialize();
}

Led::Led(int pin, PIN_MODE outputMode, bool onIfPinOn) : Component("led"), on_mode_{ onIfPinOn }, pin_{ PinFactory::CreatePin(pin, outputMode) }
{
	Initialize();
}

void Led::Initialize() {
	if (pin_ == nullptr) throw new invalid_argument("pin is a nullptr! some internal error occured..");
	const auto mode = pin_->OutputMode();
	if (mode == INPUT_MODE) throw new invalid_argument("pin for led cannot be on input mode");
	AddPin(pin_->GetPin());
}

void Led::TurnOn() {
	if (pin_ == nullptr) return;
	on_mode_ ? pin_->OutputOn() : pin_->OutputOff();
}

void Led::TurnOn(int value) {
	if (pin_ == nullptr) return;
	pin_->Output(value);
}

void Led::TurnOff() {
	if (pin_ == nullptr) return;
	on_mode_ ? pin_->OutputOff() : pin_->OutputOn();
}

bool Led::IsOn() {
	if (pin_ == nullptr) return false;
	if (on_mode_) return on_mode_ && pin_->IsOn(); //if pin has power the led is on
	return on_mode_ && !pin_->IsOn(); //if pin has no power the led is on
}