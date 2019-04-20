#include "component.hpp"

using namespace std;
using namespace rpicomponents;
using namespace rpicomponents::component;

Component::~Component() {

}

vector<int>::iterator Component::GetPinIterator(int pin) {
	return find(used_pins_.begin(), used_pins_.end(), pin);
}

bool Component::UsesPin(int pin) {
	if (GetPinIterator(pin) == used_pins_.end()) {
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

bool Component::UsesPin(std::vector<int>::iterator pinIterator) {
	if (pinIterator == used_pins_.end()) {
		return false;
	}
	return true;
}

void Component::AddPin(int pin) {
	//add pin if it's not part of the vector already
	if (!UsesPin(pin)) used_pins_.push_back(pin);
}

void Component::AddPins(vector<int> pins) {
	for (auto pin : pins) {
		AddPin(pin);
	}
}

bool Component::RemoveAllPins() {
	if (used_pins_.empty()) return false;
	used_pins_.clear();
	return true;
}

bool Component::RemovePin(int pin) {
	auto it = GetPinIterator(pin);
	if (!UsesPin(it)) return false;
	used_pins_.erase(it);
	return true;
}

string Component::ToString() {
	return string(component_name_);
}