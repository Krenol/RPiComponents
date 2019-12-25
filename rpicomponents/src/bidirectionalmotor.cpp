#include "bidirectionalmotor.hpp"

rpicomponents::Bidirectionalmotor::Bidirectionalmotor(const EnablePinStruct& enable_pins, const InPinStruct& in_pins, int enablePin, int inPinCW, int inPinCCW) :
	Motor(COMPONENT_BIDIRECTIONALMOTOR), l293d_{ std::unique_ptr<L293D>(new L293D(enable_pins , in_pins)) }, enablePin_{ enablePin }, inCW_{ inPinCW }, inCCW_{ inPinCCW }
{
	//Turn motor off and by this check if valid input was given
	if (!l293d_->WriteToEnablePin(enablePin_, false)) throw std::invalid_argument("Invalid enable pin given!");
	if (!l293d_->WriteToInPin(inCW_, false)) throw std::invalid_argument("Invalid in pin for CW given!");
	if (!l293d_->WriteToInPin(inCCW_, false)) throw std::invalid_argument("Invalid in pin for CCW given!");
}

void rpicomponents::Bidirectionalmotor::Rotate(int speed, bool cw = true) {
	l293d_->WriteToEnablePin(enablePin_, speed);
	l293d_->WriteToInPin(inCW_, cw);
	l293d_->WriteToInPin(inCCW_, !cw);
}

void rpicomponents::Bidirectionalmotor::Stop() const {
	l293d_->WriteToEnablePin(enablePin_, false);
	l293d_->WriteToInPin(inCW_, false);
	l293d_->WriteToInPin(inCCW_, false);
}