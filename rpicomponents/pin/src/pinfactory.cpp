#include "pinfactory.hpp"

using namespace std;
using namespace rpicomponents;
using namespace rpicomponents::pin;

//variable definition
map<int,const Pin*> PinFactory::created_pins_;
mutex mtx_;

const Pin* PinFactory::CreatePin(int pin, PIN_MODE outputMode, int maxOutputValue) {
	lock_guard<mutex> lck{ mtx_ };
	auto newPin = PinCreator(pin, outputMode, maxOutputValue);
	return newPin;
}

const Pin* PinFactory::PinCreator(int pin, PIN_MODE outputMode, int maxOutputValue) {
	auto exists = PinExists(pin);
	const Pin* newPin;
	if (exists) {
		std::cout << "Pin " << to_string(pin) << " already exists; returning created pin...\n";
		newPin = PinLoader(pin);
	}
	else {
		switch (outputMode)
		{
		case rpicomponents::pin::DIGITAL:
			newPin = new DigitalPin(pin);
			break;
		case rpicomponents::pin::PWM:
			newPin = new PWMPin(pin);
			break;
		case rpicomponents::pin::SOFTPWM:
			newPin = new SoftPWMPin(pin, maxOutputValue);
			break;
		case rpicomponents::pin::SOFTTONE:
			newPin = new SofttonePin(pin, maxOutputValue);
			break;
		case rpicomponents::pin::INPUT_MODE:
			newPin = new InputPin(pin);
			break;
		default:
			throw invalid_argument("Invalid PIN_MODE was passed for pin creation!");
		}
		AddPinToMap(newPin);
	}
	return newPin;
}

const Pin* PinFactory::LoadPin(int pin) {
	lock_guard<mutex> lck{ mtx_ };
	auto pinP = PinLoader(pin);
	return pinP;
}

const Pin* PinFactory::PinLoader(int pin) {
	auto exists = PinExists(pin);
	if (exists) {
		auto ptr = created_pins_[pin];
		return ptr;
	}
	else throw invalid_argument("Pin does not exists. Create it with the CreatePin(..) method call first");
}

bool PinFactory::RemovePin(const Pin* pin) {
	auto pinNo = pin->GetPin();
	auto removed = RemovePin(pinNo);
	return removed;
}

bool PinFactory::RemovePin(int pin) {
	lock_guard<mutex> lck{ mtx_ };
	auto exists = PinExists(pin);
	if (!exists) return false;
	try {
		auto itr = created_pins_.find(pin);
		delete itr->second;
		created_pins_.erase(itr);
		return true;
	}
	catch (exception e) {
		throw e;
		return false;
	}
}

PinFactory::~PinFactory() {
	lock_guard<mutex> lck{ mtx_ };
	for (auto it : created_pins_) {
		delete it.second;
	}
	created_pins_.clear();
}

bool PinFactory::PinExists(int pin) {
	auto count = created_pins_.count(pin);
	auto ptr = created_pins_[pin];
	if (count == 1 && ptr != nullptr) return true;
	return false;
}

void PinFactory::AddPinToMap(const Pin* pin) {
	auto pinNo = pin->GetPin();
	auto exists = PinExists(pinNo);
	if (exists) throw invalid_argument("Pin already exists and cannot be added to factory pointer storage!");
	created_pins_[pinNo] = pin;
}

PinFactory::PinFactory() {
    //add code here
}
