#include "button.hpp"


rpicomponents::Button::Button(const rpicomponents::pin::Pin* pin, int8_t pud) : Component("button"), pin_{pin}, pud_{pud}
{
	Initialize();
}

rpicomponents::Button::Button(int8_t pin, int8_t pud) : Component("button"), pin_(rpicomponents::pin::PinFactory::CreatePin(pin, rpicomponents::pin::INPUT_MODE)), pud_{ pud }
{
	Initialize();
}

void rpicomponents::Button::Initialize() const {
	CheckPin(pin_);
	if (!IsPUD(pud_)) throw new std::invalid_argument("given PUD is invalid!");
	const auto mode = pin_->OutputMode();
	if (mode != rpicomponents::pin::INPUT_MODE) throw new std::invalid_argument("given pin is on output mode; it must be on input mode for a button!");
	pullUpDnControl(pin_->GetPin(), pud_);
	AddPin(pin_->GetPin());
}

bool rpicomponents::Button::IsPUD(int8_t pud) const {
	if (pud == PUD_UP || pud == PUD_DOWN || pud == PUD_OFF) return true;
	return false;
}

bool rpicomponents::Button::IsPressed() const {
	CheckPin(pin_);
	auto val = pin_->ReadPinValue();
	if (val == LOW && pud_ == PUD_UP) return true;
	if (val == HIGH && pud_ == PUD_DOWN) return true;
	return false;
}

int8_t rpicomponents::Button::GetPUD() const {
	return pud_;
}