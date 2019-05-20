#include "transistor.hpp"

using namespace std;
using namespace rpicomponents;
using namespace rpicomponents::pin;
using namespace rpicomponents::pin::utils;

Transistor::Transistor(const Pin* pin, TRANSISTOR_TYPE type) : Component("transistor"), pin_{pin}, type_{type}
{
	Initialize();
}

Transistor::Transistor(int pin, TRANSISTOR_TYPE type, PIN_MODE mode) : Component("transistor"), pin_{ PinFactory::CreatePin(pin, mode) }, type_{ type }
{
	Initialize();
}

void Transistor::Initialize() {
	if (pin_ == nullptr) throw new invalid_argument("pin is a nullptr! some internal error occured..");
	const auto mode = pin_->OutputMode();
	if (mode != INPUT_MODE) throw new invalid_argument("pin for transistor cannot be on input mode");
	AddPin(pin_->GetPin());
}

TRANSISTOR_TYPE Transistor::GetType() const {
	return type_;
}

void Transistor::TurnOn() const {
	if (pin_ == nullptr) return;
	type_ == NPN ? pin_->OutputOn() : pin_->OutputOff();
}

void Transistor::TurnOn(int value) const {
	if (pin_ == nullptr) return;
	pin_->Output(value);
}

void Transistor::TurnOff() const {
	if (pin_ == nullptr) return;
	type_ == PNP ? pin_->OutputOn() : pin_->OutputOff();
}

bool Transistor::IsOn() const {
	if (pin_ == nullptr) return false;
	return type_ == NPN ? pin_->IsOn() : !pin_->IsOn();
}