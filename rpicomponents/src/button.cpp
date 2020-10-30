#include "button.hpp"
#include <pigpio.h>

namespace rpicomponents
{
	Button::Button(int pin, int pud) : Component(COMPONENT_BUTTON), pud_{pud}
	{
		pin_ = pin::PinCreator::CreateInputPin(pin, 1);
		Initialize();
	}

	Button::Button(const Button& button) : Component(button.ToString()), pud_{ button.GetPUD() }
	{
		pin_ = pin::PinCreator::CreateInputPin(button.GetPin(), 1);
		Initialize();
	}

	void Button::Initialize() {
		if (!IsPUD(pud_)) throw new std::invalid_argument("given PUD is invalid!");
		gpioSetPullUpDown(pin_->GetPin(), pud_);
		AddPin(pin_->GetPin());
	}

	bool Button::IsPUD(int pud) const {
		if (pud == PI_PUD_UP || pud == PI_PUD_DOWN || pud == PI_PUD_OFF) return true;
		return false;
	}

	bool Button::IsPressed() const {
		auto val = pin_->ReadPinValue();
		if (val == 0 && pud_ == PI_PUD_UP) return true;
		if (val == 1 && pud_ == PI_PUD_DOWN) return true;
		return false;
	}

	int Button::GetPUD() const {
		return pud_;
	}

	int Button::GetPin() const
	{
		return pin_->GetPin();
	}
	
	void Button::RegisterCallback(const gpio_cb& cb_func) 
	{
		cb_ = cb_func;
		gpioSetAlertFuncEx(GetPin(), AlertFunction, (void *)this);
	}

	void Button::AlertFunction(int gpio, int level, uint32_t tick, void *btn) 
	{
		auto b = (Button*) btn;
		b->cb_(gpio, level, b->ToString());
	}
}