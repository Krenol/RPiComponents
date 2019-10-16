#include "component.hpp"
#include <math.h>
//#include <iomanip>





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

std::vector<int>::iterator rpicomponents::Component::GetPinIterator(const int& pin) const {
	return find(used_pins_.begin(), used_pins_.end(), pin);
}

bool rpicomponents::Component::UsesPin(const int& pin) const {
	std::lock_guard<std::mutex> lck{ mtx_ };
	auto check = GetPinIterator(pin);
	if (check == used_pins_.end()) {
		return false;
	}
	return true;
}

bool rpicomponents::Component::UsesPins(std::vector<int>& pins) const {
	bool uses = true;
	for (auto pin : pins) {
		uses = uses && UsesPin(pin);
		if (!uses) return false;
	}
	return uses;
}

void rpicomponents::Component::AddPin(const int& pin) const {
	auto uses_pin = UsesPin(pin);
	if (!uses_pin) {
		std::lock_guard<std::mutex> lck{ mtx_ };
		used_pins_.push_back(pin);
	}
}

void rpicomponents::Component::AddPins(const std::vector<int>& pins) const {
	for (auto pin : pins) {
		AddPin(pin);
	}
}

bool rpicomponents::Component::RemoveAllPins() const {
	std::lock_guard<std::mutex> lck{ mtx_ };
	if (used_pins_.empty()) return false;
	used_pins_.clear();
	return true;
}

bool rpicomponents::Component::RemovePin(const int& pin) const {
	std::lock_guard<std::mutex> lck{ mtx_ };
	auto it = GetPinIterator(pin);
	if (it == used_pins_.end()) return false;
	used_pins_.erase(it);
	return true;
}

const std::string& rpicomponents::Component::ToString() const {
	return component_name_;
}