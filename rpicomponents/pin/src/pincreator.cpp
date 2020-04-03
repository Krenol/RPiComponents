#include "pincreator.hpp"
#include "digitalpin.hpp"
#include "inoutpin.hpp"
#include "inputpin.hpp"
#include "pwmpin.hpp"
#include "softpwmpin.hpp"
#include "softtonepin.hpp"

pinmap_t  rpicomponents::pin::PinCreator::func_map_ = {
    {rpicomponents::pin::DIGITAL_MODE, *CreateDigitalPin},
    {rpicomponents::pin::INPUT_MODE, *CreateInputPin},
    {rpicomponents::pin::PWM_MODE, *CreatePwmPin},
    {rpicomponents::pin::SOFTPWM_MODE, *CreateSoftPwmPin},
    {rpicomponents::pin::SOFTTONE_MODE, *CreateSofttonePin},
    {rpicomponents::pin::IN_OUT_MODE, *CreateInOutPin},
};

rpicomponents::pin::PinCreator& rpicomponents::pin::PinCreator::GetInstance() {
	static PinCreator instance;
	return instance;
}



std::shared_ptr<rpicomponents::pin::Pin> rpicomponents::pin::PinCreator::CreatePin(int pin, rpicomponents::pin::PIN_MODE mode, int maxOutputValue) {
    auto f = func_map_.find(mode);
    if (f != func_map_.end()) {
        return (*f->second)(pin, maxOutputValue);
    }

    throw std::invalid_argument("Invalid PIN_MODE \"" + std::to_string(mode) +  "\" was passed for pin creation!");
}

bool rpicomponents::pin::PinCreator::CheckPinMode(std::shared_ptr<rpicomponents::pin::Pin> const &pin, rpicomponents::pin::PIN_MODE mode) {
	if (pin.get()->OutputMode() == mode) return true;
	return false;
}

std::shared_ptr<rpicomponents::pin::Pin> rpicomponents::pin::PinCreator::CreateDigitalPin(int pin, int maxOutputValue)
{
	return std::shared_ptr<Pin>(new rpicomponents::pin::DigitalPin(pin));
}

std::shared_ptr<rpicomponents::pin::Pin> rpicomponents::pin::PinCreator::CreateInputPin(int pin, int maxOutputValue)
{
    return std::shared_ptr<Pin>(new rpicomponents::pin::InputPin(pin));
}

std::shared_ptr<rpicomponents::pin::Pin> rpicomponents::pin::PinCreator::CreateInOutPin(int pin, int maxOutputValue) {
    return std::shared_ptr<Pin>(new rpicomponents::pin::InOutPin(pin));
}

std::shared_ptr<rpicomponents::pin::Pin> rpicomponents::pin::PinCreator::CreatePwmPin(int pin, int maxOutputValue) {
    return std::shared_ptr<Pin>(new rpicomponents::pin::PWMPin(pin));
}

std::shared_ptr<rpicomponents::pin::Pin> rpicomponents::pin::PinCreator::CreateSoftPwmPin(int pin, int maxOutputValue) {
    return std::shared_ptr<Pin>(new rpicomponents::pin::SoftPWMPin(pin, maxOutputValue));
}

std::shared_ptr<rpicomponents::pin::Pin> rpicomponents::pin::PinCreator::CreateSofttonePin(int pin, int maxOutputValue) {
    return std::shared_ptr<Pin>(new rpicomponents::pin::SofttonePin(pin, maxOutputValue));
}
