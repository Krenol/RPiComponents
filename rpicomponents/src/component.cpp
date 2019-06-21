#include "component.hpp"

using namespace std;
using namespace rpicomponents;
using namespace rpicomponents::pin;
using namespace rpicomponents::pin::utils;

Component::Component(std::string componentName) : component_name_{ componentName }
{
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