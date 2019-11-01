#include "l293d.hpp"

void rpicomponents::L293D::Initialize() const {
	//catch wrong inputs
	if (enable_pin1_->OutputMode() == pin::INPUT_MODE || enable_pin1_->OutputMode() == pin::IN_OUT_MODE) {
		throw std::invalid_argument("enable pin 1 cannot be an input or input/output pin!");
	}

	if (enable_pin2_->OutputMode() == pin::INPUT_MODE || enable_pin2_->OutputMode() == pin::IN_OUT_MODE) {
		throw std::invalid_argument("enable pin 2 cannot be an input or input/output pin!");
	}

	AddPins({ enable_pin1_->GetPin(), enable_pin2_->GetPin(), in_pin1_->GetPin(), 
		in_pin2_->GetPin(), in_pin3_->GetPin(), in_pin4_->GetPin() });
}

rpicomponents::L293D::L293D(const int& enable_pin1, const int& enable_pin2, const rpicomponents::pin::PIN_MODE& enable_pin1_mode,
	const rpicomponents::pin::PIN_MODE& enable_pin2_mode, const int& max_output_enable_pin1, const int& max_output_enable_pin2,
	const int& in_pin1, const int& in_pin2, const int& in_pin3, const int& in_pin4) : 
	Component(COMPONENT_L293D), enable_pin1_{pin::PinCreator::CreatePin(enable_pin1, enable_pin1_mode, max_output_enable_pin1)}, 
	enable_pin2_{ pin::PinCreator::CreatePin(enable_pin2, enable_pin2_mode, max_output_enable_pin2) },
	in_pin1_{ pin::PinCreator::CreatePin(in_pin1, pin::DIGITAL_MODE)}, in_pin2_{ pin::PinCreator::CreatePin(in_pin2, pin::DIGITAL_MODE) }, 
	in_pin3_{ pin::PinCreator::CreatePin(in_pin3, pin::DIGITAL_MODE) }, in_pin4_{ pin::PinCreator::CreatePin(in_pin4, pin::DIGITAL_MODE) }
{
	Initialize();
}

rpicomponents::L293D::L293D(int&& enable_pin1, int&& enable_pin2, rpicomponents::pin::PIN_MODE&& enable_pin1_mode,
	rpicomponents::pin::PIN_MODE&& enable_pin2_mode, int&& max_output_enable_pin1, int&& max_output_enable_pin2,
	int&& in_pin1, int&& in_pin2, int&& in_pin3, int&& in_pin4) :
	Component(COMPONENT_L293D), enable_pin1_{ pin::PinCreator::CreatePin(enable_pin1, enable_pin1_mode, max_output_enable_pin1) },
	enable_pin2_{ pin::PinCreator::CreatePin(enable_pin2, enable_pin2_mode, max_output_enable_pin2) },
	in_pin1_{ pin::PinCreator::CreatePin(in_pin1, pin::DIGITAL_MODE) }, in_pin2_{ pin::PinCreator::CreatePin(in_pin2, pin::DIGITAL_MODE) },
	in_pin3_{ pin::PinCreator::CreatePin(in_pin3, pin::DIGITAL_MODE) }, in_pin4_{ pin::PinCreator::CreatePin(in_pin4, pin::DIGITAL_MODE) }
{
	Initialize();
}

rpicomponents::L293D::L293D(const EnablePinStruct& enable_pins, const InPinStruct& in_pins) : 
	Component(COMPONENT_L293D), enable_pin1_{ pin::PinCreator::CreatePin(enable_pins.enable_pin1_, enable_pins.enable_pin1_mode_, enable_pins.max_output_enable_pin1_) },
	enable_pin2_{ pin::PinCreator::CreatePin(enable_pins.enable_pin2_, enable_pins.enable_pin2_mode_, enable_pins.max_output_enable_pin2_) },
	in_pin1_{ pin::PinCreator::CreatePin(in_pins.in_pin1_, pin::DIGITAL_MODE) }, in_pin2_{ pin::PinCreator::CreatePin(in_pins.in_pin2_, pin::DIGITAL_MODE) },
	in_pin3_{ pin::PinCreator::CreatePin(in_pins.in_pin3_, pin::DIGITAL_MODE) }, in_pin4_{ pin::PinCreator::CreatePin(in_pins.in_pin4_, pin::DIGITAL_MODE) }
{
	Initialize();
}

rpicomponents::L293D::L293D(const L293D& l293d) : L293D(l293d.GetEnablePins(), l293d.GetInPins()) {
	// Initialize method not called here as other constructor is called
}

rpicomponents::EnablePinStruct rpicomponents::L293D::GetEnablePins() const {
	EnablePinStruct enable_pins (enable_pin1_->GetPin(), enable_pin2_->GetPin(), enable_pin1_->OutputMode(), enable_pin2_->OutputMode(),
		enable_pin1_->GetMaxOutValue(), enable_pin2_->GetMaxOutValue());

	return enable_pins;
}

rpicomponents::InPinStruct rpicomponents::L293D::GetInPins() const {
	InPinStruct in_pins(in_pin1_->GetPin(), in_pin2_->GetPin(), in_pin3_->GetPin(), in_pin4_->GetPin());

	return in_pins;
}

void rpicomponents::L293D::TurnOnIn1() const {
	in_pin1_->OutputOn();
}

void rpicomponents::L293D::TurnOffIn1() const {
	in_pin1_->OutputOff();
}

void rpicomponents::L293D::TurnOnIn2() const {
	in_pin2_->OutputOn();
}

void rpicomponents::L293D::TurnOffIn2() const {
	in_pin2_->OutputOff();
}

void rpicomponents::L293D::TurnOnIn3() const {
	in_pin3_->OutputOn();
}

void rpicomponents::L293D::TurnOffIn3() const {
	in_pin3_->OutputOff();
}

void rpicomponents::L293D::TurnOnIn4() const {
	in_pin4_->OutputOn();
}

void rpicomponents::L293D::TurnOffIn4() const {
	in_pin4_->OutputOff();
}

void rpicomponents::L293D::TurnOnEnablePin1() const {
	enable_pin1_->OutputOn();
}

void rpicomponents::L293D::TurnOnEnablePin1(const int& value) const {
	enable_pin1_->Output(value);
}

void rpicomponents::L293D::TurnOffEnablePin1() const {
	enable_pin1_->OutputOff();
}

void rpicomponents::L293D::TurnOnEnablePin2() const {
	enable_pin2_->OutputOn();
}

void rpicomponents::L293D::TurnOnEnablePin2(const int& value) const {
	enable_pin2_->Output(value);
}

void rpicomponents::L293D::TurnOffEnablePin2() const {
	enable_pin2_->OutputOff();
}

int rpicomponents::L293D::EnablePin1OutputValue() const {
	int value = enable_pin1_->ReadPinValue();
	return value;
}

int rpicomponents::L293D::EnablePin2OutputValue() const {
	int value = enable_pin2_->ReadPinValue();
	return value;
}

bool rpicomponents::L293D::InPin1On() const {
	bool status = in_pin1_->IsOn();
	return status;
}

bool rpicomponents::L293D::InPin2On() const {
	bool status = in_pin2_->IsOn();
	return status;
}

bool rpicomponents::L293D::InPin3On() const {
	bool status = in_pin3_->IsOn();
	return status;
}

bool rpicomponents::L293D::InPin4On() const {
	bool status = in_pin4_->IsOn();
	return status;
}