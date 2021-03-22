#include "transistor.hpp"




rpicomponents::Transistor::Transistor(int pin, pin::PIN_MODE pin_mode, int pin_max_val, TRANSISTOR_TYPE type) : Component(COMPONENT_TRANSISTOR), type_{ type }
{

	if (pin_mode == pin::INPUT_MODE || pin_mode == pin::IN_OUT_MODE) throw new std::invalid_argument("pin for transistor cannot be on input mode");
    pin_ = pin::PinCreator::CreatePin(pin, pin_mode, pin_max_val);
    AddPin(pin);
}

rpicomponents::Transistor::Transistor(const Transistor& transistor) : 
    Transistor(transistor.GetPin(), transistor.GetPinMode(), transistor.GetMaxOutValue(), transistor.GetType())
{

}

rpicomponents::TRANSISTOR_TYPE rpicomponents::Transistor::GetType() const {
	return type_;
}

void rpicomponents::Transistor::TurnOn() const {
	
    type_ == NPN ? pin_->OutputOn() : pin_->OutputOff();
}

void rpicomponents::Transistor::TurnOn(int value) const {
	
    pin_->Output(value);
}

void rpicomponents::Transistor::TurnOff() const {
	
    type_ == PNP ? pin_->OutputOn() : pin_->OutputOff();
}

bool rpicomponents::Transistor::IsOn() const {
	
    return type_ == NPN ? pin_->IsOn() : !pin_->IsOn();
}

int rpicomponents::Transistor::GetPin() const
{
    return pin_->GetPin();
}

pin::PIN_MODE rpicomponents::Transistor::GetPinMode() const
{
	return pin_->OutputMode();
}

int rpicomponents::Transistor::GetMaxOutValue() const {
	return pin_->GetMaxOutValue();
}