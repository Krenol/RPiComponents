#include "pinfactory.hpp"
#include "digitalpin.hpp"
#include "pwmpin.hpp"
#include "softpwmpin.hpp"
#include "softtonepin.hpp"
#include "inputpin.hpp"
#include <iostream>

/*
* Template class to check if pin pointer is really a rpicomponents::pin::Pin
*
* @param pin Pointer to a class other than pin
* @returns false qs overload guarantees pointer to be not a rpicomponents::pin::Pin
*/
template <class T>
bool IsPin(T* pin) { return false; } // normal case returns false 

/*
* Template class to check if pin pointer is really a rpicomponents::pin::Pin
*
* @param pin Pointer to a pin class
* @returns true as overload guarantees pointer to be a rpicomponents::pin::Pin
*/
template <>
bool IsPin(const rpicomponents::pin::Pin* pin) { return true; }  // but for Pin returns true

//variable definition
std::map<int8_t,const rpicomponents::pin::Pin*> rpicomponents::pin::PinFactory::created_pins_;
std::mutex rpicomponents::pin::PinFactory::mtx_;

bool rpicomponents::pin::PinFactory::CheckPinMode(const pin::Pin* pin, rpicomponents::pin::PIN_MODE mode)
{
	if (pin == nullptr || pin->OutputMode() != mode) return false;
	return true;
}

const rpicomponents::pin::Pin* rpicomponents::pin::PinFactory::CreatePinPointer(int8_t pin, rpicomponents::pin::PIN_MODE mode, int16_t maxOutputValue) {
	std::lock_guard<std::mutex> lck{ mtx_ };
	auto newPin = PinCreator(pin, mode, maxOutputValue);
	return newPin;
}

const rpicomponents::pin::Pin* rpicomponents::pin::PinFactory::PinCreator(int8_t pin, rpicomponents::pin::PIN_MODE outputMode, int16_t maxOutputValue) {
	auto exists = PinExists(pin);
	const Pin* newPin;
	if (exists) {
		std::cout << "Pin " << std::to_string(pin) << " already exists; returning created pin...\n";
		newPin = PinLoader(pin);
	}
	else {
		switch (outputMode)
		{
		case rpicomponents::pin::DIGITAL_MODE:
			newPin = new DigitalPin(pin);
			break;
		case rpicomponents::pin::PWM_MODE:
			newPin = new PWMPin(pin);
			break;
		case rpicomponents::pin::SOFTPWM_MODE:
			newPin = new SoftPWMPin(pin, maxOutputValue);
			break;
		case rpicomponents::pin::SOFTTONE_MODE:
			newPin = new SofttonePin(pin, maxOutputValue);
			break;
		case rpicomponents::pin::INPUT_MODE:
			newPin = new InputPin(pin);
			break;
		default:
			throw std::invalid_argument("Invalid PIN_MODE was passed for pin creation!");
		}
		AddPinToMap(newPin);
	}
	return newPin;
}

const rpicomponents::pin::Pin* rpicomponents::pin::PinFactory::LoadPinPointer(int8_t pin) {
	std::lock_guard<std::mutex> lck{ mtx_ };
	auto pinP = PinLoader(pin);
	return pinP;
}

bool rpicomponents::pin::PinFactory::CheckPin(const Pin* pin)
{
	if (pin == nullptr) {
		return false;
	}
	return IsPin(pin);
}

const rpicomponents::pin::Pin* rpicomponents::pin::PinFactory::PinLoader(int8_t pin) {
	auto exists = PinExists(pin);
	if (exists) {
		auto ptr = created_pins_[pin];
		if (CheckPin(ptr)) {
			return ptr;
		}
	}
	throw std::invalid_argument("Pin does not exists or pin pointer has been deleted. Create pin with the CreatePin(..) method!");
}

bool rpicomponents::pin::PinFactory::RemovePin(const Pin* pin) {
	auto pinNo = pin->GetPin();
	auto removed = RemovePin(pinNo);
	return removed;
}

bool rpicomponents::pin::PinFactory::RemovePin(int8_t pin) {
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

rpicomponents::pin::PinFactory::~PinFactory() {
	std::lock_guard<std::mutex> lck{ mtx_ };
	for (auto it : created_pins_) {
		delete it.second;
	}
	created_pins_.clear();
}

bool rpicomponents::pin::PinFactory::PinExists(int8_t pin) {
	auto count = created_pins_.count(pin);
	auto ptr = created_pins_[pin];
	if (count == 1 && ptr != nullptr) return true;
	return false;
}

void rpicomponents::pin::PinFactory::AddPinToMap(const Pin* pin) {
	auto pinNo = pin->GetPin();
	auto exists = PinExists(pinNo);
	if (exists) throw std::invalid_argument("Pin already exists and cannot be added to factory pointer storage!");
	created_pins_[pinNo] = pin;
}

rpicomponents::pin::PinFactory::PinFactory() {

}
