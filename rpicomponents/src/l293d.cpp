#include "l293d.hpp"

void rpicomponents::L293D::Initialize()
{
	//check both maps
	if (enablePins_.find(1) == enablePins_.end())
	{
		throw std::invalid_argument("enable pin 1 is not part of the EnablePinMap!");
	}
	if (enablePins_.find(2) == enablePins_.end())
	{
		throw std::invalid_argument("enable pin 2 is not part of the EnablePinMap!");
	}
	if (inPins_.find(1) == inPins_.end())
	{
		throw std::invalid_argument("in pin 1 is not part of the InPinMap!");
	}
	if (inPins_.find(2) == inPins_.end())
	{
		throw std::invalid_argument("in pin 2 is not part of the InPinMap!");
	}
	if (inPins_.find(3) == inPins_.end())
	{
		throw std::invalid_argument("in pin 3 is not part of the InPinMap!");
	}
	if (inPins_.find(4) == inPins_.end())
	{
		throw std::invalid_argument("in pin 4 is not part of the InPinMap!");
	}

	//catch wrong inputs
	if (enablePins_.at(1)->OutputMode() == pin::INPUT_MODE || enablePins_.at(1)->OutputMode() == pin::IN_OUT_MODE)
	{
		throw std::invalid_argument("enable pin 1 cannot be an input or input/output pin!");
	}

	if (enablePins_.at(2)->OutputMode() == pin::INPUT_MODE || enablePins_.at(2)->OutputMode() == pin::IN_OUT_MODE)
	{
		throw std::invalid_argument("enable pin 2 cannot be an input or input/output pin!");
	}

	//add pins to vector
	AddPins({enablePins_.at(1)->GetPin(), enablePins_.at(2)->GetPin(), inPins_.at(1)->GetPin(),
			 inPins_.at(2)->GetPin(), inPins_.at(3)->GetPin(), inPins_.at(4)->GetPin()});
}

rpicomponents::L293D::L293D(int enable_pin1, int enable_pin1_mode, int enable_pin1_max, int enable_pin2, int enable_pin2_mode, int enable_pin2_max, int in_pin1,
							int in_pin2, int in_pin3, int in_pin4) : Component(COMPONENT_L293D)
{
	enablePins_ = {{1, pin::PinCreator::CreatePin(enable_pin1, enable_pin1_mode, enable_pin1_max)}, {2, pin::PinCreator::CreatePin(enable_pin2, enable_pin2_mode, enable_pin2_max)}};
	inPins_ = {{1, pin::PinCreator::CreateInputPin(in_pin1, pin::DIGITAL_MODE_MAX_VAL)}}, {2, pin::PinCreator::CreateInputPin(in_pin2, pin::DIGITAL_MODE_MAX_VAL)},
	{3, pin::PinCreator::CreateInputPin(in_pin3, pin::DIGITAL_MODE_MAX_VAL)}, { 4, pin::PinCreator::CreateInputPin(in_pin4, pin::DIGITAL_MODE_MAX_VAL) }
};
Initialize();
}

rpicomponents::L293D::L293D(const EnablePinMap &enablePins, const InPinMap &inPins) : Component(COMPONENT_L293D)																					  
{
	enablePins_ = std::move(enablePins);
	inPins_ = std::move(inPins);
	Initialize();
}

rpicomponents::L293D::L293D(const L293D &l293d) : L293D(l293d.GetEnablePins(), l293d.GetInPins())
{
	// Initialize method not called here as other constructor is called
}

const rpicomponents::EnablePinMap &rpicomponents::L293D::GetEnablePins() const
{
	return enablePins_;
}

const rpicomponents::InPinMap &rpicomponents::L293D::GetInPins() const
{
	return inPins_;
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
