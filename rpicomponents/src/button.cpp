#include "button.hpp"

using namespace std;
using namespace rpicomponents;
using namespace rpicomponents::pin;
using namespace rpicomponents::pin::utils;

Button::Button(const Pin* pin, int8_t pud) : Component("button"), pin_{pin}, pud_{pud}
{
	Initialize();
}

Button::Button(int8_t pin, int8_t pud) : Component("button"), pin_(PinFactory::CreatePin(pin, INPUT_MODE)), pud_{ pud }
{
	Initialize();
}

void Button::Initialize() const {
	if (!IsPUD(pud_)) throw new invalid_argument("given PUD is invalid!");
	const auto mode = pin_->OutputMode();
	if (mode != INPUT_MODE) throw new invalid_argument("given pin is on output mode; it must be on input mode for a button!");
	pullUpDnControl(pin_->GetPin(), pud_);
	AddPin(pin_->GetPin());
}

bool Button::IsPUD(int8_t pud) const {
	if (pud == PUD_UP || pud == PUD_DOWN || pud == PUD_OFF) return true;
	return false;
}

bool Button::IsPressed() const {
	auto val = pin_->ReadPinValue();
	if (val == LOW && pud_ == PUD_UP) return true;
	if (val == HIGH && pud_ == PUD_DOWN) return true;
	return false;
}

int8_t Button::GetPUD() const {
	return pud_;
}