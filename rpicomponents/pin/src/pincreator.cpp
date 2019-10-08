#include "pincreator.hpp"
#include "digitalpin.hpp"
#include "inoutpin.hpp"
#include "inputpin.hpp"
#include "pwmpin.hpp"
#include "softpwmpin.hpp"
#include "softtonepin.hpp"


rpicomponents::pin::PinCreator& rpicomponents::pin::PinCreator::GetInstance() {
	static PinCreator instance;
	return instance;
}


std::unique_ptr<rpicomponents::pin::Pin> rpicomponents::pin::PinCreator::CreatePin(const int8_t& pin, rpicomponents::pin::PIN_MODE mode, const int16_t& maxOutputValue) {
	switch (mode)
	{
	case rpicomponents::pin::DIGITAL_MODE:
		return std::unique_ptr <rpicomponents::pin::Pin>(new rpicomponents::pin::DigitalPin(pin));

	case rpicomponents::pin::PWM_MODE:
		return std::unique_ptr <rpicomponents::pin::Pin>(new rpicomponents::pin::PWMPin(pin));

	case rpicomponents::pin::SOFTPWM_MODE:
		return std::unique_ptr <rpicomponents::pin::Pin>(new rpicomponents::pin::SoftPWMPin(pin, maxOutputValue));

	case rpicomponents::pin::SOFTTONE_MODE:
		return std::unique_ptr <rpicomponents::pin::Pin>(new rpicomponents::pin::SofttonePin(pin, maxOutputValue));

	case rpicomponents::pin::INPUT_MODE:
		return std::unique_ptr <rpicomponents::pin::Pin>(new rpicomponents::pin::InputPin(pin));

	case rpicomponents::pin::IN_OUT_MODE:
		return std::unique_ptr <rpicomponents::pin::Pin>(new rpicomponents::pin::InOutPin(pin));

	default:
		throw std::invalid_argument("Invalid PIN_MODE was passed for pin creation!");
	}
}

bool rpicomponents::pin::PinCreator::CheckPinMode(std::unique_ptr<rpicomponents::pin::Pin> const &pin, rpicomponents::pin::PIN_MODE mode) {
	if (pin.get()->OutputMode() == mode) return true;
	return false;
}