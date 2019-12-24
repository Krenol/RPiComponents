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

    for (int i = 0; i < max_q_pin_no_; i++) {
		q_pin_map_.insert(std::make_pair(i, false));
	}
	AddPins({ shcp_->GetPin(),  ds_->GetPin(), stcp_->GetPin() });
}


bool rpicomponents::Q74HC595::ValidQPin(int pin_no) const
{
	if (pin_no < 0 || pin_no >= max_q_pin_no_) {
		return false;
	}
	return true;
}


void rpicomponents::Q74HC595::WriteToQPins()
{
	ds_->OutputOff();
	shcp_->OutputOff();
	stcp_->OutputOff();
    for (int i = max_q_pin_no_ - 1; i >= 0; i--) {
		ds_->Output(q_pin_map_[i]);
		shcp_->OutputOn();
		utils::Waiter::SleepMillis(1); //sleep to make sure data is pushed correctly
		shcp_->OutputOff();
	}
	stcp_->OutputOn();
	utils::Waiter::SleepMillis(1); //sleep to make sure data is pushed correctly
	stcp_->OutputOff();
}

rpicomponents::Q74HC595::Q74HC595(int ds_pin, int stcp_pin, int shcp_pin) : Component(COMPONENT_Q74HC595), 
ds_{pin::PinCreator::CreatePin(ds_pin, pin::DIGITAL_MODE)}, shcp_{ pin::PinCreator::CreatePin(shcp_pin, pin::DIGITAL_MODE) },
stcp_{ pin::PinCreator::CreatePin(stcp_pin, pin::DIGITAL_MODE) }
{
	Initialize();
}

//rpicomponents::Q74HC595::Q74HC595(int&& ds_pin, int&& stcp_pin, int&& shcp_pin) : Component(COMPONENT_Q74HC595),
//ds_{ pin::PinCreator::CreatePin(ds_pin, pin::DIGITAL_MODE) }, shcp_{ pin::PinCreator::CreatePin(shcp_pin, pin::DIGITAL_MODE) },
//stcp_{ pin::PinCreator::CreatePin(stcp_pin, pin::DIGITAL_MODE) }
//{
//	Initialize();
//}

rpicomponents::Q74HC595::Q74HC595(const Q74HC595& q74hc595) : Component(COMPONENT_Q74HC595),
ds_{ pin::PinCreator::CreatePin(q74hc595.GetDsPin(), pin::DIGITAL_MODE) }, shcp_{ pin::PinCreator::CreatePin(q74hc595.GetShcpPin(), pin::DIGITAL_MODE) },
stcp_{ pin::PinCreator::CreatePin(q74hc595.GetStcpPin(), pin::DIGITAL_MODE) }
{
	Initialize();
}

void rpicomponents::Q74HC595::SetQPinOutput(int pin, bool turn_on)
{
	if (!ValidQPin(pin)) {
		throw new std::invalid_argument("pin_no must be in the range 0 <= pin_no < max_q_pin_no_");
	}
	q_pin_map_[pin] = turn_on;
	WriteToQPins();
}

void rpicomponents::Q74HC595::SetQPinOutput(const std::map<int, bool>& pins)
{
	for (auto const& it : pins) {
		if(ValidQPin(it.first)) q_pin_map_[it.first] = it.second;
	}
	WriteToQPins();
}

bool rpicomponents::Q74HC595::GetQPinOutput(int pin)
{
	if (!ValidQPin(pin)) {
		throw new std::invalid_argument("pin_no must be in the range 0 <= pin_no < max_q_pin_no_");
	}
	auto val = q_pin_map_[pin];
	return val;
}

void rpicomponents::Q74HC595::TurnOn()
{
	for (int i = 0; i < max_q_pin_no_; i++) {
		q_pin_map_[i] = true;
	}
	WriteToQPins();
}

void rpicomponents::Q74HC595::TurnOff()
{
	for (int i = 0; i < max_q_pin_no_; i++) {
		q_pin_map_[i] = false;
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

int rpicomponents::Q74HC595::GetMaxQPinCount() const
{
    return max_q_pin_no_;
}
