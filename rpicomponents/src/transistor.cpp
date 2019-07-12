#include "transistor.hpp"



using namespace rpicomponents::pin;
using namespace rpicomponents::pin::utils;

rpicomponents::Transistor::Transistor(const Pin* pin, TRANSISTOR_TYPE type) : Component("transistor"), pin_{pin}, type_{type}
{
	Initialize();
}

rpicomponents::Transistor::Transistor(int8_t pin, TRANSISTOR_TYPE type, PIN_MODE mode) : Component("transistor"), pin_{ PinFactory::CreatePin(pin, mode) }, type_{ type }
{
	Initialize();
}

void rpicomponents::Transistor::Initialize() {
	if (pin_ == nullptr) throw new std::invalid_argument("pin is a nullptr! some internal error occured..");
	const auto mode = pin_->OutputMode();
	if (mode != INPUT_MODE) throw new std::invalid_argument("pin for transistor cannot be on input mode");
	AddPin(pin_->GetPin());
}

rpicomponents::TRANSISTOR_TYPE rpicomponents::Transistor::GetType() const {
	return type_;
}

void rpicomponents::Transistor::TurnOn() const {
	if (pin_ == nullptr) return;
	type_ == NPN ? pin_->OutputOn() : pin_->OutputOff();
}

void rpicomponents::Transistor::TurnOn(int16_t value) const {
	if (pin_ == nullptr) return;
	pin_->Output(value);
}

void rpicomponents::Transistor::TurnOff() const {
	if (pin_ == nullptr) return;
	type_ == PNP ? pin_->OutputOn() : pin_->OutputOff();
}

bool rpicomponents::Transistor::IsOn() const {
	if (pin_ == nullptr) return false;
	return type_ == NPN ? pin_->IsOn() : !pin_->IsOn();
}