#include "bidirectionalmotor.hpp"

rpicomponents::Bidirectionalmotor::Bidirectionalmotor(const std::shared_ptr<L293D> l293d,int enablePin, int inPinCW, int inPinCCW) :
    Motor(COMPONENT_BIDIRECTIONALMOTOR), l293d_{ l293d },
	usedPins_{ BidirectionalmotorData(enablePin, inPinCW , inPinCCW) }
{
	Initialize();
}

rpicomponents::Bidirectionalmotor::Bidirectionalmotor(const std::shared_ptr<L293D> l293d, const BidirectionalmotorData& usedL293DPins) :
    Motor(COMPONENT_BIDIRECTIONALMOTOR), l293d_{ l293d }, usedPins_{ usedL293DPins }
{
	Initialize();
}

rpicomponents::Bidirectionalmotor::Bidirectionalmotor(const Bidirectionalmotor& motor) : 
    Bidirectionalmotor(motor.GetL293D(), motor.GetL293DInPins(), motor.GetUsedL293DPins())
{

}

const std::shared_ptr<rpicomponents::Bidirectionalmotor::L293D>& rpicomponents::Bidirectionalmotor::GetL293D() const {
    return l293d_;
}

void rpicomponents::Bidirectionalmotor::Initialize() {
	//Turn motor off and by this check if valid input was given
	if (!l293d_->WriteToEnablePin(usedPins_.enablePin, false)) throw std::invalid_argument("Invalid enable pin given!");
	if (!l293d_->WriteToInPin(usedPins_.inCW, false)) throw std::invalid_argument("Invalid in pin for CW given!");
	if (!l293d_->WriteToInPin(usedPins_.inCCW, false)) throw std::invalid_argument("Invalid in pin for CCW given!");
    AddPins(l293d_->GetUsedPins());
}

void rpicomponents::Bidirectionalmotor::Rotate(int speed, bool cw) {
	l293d_->WriteToEnablePin(usedPins_.enablePin, speed);
	l293d_->WriteToInPin(usedPins_.inCW, cw);
	l293d_->WriteToInPin(usedPins_.inCCW, !cw);
}

void rpicomponents::Bidirectionalmotor::Stop() {
	l293d_->WriteToEnablePin(usedPins_.enablePin, false);
	l293d_->WriteToInPin(usedPins_.inCW, false);
	l293d_->WriteToInPin(usedPins_.inCCW, false);
}

const rpicomponents::EnablePinStruct& rpicomponents::Bidirectionalmotor::GetL293DEnablePins() const {
	return l293d_->GetEnablePins();
}


const rpicomponents::InPinStruct& rpicomponents::Bidirectionalmotor::GetL293DInPins() const {
	return l293d_->GetInPins();
}


const rpicomponents::BidirectionalmotorData& rpicomponents::Bidirectionalmotor::GetUsedL293DPins() const {
	return usedPins_;
}
