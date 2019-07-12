#include "component.hpp"
#include <math.h>
//#include <iomanip>


using namespace rpicomponents::pin;
using namespace rpicomponents::pin::utils;

rpicomponents::Component::Component(std::string componentName) : component_name_{ componentName }
{
}

void rpicomponents::Component::CheckPinStatus(const Pin* pin, PIN_MODE mode) const
{
	CheckPinStatus(pin, std::vector<PIN_MODE>{ mode });
}

void rpicomponents::Component::CheckPinStatus(const pin::Pin* pin, std::vector<pin::utils::PIN_MODE> mode) const
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

rpicomponents::Component::~Component() {

}

std::vector<int8_t>::iterator rpicomponents::Component::GetPinIterator(int8_t pin) const {
	return find(used_pins_.begin(), used_pins_.end(), pin);
}

bool rpicomponents::Component::UsesPin(int8_t pin) const {
	std::lock_guard<std::mutex> lck{ mtx_ };
	auto check = GetPinIterator(pin);
	if (check == used_pins_.end()) {
		return false;
	}
	return true;
}

bool rpicomponents::Component::UsesPins(std::vector<int8_t> pins) const {
	bool uses = true;
	for (auto pin : pins) {
		uses = uses && UsesPin(pin);
		if (!uses) return false;
	}
	return uses;
}

void rpicomponents::Component::AddPin(int8_t pin) const {
	auto uses_pin = UsesPin(pin);
	if (!uses_pin) {
		std::lock_guard<std::mutex> lck{ mtx_ };
		used_pins_.push_back(pin);
	}
}

void rpicomponents::Component::AddPins(std::vector<int8_t> pins) const {
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

bool rpicomponents::Component::RemovePin(int8_t pin) const {
	std::lock_guard<std::mutex> lck{ mtx_ };
	auto it = GetPinIterator(pin);
	if (it == used_pins_.end()) return false;
	used_pins_.erase(it);
	return true;
}

std::string rpicomponents::Component::ToString() const {
	return std::string(component_name_);
}