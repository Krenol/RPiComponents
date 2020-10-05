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
	pullUpDnControl(pin_->GetPin(), pud_);
	AddPin(pin_->GetPin());
}

bool rpicomponents::Button::IsPUD(int pud) const {
	if (pud == PUD_UP || pud == PUD_DOWN || pud == PUD_OFF) return true;
	return false;
}

bool rpicomponents::Button::IsPressed() const {
	auto val = pin_->ReadPinValue();
	if (val == LOW && pud_ == PUD_UP) return true;
	if (val == HIGH && pud_ == PUD_DOWN) return true;
	return false;
}

int rpicomponents::Button::GetPUD() const {
	return pud_;
}

int rpicomponents::Button::GetPin() const
{
	return pin_->GetPin();
}
