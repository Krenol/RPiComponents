#include "q74hc595.hpp"
#include "utils/utils.hpp"


bool rpicomponents::Q74HC595::ValidQPin(int pin_no) const
{
	if (pin_no < 0 || pin_no >= COMPONENT_Q74HC595_MAX_Q_PINS) {
		return false;
	}
	return true;
}


void rpicomponents::Q74HC595::WriteToQPins()
{
	ds_->OutputOff();
	shcp_->OutputOff();
	stcp_->OutputOff();
    for (int i = COMPONENT_Q74HC595_MAX_Q_PINS - 1; i >= 0; i--) {
		ds_->Output(q_pin_map_.at(i));
		shcp_->OutputOn();
		utils::Waiter::SleepMillis(out_sleep_); //sleep to make sure data is pushed correctly
		shcp_->OutputOff();
	}
	stcp_->OutputOn();
	utils::Waiter::SleepMillis(out_sleep_); //sleep to make sure data is pushed correctly
	stcp_->OutputOff();
}

rpicomponents::Q74HC595::Q74HC595(int ds_pin, int stcp_pin, int shcp_pin) : 
	Component(COMPONENT_Q74HC595)
{
	if (ds_pin == shcp_pin) {
		throw new std::invalid_argument("shcp pin cannot be the same as the ds pin!");
	}
	if (shcp_pin == stcp_pin) {
		throw new std::invalid_argument("stcp pin cannot be the same as the shcp pin!");
	}
	if (ds_pin == stcp_pin) {
		throw new std::invalid_argument("stcp pin cannot be the same as the ds pin!");
	}
	ds_ = pin::PinCreator::CreateDigitalPin(ds_pin, pin::DIGITAL_MODE_MAX_VAL);
	stcp_ = pin::PinCreator::CreateDigitalPin(ds_pin, pin::DIGITAL_MODE_MAX_VAL);
	shcp_ = pin::PinCreator::CreateDigitalPin(ds_pin, pin::DIGITAL_MODE_MAX_VAL);
	for (int i = 0; i < COMPONENT_Q74HC595_MAX_Q_PINS; i++) {
		q_pin_map_.insert(std::make_pair(i, false));
	}
	AddPins({ ds_pin, shcp_pin, stcp_pin });
}

rpicomponents::Q74HC595::Q74HC595(const Q74HC595& q74hc595) : Q74HC595(q74hc595.GetDsPin(), q74hc595.GetStcpPin(), q74hc595.GetShcpPin())
{

}

void rpicomponents::Q74HC595::SetQPinOutput(int pin, bool turn_on)
{
	if (!ValidQPin(pin)) {
		throw new std::invalid_argument("pin_no must be in the range 0 <= pin_no < max_q_pin_no_");
	}
	q_pin_map_[pin] = turn_on;
	WriteToQPins();
}

void rpicomponents::Q74HC595::SetQPinOutput(const QPinMap& pins)
{
	std::map<int, bool>::iterator mapIt;

	for (auto const& it : pins) {
		mapIt = q_pin_map_.find(it.first);
		if (mapIt != q_pin_map_.end()) {
			mapIt->second = it.second;
		}
	}
	WriteToQPins();
}

bool rpicomponents::Q74HC595::GetQPinOutput(int pin)
{
	auto p = q_pin_map_.find(pin);
	if (p == q_pin_map_.end()) {
		throw new std::invalid_argument("invalid pin number!");
	}
	auto val = p->second;
	return val;
}

void rpicomponents::Q74HC595::TurnOn()
{
	for (int i = 0; i < COMPONENT_Q74HC595_MAX_Q_PINS; i++) {
		q_pin_map_.at(i) = true;
	}
	WriteToQPins();
}

void rpicomponents::Q74HC595::TurnOff()
{
	for (int i = 0; i < COMPONENT_Q74HC595_MAX_Q_PINS; i++) {
		q_pin_map_.at(i) = false;
	}
	WriteToQPins();
}

int rpicomponents::Q74HC595::GetDsPin() const
{
	return ds_->GetPin();
}

int rpicomponents::Q74HC595::GetStcpPin() const
{
	return stcp_->GetPin();
}

int rpicomponents::Q74HC595::GetShcpPin() const
{
	return shcp_->GetPin();
}

