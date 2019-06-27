#include "component.hpp"

using namespace std;
using namespace rpicomponents;
using namespace rpicomponents::pin;
using namespace rpicomponents::pin::utils;

Component::Component(std::string componentName) : component_name_{ componentName }
{
}

void Component::CheckPinStatus(const Pin* pin, PIN_MODE mode) const
{
	CheckPinStatus(pin, std::vector<PIN_MODE>{ mode });
}

void Component::CheckPinStatus(const pin::Pin* pin, std::vector<pin::utils::PIN_MODE> mode) const
{
	lock_guard<mutex> grd(mtx_);
	if (pin == nullptr) throw new invalid_argument("pin of component is null");
	bool valid = false;
	string modes = "";
	for (int i = 0; i < mode.size(); i++) {
		valid = PinFactory::CheckPinMode(pin, mode[i]);
		if (valid) return;
		modes += (i == 0 ? "" : ", ") + mode[i];
	}
	throw new invalid_argument("pin is not of PIN_MODES " + modes);
}

Component::~Component() {

}

vector<int8_t>::iterator Component::GetPinIterator(int8_t pin) const {
	return find(used_pins_.begin(), used_pins_.end(), pin);
}

bool Component::UsesPin(int8_t pin) const {
	lock_guard<mutex> lck{ mtx_ };
	auto check = GetPinIterator(pin);
	if (check == used_pins_.end()) {
		return false;
	}
	return true;
}

bool Component::UsesPins(vector<int8_t> pins) const {
	bool uses = true;
	for (auto pin : pins) {
		uses = uses && UsesPin(pin);
		if (!uses) return false;
	}
	return uses;
}

void Component::AddPin(int8_t pin) const {
	auto uses_pin = UsesPin(pin);
	if (!uses_pin) {
		lock_guard<mutex> lck{ mtx_ };
		used_pins_.push_back(pin);
	}
}

void Component::AddPins(vector<int8_t> pins) const {
	for (auto pin : pins) {
		AddPin(pin);
	}
}

bool Component::RemoveAllPins() const {
	lock_guard<mutex> lck{ mtx_ };
	if (used_pins_.empty()) return false;
	used_pins_.clear();
	return true;
}

bool Component::RemovePin(int8_t pin) const {
	lock_guard<mutex> lck{ mtx_ };
	auto it = GetPinIterator(pin);
	if (it == used_pins_.end()) return false;
	used_pins_.erase(it);
	return true;
}

string Component::ToString() const {
	return string(component_name_);
}