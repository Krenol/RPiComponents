#include "q74hc595.hpp"

void rpicomponents::Q74HC595::Initialize()
{
	if (ds_->GetPin() == shcp_->GetPin()) {
		throw new std::invalid_argument("shcp pin cannot be the same as the ds pin!");
	}
	if (shcp_->GetPin() == stcp_->GetPin()) {
		throw new std::invalid_argument("stcp pin cannot be the same as the shcp pin!");
	}
	if (ds_->GetPin() == stcp_->GetPin()) {
		throw new std::invalid_argument("stcp pin cannot be the same as the ds pin!");
	}

	if (ds_->OutputMode() != pin::DIGITAL_MODE) {
		throw new std::invalid_argument("ds pin must be on DIGITAL_MODE!");
	}
	if (shcp_->OutputMode() != pin::DIGITAL_MODE) {
		throw new std::invalid_argument("shcp pin must be on DIGITAL_MODE!");
	}
	if (stcp_->OutputMode() != pin::DIGITAL_MODE) {
		throw new std::invalid_argument("stcp pin must be on DIGITAL_MODE!");
	}

    for (int i = 0; i < COMPONENT_Q74HC595_MAX_Q_PINS; i++) {
		q_pin_map_.insert(std::make_pair(i, false));
	}
	AddPins({ shcp_->GetPin(),  ds_->GetPin(), stcp_->GetPin() });
}


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

rpicomponents::Q74HC595::Q74HC595(std::shared_ptr<pin::Pin> ds_pin, std::shared_ptr<pin::Pin> stcp_pin, std::shared_ptr<pin::Pin> shcp_pin) : 
	Component(COMPONENT_Q74HC595), ds_{ ds_pin }, shcp_{ stcp_pin }, stcp_{ shcp_pin }
{
	Initialize();
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

const std::shared_ptr<rpicomponents::pin::Pin>& rpicomponents::Q74HC595::GetDsPin() const
{
	return ds_;
}

const std::shared_ptr<rpicomponents::pin::Pin>& rpicomponents::Q74HC595::GetStcpPin() const
{
	return stcp_;
}

const std::shared_ptr<rpicomponents::pin::Pin>& rpicomponents::Q74HC595::GetShcpPin() const
{
	return shcp_;
}

