#include "component.hpp"


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
	std::lock_guard<std::mutex> grd(mtx_);
	if (pin == nullptr) throw new std::invalid_argument("pin of component is null");
	bool valid = false;
	std::string modes = "";
	for (int i = 0; i < mode.size(); i++) {
		valid = PinFactory::CheckPinMode(pin, mode[i]);
		if (valid) return;
		modes += (i == 0 ? "" : ", ") + mode[i];
	}
	throw new std::invalid_argument("pin is not of PIN_MODES " + modes);
}

Component::~Component() {

}

std::vector<int8_t>::iterator Component::GetPinIterator(int8_t pin) const {
	return find(used_pins_.begin(), used_pins_.end(), pin);
}

bool Component::UsesPin(int8_t pin) const {
	std::lock_guard<std::mutex> lck{ mtx_ };
	auto check = GetPinIterator(pin);
	if (check == used_pins_.end()) {
		return false;
	}
	return true;
}

bool Component::UsesPins(std::vector<int8_t> pins) const {
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
		std::lock_guard<std::mutex> lck{ mtx_ };
		used_pins_.push_back(pin);
	}
}

void Component::AddPins(std::vector<int8_t> pins) const {
	for (auto pin : pins) {
		AddPin(pin);
	}
}

bool Component::RemoveAllPins() const {
	std::lock_guard<std::mutex> lck{ mtx_ };
	if (used_pins_.empty()) return false;
	used_pins_.clear();
	return true;
}

bool Component::RemovePin(int8_t pin) const {
	std::lock_guard<std::mutex> lck{ mtx_ };
	auto it = GetPinIterator(pin);
	if (it == used_pins_.end()) return false;
	used_pins_.erase(it);
	return true;
}

std::string Component::ToString() const {
	return std::string(component_name_);
}