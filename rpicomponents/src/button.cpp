#include "button.hpp"
#include "../external/doctest/doctest/doctest.h"

rpicomponents::Button::Button(const int &pin, const int &pud) : Component(COMPONENT_BUTTON), pin_{ rpicomponents::pin::PinCreator::CreatePin(pin, rpicomponents::pin::INPUT_MODE) }, pud_{pud}
{
	Initialize();
}

rpicomponents::Button::Button(int &&pin, int &&pud) : Component(COMPONENT_BUTTON), pin_(rpicomponents::pin::PinCreator::CreatePin(pin, rpicomponents::pin::INPUT_MODE)), pud_{ pud }
{
	Initialize();
}

rpicomponents::Button::Button(const Button& button) : Component(button.ToString()), pin_{ rpicomponents::pin::PinCreator::CreatePin(button.GetPin(), rpicomponents::pin::INPUT_MODE) }, 
pud_{ button.GetPUD() }
{
	Initialize();
}

void rpicomponents::Button::Initialize() const {
	if (!IsPUD(pud_)) throw new std::invalid_argument("given PUD is invalid!");
	const auto mode = pin_->OutputMode();
	if (mode != rpicomponents::pin::INPUT_MODE) throw new std::invalid_argument("given pin is on output mode; it must be on input mode for a button!");
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

const int& rpicomponents::Button::GetPUD() const {
	return pud_;
}

const int& rpicomponents::Button::GetPin() const
{
	return pin_->GetPin();
}

//***TEST CASES***

TEST_CASE("Creating button and checking it") {
	rpicomponents::Button btn(1, PUD_UP);
	CHECK(btn.ToString().compare(rpicomponents::COMPONENT_BUTTON) == 0);
	CHECK(btn.ToString().compare(rpicomponents::COMPONENT) == 0);
}