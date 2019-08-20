#include "transistor.hpp"

void rpicomponents::Transistor::Initialize() {
	
	const auto mode = pin_.OutputMode();
	if (mode != rpicomponents::pin::INPUT_MODE) throw new std::invalid_argument("pin for transistor cannot be on input mode");
	AddPin(pin_.GetPin());
}

rpicomponents::Transistor::Transistor(const int8_t& pin, const TRANSISTOR_TYPE& type, const rpicomponents::pin::PIN_MODE& mode) : Component("transistor"),
pin_{ rpicomponents::pin::PinFactory::CreatePin(pin, mode) }, type_{ type }
{
	Initialize();
}

rpicomponents::Transistor::Transistor(int8_t&& pin, TRANSISTOR_TYPE&& type, rpicomponents::pin::PIN_MODE&& mode) : Component("transistor"),
pin_{ rpicomponents::pin::PinFactory::CreatePin(pin, mode) }, type_{ type }
{
	Initialize();
}

rpicomponents::Transistor::Transistor(const Transistor& transistor) : Component(transistor.ToString()),
pin_{ rpicomponents::pin::PinFactory::CreatePin(transistor.GetPin(), transistor.GetPinMode()) }, type_{ transistor.GetType() }
{
	Initialize();
}

const rpicomponents::TRANSISTOR_TYPE& rpicomponents::Transistor::GetType() const {
	return type_;
}

void rpicomponents::Transistor::TurnOn() const {
	
	type_ == NPN ? pin_.OutputOn() : pin_.OutputOff();
}

void rpicomponents::Transistor::TurnOn(int16_t value) const {
	
	pin_.Output(value);
}

void rpicomponents::Transistor::TurnOff() const {
	
	type_ == PNP ? pin_.OutputOn() : pin_.OutputOff();
}

bool rpicomponents::Transistor::IsOn() const {
	
	return type_ == NPN ? pin_.IsOn() : !pin_.IsOn();
}

const int8_t& rpicomponents::Transistor::GetPin() const
{
	return pin_.GetPin();
}

const rpicomponents::pin::PIN_MODE& rpicomponents::Transistor::GetPinMode() const
{
	return pin_.OutputMode();
}
