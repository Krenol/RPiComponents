#include "undirectionalmotor.hpp"

void rpicomponents::Undirectionalmotor::Initialize()
{
	//check if valid input was given
	if (!l293d_->ValidEnablePin(usedPins_.enablePin)) throw std::invalid_argument("Invalid enable pin given!");
	if (!l293d_->ValidInPin(usedPins_.inPin)) throw std::invalid_argument("Invalid in pin given!");

	AddPins( l293d_->GetUsedPins() );
}

rpicomponents::Undirectionalmotor::Undirectionalmotor(std::shared_ptr<rpicomponents::L293D> l293d, int enablePin, int inPin) :
	Motor(COMPONENT_UNDIRECTIONALMOTOR), l293d_{l293d}, usedPins_{ UndirectionalmotorData(enablePin, inPin) }
{
	Initialize();
}

rpicomponents::Undirectionalmotor::Undirectionalmotor(std::shared_ptr<rpicomponents::L293D> l293d, const UndirectionalmotorData& usedL293DPins) :
	Motor(COMPONENT_UNDIRECTIONALMOTOR), l293d_{ l293d }, usedPins_{ UndirectionalmotorData(usedL293DPins) }
{
	Initialize();
}

rpicomponents::Undirectionalmotor::Undirectionalmotor(const Undirectionalmotor& motor) : 
	Undirectionalmotor(motor.GetUsedL293D(), motor.GetUsedL293DPins())
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
    l293d_->WriteToInPin(usedPins_.inPin, false);
}

const rpicomponents::UndirectionalmotorData& rpicomponents::Undirectionalmotor::GetUsedL293DPins() const
{
	return usedPins_;
}

const std::shared_ptr<rpicomponents::L293D>& rpicomponents::Undirectionalmotor::GetUsedL293D() const {
	return l293d_;
}
