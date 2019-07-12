#include "pinfactory.hpp"
#include "digitalpin.hpp"
#include "pwmpin.hpp"
#include "softpwmpin.hpp"
#include "softtonepin.hpp"
#include "inputpin.hpp"
#include <iostream>


using namespace rpicomponents::pin;
using namespace rpicomponents::pin::utils;

//variable definition
std::map<int8_t,const Pin*> PinFactory::created_pins_;
std::mutex PinFactory::mtx_;

bool PinFactory::CheckPinMode(const pin::Pin* pin, pin::utils::PIN_MODE mode)
{
	if (pin == nullptr || pin->OutputMode() != mode) return false;
	return true;
}

const Pin* PinFactory::CreatePin(int8_t pin, PIN_MODE mode, int16_t maxOutputValue) {
	std::lock_guard<std::mutex> lck{ mtx_ };
	auto newPin = PinCreator(pin, mode, maxOutputValue);
	return newPin;
}

const Pin* PinFactory::PinCreator(int8_t pin, PIN_MODE outputMode, int16_t maxOutputValue) {
	auto exists = PinExists(pin);
	const Pin* newPin;
	if (exists) {
		std::cout << "Pin " << std::to_string(pin) << " already exists; returning created pin...\n";
		newPin = PinLoader(pin);
	}
	else {
		switch (outputMode)
		{
		case rpicomponents::pin::utils::DIGITAL_MODE:
			newPin = new DigitalPin(pin);
			break;
		case rpicomponents::pin::utils::PWM_MODE:
			newPin = new PWMPin(pin);
			break;
		case rpicomponents::pin::utils::SOFTPWM_MODE:
			newPin = new SoftPWMPin(pin, maxOutputValue);
			break;
		case rpicomponents::pin::utils::SOFTTONE_MODE:
			newPin = new SofttonePin(pin, maxOutputValue);
			break;
		case rpicomponents::pin::utils::INPUT_MODE:
			newPin = new InputPin(pin);
			break;
		default:
			throw std::invalid_argument("Invalid PIN_MODE was passed for pin creation!");
		}
		AddPinToMap(newPin);
	}
	return newPin;
}

const Pin* PinFactory::LoadPin(int8_t pin) {
	std::lock_guard<std::mutex> lck{ mtx_ };
	auto pinP = PinLoader(pin);
	return pinP;
}

const Pin* PinFactory::PinLoader(int8_t pin) {
	auto exists = PinExists(pin);
	if (exists) {
		auto ptr = created_pins_[pin];
		return ptr;
	}
	else throw std::invalid_argument("Pin does not exists. Create it with the CreatePin(..) method call first");
}

bool PinFactory::RemovePin(const Pin* pin) {
	auto pinNo = pin->GetPin();
	auto removed = RemovePin(pinNo);
	return removed;
}

bool PinFactory::RemovePin(int8_t pin) {
	std::lock_guard<std::mutex> lck{ mtx_ };
	auto exists = PinExists(pin);
	if (!exists) return false;
	try {
		auto itr = created_pins_.find(pin);
		delete itr->second;
		created_pins_.erase(itr);
		return true;
	}
	catch (std::exception e) {
		throw e;
		return false;
	}
}

PinFactory::~PinFactory() {
	std::lock_guard<std::mutex> lck{ mtx_ };
	for (auto it : created_pins_) {
		delete it.second;
	}
	created_pins_.clear();
}

bool PinFactory::PinExists(int8_t pin) {
	auto count = created_pins_.count(pin);
	auto ptr = created_pins_[pin];
	if (count == 1 && ptr != nullptr) return true;
	return false;
}

void PinFactory::AddPinToMap(const Pin* pin) {
	auto pinNo = pin->GetPin();
	auto exists = PinExists(pinNo);
	if (exists) throw std::invalid_argument("Pin already exists and cannot be added to factory pointer storage!");
	created_pins_[pinNo] = pin;
}

PinFactory::PinFactory() {
    //add code here
}
