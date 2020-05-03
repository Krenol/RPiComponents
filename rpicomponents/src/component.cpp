#include "component.hpp"
#include <math.h>



rpicomponents::Component::Component(const std::string &componentName) : component_name_{ componentName }
{
}

rpicomponents::Component::Component(std::string&& componentName) : component_name_{ componentName }
{
}

rpicomponents::Component::Component(const Component& component) : component_name_{component.ToString()}
{
}

rpicomponents::Component::~Component() {

}

std::vector<int>::iterator rpicomponents::Component::GetPinIterator(int pin) {
	return find(used_pins_.begin(), used_pins_.end(), pin);
}

bool rpicomponents::Component::UsesPin(int pin) {
	auto check = GetPinIterator(pin);
	if (check == used_pins_.end()) {
		return false;
	}
	return true;
}

bool rpicomponents::Component::UsesPins(std::vector<int>& pins) {
	bool uses = true;
	for (auto pin : pins) {
		uses = uses && UsesPin(pin);
		if (!uses) return false;
	}
	return uses;
}

const std::vector<int>& rpicomponents::Component::GetUsedPins()
{
	return used_pins_;
}

void rpicomponents::Component::AddPin(int pin) {
	auto uses_pin = UsesPin(pin);
	if (!uses_pin) {
		used_pins_.push_back(pin);
	}
}

void rpicomponents::Component::AddPins(const std::vector<int>& pins) {
	for (auto pin : pins) {
		AddPin(pin);
	}
}

bool rpicomponents::Component::RemoveAllPins() {
	if (used_pins_.empty()) return false;
	used_pins_.clear();
	return true;
}

bool rpicomponents::Component::RemovePin(int pin) {
	auto it = GetPinIterator(pin);
	if (it == used_pins_.end()) return false;
	used_pins_.erase(it);
	return true;
}

const std::string& rpicomponents::Component::ToString() const {
	return component_name_;
}
