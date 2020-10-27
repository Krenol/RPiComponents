#include "button.hpp"


rpicomponents::Button::Button(int pin, int pud) : Component(COMPONENT_BUTTON), pud_{pud}
{
	pin_ = pin::PinCreator::CreateInputPin(pin, 1);
	Initialize();
}

rpicomponents::Button::Button(const Button& button) : Component(button.ToString()), pud_{ button.GetPUD() }
{
	pin_ = pin::PinCreator::CreateInputPin(button.GetPin(), 1);
	Initialize();
}

void rpicomponents::Button::Initialize() {
	if (!IsPUD(pud_)) throw new std::invalid_argument("given PUD is invalid!");
	gpioSetPullUpDown(pin_->GetPin(), pud_);
	AddPin(pin_->GetPin());
}

bool rpicomponents::Button::IsPUD(int pud) const {
	if (pud == PI_PUD_UP || pud == PI_PUD_DOWN || pud == PI_PUD_OFF) return true;
	return false;
}

bool rpicomponents::Button::IsPressed() const {
	auto val = pin_->ReadPinValue();
	if (val == 0 && pud_ == PI_PUD_UP) return true;
	if (val == 1 && pud_ == PI_PUD_DOWN) return true;
	return false;
}

int rpicomponents::Button::GetPUD() const {
	return pud_;
}

int rpicomponents::Button::GetPin() const
{
	return pin_->GetPin();
}
