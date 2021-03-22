#include "bidirectionalmotor.hpp"

rpicomponents::Bidirectionalmotor::Bidirectionalmotor(std::shared_ptr<L293D> l293d,int enablePin, int inPinCW, int inPinCCW) :
    Motor(COMPONENT_BIDIRECTIONALMOTOR), l293d_{ l293d },
	usedPins_{ BidirectionalmotorData(enablePin, inPinCW , inPinCCW) }
{
	Initialize();
}

rpicomponents::Bidirectionalmotor::Bidirectionalmotor(std::shared_ptr<L293D> l293d, const BidirectionalmotorData& usedL293DPins) :
    Motor(COMPONENT_BIDIRECTIONALMOTOR), l293d_{ l293d }, usedPins_{ usedL293DPins }
{
	Initialize();
}

rpicomponents::Bidirectionalmotor::Bidirectionalmotor(const Bidirectionalmotor& motor) : 
    Bidirectionalmotor(motor.GetL293D(), motor.GetUsedL293DPins())
{

}

const std::shared_ptr<rpicomponents::L293D>& rpicomponents::Bidirectionalmotor::GetL293D() const {
    return l293d_;
}

void rpicomponents::Bidirectionalmotor::Initialize() {
    //check if valid input was given
    if (!l293d_->ValidEnablePin(usedPins_.enablePin)) throw std::invalid_argument("Invalid enable pin given!");
    if (!l293d_->ValidInPin(usedPins_.inCW)) throw std::invalid_argument("Invalid in pin for CW given!");
    if (!l293d_->ValidInPin(usedPins_.inCCW)) throw std::invalid_argument("Invalid in pin for CCW given!");
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

const rpicomponents::BidirectionalmotorData& rpicomponents::Bidirectionalmotor::GetUsedL293DPins() const {
	return usedPins_;
}

void rpicomponents::to_json(nlohmann::json& j, const rpicomponents::BidirectionalmotorData& d) {
    j = nlohmann::json{{"enablePin", d.enablePin}, {"inCW", d.inCW}, {"inCCW", d.inCCW}};
}

void rpicomponents::from_json(const nlohmann::json& j, rpicomponents::BidirectionalmotorData& d) {
	j.at("enablePin").get_to(d.enablePin);
	j.at("inCW").get_to(d.inCW);
	j.at("inCCW").get_to(d.inCCW);
}