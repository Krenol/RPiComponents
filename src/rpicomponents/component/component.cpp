#include "component.hpp"

using namespace std;
using namespace rpicomponents;
using namespace rpicomponents::component;
using namespace rpicomponents::pin;

Component::Component(std::string componentName) : component_name_{ componentName }
{
}

Component::~Component() {

}

vector<int>::iterator Component::GetPinIterator(int pin) {
	return find(used_pins_.begin(), used_pins_.end(), pin);
}

bool Component::UsesPin(int pin) {
	lock_guard<mutex> lck{ mtx_ };
	auto check = GetPinIterator(pin);
	if (check == used_pins_.end()) {
		return false;
	}
	return true;
}

bool Component::UsesPins(vector<int> pins) {
	bool uses = true;
	for (auto pin : pins) {
		uses = uses && UsesPin(pin);
		if (!uses) return false;
	}
	return uses;
}

void Component::AddPin(int pin) {
	auto uses_pin = UsesPin(pin);
	if (!uses_pin) {
		lock_guard<mutex> lck{ mtx_ };
		used_pins_.push_back(pin);
	}
}

void Component::AddPins(vector<int> pins) {
	for (auto pin : pins) {
		AddPin(pin);
	}
}

bool Component::RemoveAllPins() {
	lock_guard<mutex> lck{ mtx_ };
	if (used_pins_.empty()) return false;
	used_pins_.clear();
	return true;
}

bool Component::RemovePin(int pin) {
	lock_guard<mutex> lck{ mtx_ };
	auto it = GetPinIterator(pin);
	if (it == used_pins_.end()) return false;
	used_pins_.erase(it);
	return true;
}

string Component::ToString() {
	return string(component_name_);
}