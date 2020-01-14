#include "transistor.hpp"

void rpicomponents::Transistor::Initialize() {
	
    auto mode = pin_->OutputMode();
    if (mode == rpicomponents::pin::INPUT_MODE || mode == rpicomponents::pin::IN_OUT_MODE) throw new std::invalid_argument("pin for transistor cannot be on input mode");
    AddPin(pin_->GetPin());
}


rpicomponents::Transistor::Transistor(std::shared_ptr<pin::Pin> pin, TRANSISTOR_TYPE type) : Component(COMPONENT_TRANSISTOR),
pin_{ pin }, type_{ type }
{
	Initialize();
}

rpicomponents::Transistor::Transistor(const Transistor& transistor) : Transistor(transistor.GetPin(), transistor.GetType())
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

const std::shared_ptr<rpicomponents::pin::Pin>& rpicomponents::Transistor::GetPin() const
{
    return pin_;
}
