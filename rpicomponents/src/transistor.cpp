#include "transistor.hpp"






rpicomponents::Transistor::Transistor(const rpicomponents::pin::Pin* pin, TRANSISTOR_TYPE type) : Component("transistor"), pin_{pin}, type_{type}
{
	Initialize();
}

rpicomponents::Transistor::Transistor(int8_t pin, TRANSISTOR_TYPE type, rpicomponents::pin::utils::PIN_MODE mode) : Component("transistor"), 
	pin_{ rpicomponents::pin::PinFactory::CreatePin(pin, mode) }, type_{ type }
{
	Initialize();
}

void rpicomponents::Transistor::Initialize() {
	CheckPin(pin_);
	const auto mode = pin_->OutputMode();
	if (mode != rpicomponents::pin::utils::INPUT_MODE) throw new std::invalid_argument("pin for transistor cannot be on input mode");
	AddPin(pin_->GetPin());
}

rpicomponents::TRANSISTOR_TYPE rpicomponents::Transistor::GetType() const {
	return type_;
}

void rpicomponents::Transistor::TurnOn() const {
	CheckPin(pin_);
	type_ == NPN ? pin_->OutputOn() : pin_->OutputOff();
}

void rpicomponents::Transistor::TurnOn(int16_t value) const {
	CheckPin(pin_);
	pin_->Output(value);
}

void rpicomponents::Transistor::TurnOff() const {
	CheckPin(pin_);
	type_ == PNP ? pin_->OutputOn() : pin_->OutputOff();
}

bool rpicomponents::Transistor::IsOn() const {
	CheckPin(pin_);
	return type_ == NPN ? pin_->IsOn() : !pin_->IsOn();
}