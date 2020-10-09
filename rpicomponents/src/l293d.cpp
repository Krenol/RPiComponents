#include "l293d.hpp"

void rpicomponents::L293D::Initialize()
{
	//catch wrong inputs
	if (enable1_->OutputMode() == pin::INPUT_MODE || enable1_->OutputMode() == pin::IN_OUT_MODE)
	{
		throw std::invalid_argument("enable pin 1 cannot be an input or input/output pin!");
	}

	if (enable2_->OutputMode() == pin::INPUT_MODE || enable2_->OutputMode() == pin::IN_OUT_MODE)
	{
		throw std::invalid_argument("enable pin 2 cannot be an input or input/output pin!");
	}

	//add pins to vector
	AddPins({enable1_->GetPin(), enable2_->GetPin(), in1_->GetPin(),
			 in2_->GetPin(), in3_->GetPin(), in4_->GetPin()});
}

rpicomponents::L293D::L293D(int enable_pin1, pin::PIN_MODE enable_pin1_mode, int enable_pin1_max, int enable_pin2, pin::PIN_MODE enable_pin2_mode, int enable_pin2_max, int in_pin1,
							int in_pin2, int in_pin3, int in_pin4) : Component(COMPONENT_L293D)
{
	enable1_ = pin::PinCreator::CreatePin(enable_pin1, enable_pin1_mode, enable_pin1_max);
	enable2_ = pin::PinCreator::CreatePin(enable_pin2, enable_pin2_mode, enable_pin2_max);
	enablePins_ = {{1, enable1_}, {2, enable2_}};
	in1_ = pin::PinCreator::CreateInputPin(in_pin1, pin::DIGITAL_MODE_MAX_VAL);
	in2_ = pin::PinCreator::CreateInputPin(in_pin2, pin::DIGITAL_MODE_MAX_VAL);
	in3_ = pin::PinCreator::CreateInputPin(in_pin3, pin::DIGITAL_MODE_MAX_VAL);
	in4_ = pin::PinCreator::CreateInputPin(in_pin4, pin::DIGITAL_MODE_MAX_VAL);
	inPins_ = {{1, in1_}, {2, in2_}, {3, in3_}, {4, in4_}};
	Initialize();
}

rpicomponents::L293D::L293D(const pin::pin_data& enable_pin1, const pin::pin_data& enable_pin2, int in_pin1, 
			int in_pin2, int in_pin3, int in_pin4) : Component(COMPONENT_L293D)
{
	enable1_ = pin::PinCreator::CreatePin(enable_pin1);
	enable2_ = pin::PinCreator::CreatePin(enable_pin2);
	enablePins_ = {{1, enable1_}, {2, enable2_}};
	in1_ = pin::PinCreator::CreateInputPin(in_pin1, pin::DIGITAL_MODE_MAX_VAL);
	in2_ = pin::PinCreator::CreateInputPin(in_pin2, pin::DIGITAL_MODE_MAX_VAL);
	in3_ = pin::PinCreator::CreateInputPin(in_pin3, pin::DIGITAL_MODE_MAX_VAL);
	in4_ = pin::PinCreator::CreateInputPin(in_pin4, pin::DIGITAL_MODE_MAX_VAL);
	inPins_ = {{1, in1_}, {2, in2_}, {3, in3_}, {4, in4_}};
	Initialize();
}

rpicomponents::L293D::L293D(const L293D& l293d) : Component(COMPONENT_L293D)
{
	auto enable = l293d.GetEnablePins();
	auto in = l293d.GetInPins();
	enable1_ = pin::PinCreator::CreatePin(enable.at(1));
	enable2_ = pin::PinCreator::CreatePin(enable.at(2));
	enablePins_ = {{1, enable1_}, {2, enable2_}};
	in1_ = pin::PinCreator::CreatePin(in.at(1));
	in2_ = pin::PinCreator::CreatePin(in.at(2));
	in3_ = pin::PinCreator::CreatePin(in.at(3));
	in4_ = pin::PinCreator::CreatePin(in.at(4));
	inPins_ = {{1, in1_}, {2, in2_}, {3, in3_}, {4, in4_}};
	Initialize();
}

std::map<int, pin::pin_data> rpicomponents::L293D::GetEnablePins() const {
	std::map<int, pin::pin_data> data;
	auto it = enablePins_.begin();
	while (it != enablePins_.end())
    {
		data.insert({it->first, it->second->GetPinData()});
        it++;
    }
	return data;
}


std::map<int, pin::pin_data> rpicomponents::L293D::GetInPins() const {
	std::map<int, pin::pin_data> data;
	auto it = inPins_.begin();
	while (it != inPins_.end())
    {
		data.insert({it->first, it->second->GetPinData()});
        it++;
    }
	return data;
}

void rpicomponents::L293D::TurnOnIn1() const
{
	WriteToInPin(1, true);
}

void rpicomponents::L293D::TurnOffIn1() const
{
	WriteToInPin(1, false);
}

void rpicomponents::L293D::TurnOnIn2() const
{
	WriteToInPin(2, true);
}

void rpicomponents::L293D::TurnOffIn2() const
{
	WriteToInPin(2, false);
}

void rpicomponents::L293D::TurnOnIn3() const
{
	WriteToInPin(3, true);
}

void rpicomponents::L293D::TurnOffIn3() const
{
	WriteToInPin(3, false);
}

void rpicomponents::L293D::TurnOnIn4() const
{
	WriteToInPin(4, true);
}

void rpicomponents::L293D::TurnOffIn4() const
{
	WriteToInPin(4, false);
}

void rpicomponents::L293D::TurnOnEnablePin1() const
{
	WriteToEnablePin(1, true);
}

void rpicomponents::L293D::TurnOnEnablePin1(int value) const
{
	WriteToEnablePin(1, value);
}

void rpicomponents::L293D::TurnOffEnablePin1() const
{
	WriteToEnablePin(1, false);
}

void rpicomponents::L293D::TurnOnEnablePin2() const
{
	WriteToEnablePin(2, true);
}

void rpicomponents::L293D::TurnOnEnablePin2(int value) const
{
	WriteToEnablePin(2, value);
}

void rpicomponents::L293D::TurnOffEnablePin2() const
{
	WriteToEnablePin(2, false);
}

int rpicomponents::L293D::EnablePin1OutputValue() const
{
	int value = EnablePinOutputValue(1);
	return value;
}

int rpicomponents::L293D::EnablePin2OutputValue() const
{
	int value = EnablePinOutputValue(2);
	return value;
}

bool rpicomponents::L293D::InPin1On() const
{
	bool status = InPinIsOn(1);
	return status;
}

bool rpicomponents::L293D::InPin2On() const
{
	bool status = InPinIsOn(2);
	return status;
}

bool rpicomponents::L293D::InPin3On() const
{
	bool status = InPinIsOn(3);
	return status;
}

bool rpicomponents::L293D::InPin4On() const
{
	bool status = InPinIsOn(4);
	return status;
}

void rpicomponents::L293D::WriteToInPin(int pinNo, bool turnOn) const
{
	auto p = inPins_.find(pinNo);
	if (p == inPins_.end())
	{
		throw std::invalid_argument("invalid pin number given!");
	}
	p->second->Output(turnOn);
}

void rpicomponents::L293D::WriteToEnablePin(int pinNo, bool turnOn) const
{
	auto p = enablePins_.find(pinNo);
	if (p == enablePins_.end())
	{
		throw std::invalid_argument("invalid pin number given!");
	}
	p->second->Output(turnOn ? p->second->GetMaxOutValue() : 0);
}

void rpicomponents::L293D::WriteToEnablePin(int pinNo, int value) const
{
	auto p = enablePins_.find(pinNo);
	if (p == enablePins_.end())
	{
		throw std::invalid_argument("invalid pin number given!");
	}
	p->second->Output(value);
}

bool rpicomponents::L293D::InPinIsOn(int pinNo) const
{
	auto p = inPins_.find(pinNo);
	if (p == inPins_.end())
	{
		throw std::invalid_argument("invalid pin number given!");
	}
	auto val = p->second->IsOn();
	return val;
}

int rpicomponents::L293D::EnablePinOutputValue(int pinNo) const
{
	auto p = enablePins_.find(pinNo);
	if (p == enablePins_.end())
	{
		throw std::invalid_argument("invalid pin number given!");
	}
	auto val = p->second->ReadPinValue();
	return val;
}

bool rpicomponents::L293D::ValidEnablePin(int pinNo) const
{
	auto p = enablePins_.find(pinNo);
	return p != enablePins_.end();
}

bool rpicomponents::L293D::ValidInPin(int pinNo) const
{
	auto p = inPins_.find(pinNo);
	return p != enablePins_.end();
}
