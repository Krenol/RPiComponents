#include "undirectionalmotor.hpp"

void rpicomponents::Undirectionalmotor::Initialize()
{
	//Turn motor off and by this check if valid input was given
	if (!l293d_->WriteToEnablePin(usedPins_.enablePin, false)) throw std::invalid_argument("Invalid enable pin given!");
	if (!l293d_->WriteToInPin(usedPins_.inPin, false)) throw std::invalid_argument("Invalid in pin given!");

	AddPins( l293d_->GetUsedPins() );
}

rpicomponents::Undirectionalmotor::Undirectionalmotor(const EnablePinStruct& enable_pins, const InPinStruct& in_pins, int enablePin, int inPin) :
	Motor(COMPONENT_UNDIRECTIONALMOTOR), l293d_{ std::unique_ptr<L293D>(new L293D(enable_pins , in_pins)) },
	usedPins_{ UndirectionalmotorData(enablePin, inPin) }
{
	Initialize();
}

rpicomponents::Undirectionalmotor::Undirectionalmotor(const EnablePinStruct& enable_pins, const InPinStruct& in_pins, const UndirectionalmotorData& usedL293DPins) :
	Motor(COMPONENT_UNDIRECTIONALMOTOR), l293d_{ std::unique_ptr<L293D>(new L293D(enable_pins , in_pins)) },
	usedPins_{ UndirectionalmotorData(usedL293DPins) }
{
	Initialize();
}

rpicomponents::Undirectionalmotor::Undirectionalmotor(const Undirectionalmotor& motor) : 
	Undirectionalmotor(motor.GetL293DEnablePins(), motor.GetL293DInPins(), motor.GetUsedL293DPins())
{
}

void rpicomponents::Undirectionalmotor::Rotate(int speed)
{
	l293d_->WriteToEnablePin(usedPins_.enablePin, speed);
	l293d_->WriteToInPin(usedPins_.inPin, true);
}

void rpicomponents::Undirectionalmotor::Stop() const
{
	l293d_->WriteToEnablePin(usedPins_.enablePin, false);
	l293d_->WriteToInPin(usedPins_.inPins, false);
}

const rpicomponents::EnablePinStruct& rpicomponents::Undirectionalmotor::GetL293DEnablePins() const
{
	return l293d_->GetEnablePins();
}

const rpicomponents::InPinStruct& rpicomponents::Undirectionalmotor::GetL293DInPins() const
{
	return l293d_->GetInPins();
}

const rpicomponents::UndirectionalmotorData& rpicomponents::Undirectionalmotor::GetUsedL293DPins() const
{
	return usedPins_;
}
