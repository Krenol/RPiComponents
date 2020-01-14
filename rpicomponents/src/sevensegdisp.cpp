#include "sevensegdisp.hpp"


rpicomponents::SevenSegmentDisplay::SevenSegmentDisplay(std::shared_ptr<Q74HC595> q74hc595, const DisplaySegments& dispSegments) :
	Component(COMPONENT_SEVENSEGMENTDISPLAY), q74_{ q74hc595 }, segments_{ dispSegments }
{
}

rpicomponents::SevenSegmentDisplay::SevenSegmentDisplay(std::shared_ptr<Q74HC595> q74hc595, int a, int b, int c,
	int d, int e, int f, int g, int dp) : 
	Component(COMPONENT_SEVENSEGMENTDISPLAY), q74_{ q74hc595 }, segments_{ DisplaySegments(a, b, c, d, e, f, g, dp) }
{
}

rpicomponents::SevenSegmentDisplay::SevenSegmentDisplay(const SevenSegmentDisplay& sevenSegDisp) :
	SevenSegmentDisplay(sevenSegDisp.GetQ74HC595(), sevenSegDisp.GetDisplaySegments())
{
}

const std::shared_ptr<rpicomponents::Q74HC595>& rpicomponents::SevenSegmentDisplay::GetQ74HC595() const
{
	return q74_;
}

const DisplaySegments& rpicomponents::SevenSegmentDisplay::GetDisplaySegments() const
{
	return segments_;
}

void rpicomponents::SevenSegmentDisplay::TurnOffAll() const
{
	q74_->TurnOn();
}

void rpicomponents::SevenSegmentDisplay::TurnOnAll() const
{
	q74_->TurnOff();
}

void rpicomponents::SevenSegmentDisplay::Write0(bool showPoint) const
{
	QPinMap pins = {
		{segments_.segA, SEG_ON},
		{segments_.segB, SEG_ON},
		{segments_.segC, SEG_ON},
		{segments_.segD, SEG_ON},
		{segments_.segE, SEG_ON},
		{segments_.segF, SEG_ON},
		{segments_.segG, SEG_OFF},
		{segments_.segDP, showPoint ? SEG_ON: SEG_OFF}
	};
	q74_->SetQPinOutput(pins)
}

void rpicomponents::SevenSegmentDisplay::Write1(bool showPoint) const
{
	QPinMap pins = {
		{segments_.segA, SEG_OFF},
		{segments_.segB, SEG_ON},
		{segments_.segC, SEG_ON},
		{segments_.segD, SEG_OFF},
		{segments_.segE, SEG_OFF},
		{segments_.segF, SEG_OFF},
		{segments_.segG, SEG_OFF},
		{segments_.segDP, showPoint ? SEG_ON : SEG_OFF}
	};
	q74_->SetQPinOutput(pins)
}

void rpicomponents::SevenSegmentDisplay::Write2(bool showPoint) const
{
	QPinMap pins = {
		{segments_.segA, SEG_ON},
		{segments_.segB, SEG_ON},
		{segments_.segC, SEG_OFF},
		{segments_.segD, SEG_ON},
		{segments_.segE, SEG_ON},
		{segments_.segF, SEG_OFF},
		{segments_.segG, SEG_ON},
		{segments_.segDP, showPoint ? SEG_ON : SEG_OFF}
	};
	q74_->SetQPinOutput(pins)
}


void rpicomponents::SevenSegmentDisplay::Write3(bool showPoint) const
{
	QPinMap pins = {
		{segments_.segA, SEG_OFF},
		{segments_.segB, SEG_OFF},
		{segments_.segC, SEG_OFF},
		{segments_.segD, SEG_OFF},
		{segments_.segE, SEG_OFF},
		{segments_.segF, SEG_OFF},
		{segments_.segG, SEG_OFF},
		{segments_.segDP, showPoint ? SEG_ON : SEG_OFF}
	};
	q74_->SetQPinOutput(pins)
}

void rpicomponents::SevenSegmentDisplay::Write4(bool showPoint) const
{
	QPinMap pins = {
		{segments_.segA, SEG_OFF},
		{segments_.segB, SEG_OFF},
		{segments_.segC, SEG_OFF},
		{segments_.segD, SEG_OFF},
		{segments_.segE, SEG_OFF},
		{segments_.segF, SEG_OFF},
		{segments_.segG, SEG_OFF},
		{segments_.segDP, showPoint ? SEG_ON : SEG_OFF}
	};
	q74_->SetQPinOutput(pins)
}

void rpicomponents::SevenSegmentDisplay::Write5(bool showPoint) const
{
	QPinMap pins = {
		{segments_.segA, SEG_OFF},
		{segments_.segB, SEG_OFF},
		{segments_.segC, SEG_OFF},
		{segments_.segD, SEG_OFF},
		{segments_.segE, SEG_OFF},
		{segments_.segF, SEG_OFF},
		{segments_.segG, SEG_OFF},
		{segments_.segDP, showPoint ? SEG_ON : SEG_OFF}
	};
	q74_->SetQPinOutput(pins)
}

void rpicomponents::SevenSegmentDisplay::Write6(bool showPoint) const
{
	QPinMap pins = {
		{segments_.segA, SEG_OFF},
		{segments_.segB, SEG_OFF},
		{segments_.segC, SEG_OFF},
		{segments_.segD, SEG_OFF},
		{segments_.segE, SEG_OFF},
		{segments_.segF, SEG_OFF},
		{segments_.segG, SEG_OFF},
		{segments_.segDP, showPoint ? SEG_ON : SEG_OFF}
	};
	q74_->SetQPinOutput(pins)
}

void rpicomponents::SevenSegmentDisplay::Write7(bool showPoint) const
{
	QPinMap pins = {
		{segments_.segA, SEG_OFF},
		{segments_.segB, SEG_OFF},
		{segments_.segC, SEG_OFF},
		{segments_.segD, SEG_OFF},
		{segments_.segE, SEG_OFF},
		{segments_.segF, SEG_OFF},
		{segments_.segG, SEG_OFF},
		{segments_.segDP, showPoint ? SEG_ON : SEG_OFF}
	};
	q74_->SetQPinOutput(pins)
}

void rpicomponents::SevenSegmentDisplay::Write8(bool showPoint) const
{
	QPinMap pins = {
		{segments_.segA, SEG_OFF},
		{segments_.segB, SEG_OFF},
		{segments_.segC, SEG_OFF},
		{segments_.segD, SEG_OFF},
		{segments_.segE, SEG_OFF},
		{segments_.segF, SEG_OFF},
		{segments_.segG, SEG_OFF},
		{segments_.segDP, showPoint ? SEG_ON : SEG_OFF}
	};
	q74_->SetQPinOutput(pins)
}

void rpicomponents::SevenSegmentDisplay::Write9(bool showPoint) const
{
	QPinMap pins = {
		{segments_.segA, SEG_OFF},
		{segments_.segB, SEG_OFF},
		{segments_.segC, SEG_OFF},
		{segments_.segD, SEG_OFF},
		{segments_.segE, SEG_OFF},
		{segments_.segF, SEG_OFF},
		{segments_.segG, SEG_OFF},
		{segments_.segDP, showPoint ? SEG_ON : SEG_OFF}
	};
	q74_->SetQPinOutput(pins)
}

void rpicomponents::SevenSegmentDisplay::WriteA(bool showPoint) const
{
	QPinMap pins = {
		{segments_.segA, SEG_OFF},
		{segments_.segB, SEG_OFF},
		{segments_.segC, SEG_OFF},
		{segments_.segD, SEG_OFF},
		{segments_.segE, SEG_OFF},
		{segments_.segF, SEG_OFF},
		{segments_.segG, SEG_OFF},
		{segments_.segDP, showPoint ? SEG_ON : SEG_OFF}
	};
	q74_->SetQPinOutput(pins)
}

void rpicomponents::SevenSegmentDisplay::WriteB(bool showPoint) const
{
	QPinMap pins = {
		{segments_.segA, SEG_OFF},
		{segments_.segB, SEG_OFF},
		{segments_.segC, SEG_OFF},
		{segments_.segD, SEG_OFF},
		{segments_.segE, SEG_OFF},
		{segments_.segF, SEG_OFF},
		{segments_.segG, SEG_OFF},
		{segments_.segDP, showPoint ? SEG_ON : SEG_OFF}
	};
	q74_->SetQPinOutput(pins)
}

void rpicomponents::SevenSegmentDisplay::WriteC(bool showPoint) const
{
	QPinMap pins = {
		{segments_.segA, SEG_OFF},
		{segments_.segB, SEG_OFF},
		{segments_.segC, SEG_OFF},
		{segments_.segD, SEG_OFF},
		{segments_.segE, SEG_OFF},
		{segments_.segF, SEG_OFF},
		{segments_.segG, SEG_OFF},
		{segments_.segDP, showPoint ? SEG_ON : SEG_OFF}
	};
	q74_->SetQPinOutput(pins)
}

void rpicomponents::SevenSegmentDisplay::WriteD(bool showPoint) const
{
	QPinMap pins = {
		{segments_.segA, SEG_OFF},
		{segments_.segB, SEG_OFF},
		{segments_.segC, SEG_OFF},
		{segments_.segD, SEG_OFF},
		{segments_.segE, SEG_OFF},
		{segments_.segF, SEG_OFF},
		{segments_.segG, SEG_OFF},
		{segments_.segDP, showPoint ? SEG_ON : SEG_OFF}
	};
	q74_->SetQPinOutput(pins)
}

void rpicomponents::SevenSegmentDisplay::WriteE(bool showPoint) const
{
	QPinMap pins = {
		{segments_.segA, SEG_OFF},
		{segments_.segB, SEG_OFF},
		{segments_.segC, SEG_OFF},
		{segments_.segD, SEG_OFF},
		{segments_.segE, SEG_OFF},
		{segments_.segF, SEG_OFF},
		{segments_.segG, SEG_OFF},
		{segments_.segDP, showPoint ? SEG_ON : SEG_OFF}
	};
	q74_->SetQPinOutput(pins)
}

void rpicomponents::SevenSegmentDisplay::WriteF(bool showPoint) const
{
	QPinMap pins = {
		{segments_.segA, SEG_OFF},
		{segments_.segB, SEG_OFF},
		{segments_.segC, SEG_OFF},
		{segments_.segD, SEG_OFF},
		{segments_.segE, SEG_OFF},
		{segments_.segF, SEG_OFF},
		{segments_.segG, SEG_OFF},
		{segments_.segDP, showPoint ? SEG_ON : SEG_OFF}
	};
	q74_->SetQPinOutput(pins)
}

void rpicomponents::SevenSegmentDisplay::WriteG(bool showPoint) const
{
	QPinMap pins = {
		{segments_.segA, SEG_OFF},
		{segments_.segB, SEG_OFF},
		{segments_.segC, SEG_OFF},
		{segments_.segD, SEG_OFF},
		{segments_.segE, SEG_OFF},
		{segments_.segF, SEG_OFF},
		{segments_.segG, SEG_OFF},
		{segments_.segDP, showPoint ? SEG_ON : SEG_OFF}
	};
	q74_->SetQPinOutput(pins)
}

void rpicomponents::SevenSegmentDisplay::WriteH(bool showPoint) const
{
	QPinMap pins = {
		{segments_.segA, SEG_OFF},
		{segments_.segB, SEG_OFF},
		{segments_.segC, SEG_OFF},
		{segments_.segD, SEG_OFF},
		{segments_.segE, SEG_OFF},
		{segments_.segF, SEG_OFF},
		{segments_.segG, SEG_OFF},
		{segments_.segDP, showPoint ? SEG_ON : SEG_OFF}
	};
	q74_->SetQPinOutput(pins)
}

void rpicomponents::SevenSegmentDisplay::WriteI(bool showPoint) const
{
	QPinMap pins = {
		{segments_.segA, SEG_OFF},
		{segments_.segB, SEG_OFF},
		{segments_.segC, SEG_OFF},
		{segments_.segD, SEG_OFF},
		{segments_.segE, SEG_OFF},
		{segments_.segF, SEG_OFF},
		{segments_.segG, SEG_OFF},
		{segments_.segDP, showPoint ? SEG_ON : SEG_OFF}
	};
	q74_->SetQPinOutput(pins)
}

void rpicomponents::SevenSegmentDisplay::WriteJ(bool showPoint) const
{
	QPinMap pins = {
		{segments_.segA, SEG_OFF},
		{segments_.segB, SEG_OFF},
		{segments_.segC, SEG_OFF},
		{segments_.segD, SEG_OFF},
		{segments_.segE, SEG_OFF},
		{segments_.segF, SEG_OFF},
		{segments_.segG, SEG_OFF},
		{segments_.segDP, showPoint ? SEG_ON : SEG_OFF}
	};
	q74_->SetQPinOutput(pins)
}

void rpicomponents::SevenSegmentDisplay::WriteL(bool showPoint) const
{
	QPinMap pins = {
		{segments_.segA, SEG_OFF},
		{segments_.segB, SEG_OFF},
		{segments_.segC, SEG_OFF},
		{segments_.segD, SEG_OFF},
		{segments_.segE, SEG_OFF},
		{segments_.segF, SEG_OFF},
		{segments_.segG, SEG_OFF},
		{segments_.segDP, showPoint ? SEG_ON : SEG_OFF}
	};
	q74_->SetQPinOutput(pins)
}

void rpicomponents::SevenSegmentDisplay::WriteO(bool showPoint) const
{
	QPinMap pins = {
		{segments_.segA, SEG_OFF},
		{segments_.segB, SEG_OFF},
		{segments_.segC, SEG_OFF},
		{segments_.segD, SEG_OFF},
		{segments_.segE, SEG_OFF},
		{segments_.segF, SEG_OFF},
		{segments_.segG, SEG_OFF},
		{segments_.segDP, showPoint ? SEG_ON : SEG_OFF}
	};
	q74_->SetQPinOutput(pins)
}

void rpicomponents::SevenSegmentDisplay::WriteP(bool showPoint) const
{
	QPinMap pins = {
		{segments_.segA, SEG_OFF},
		{segments_.segB, SEG_OFF},
		{segments_.segC, SEG_OFF},
		{segments_.segD, SEG_OFF},
		{segments_.segE, SEG_OFF},
		{segments_.segF, SEG_OFF},
		{segments_.segG, SEG_OFF},
		{segments_.segDP, showPoint ? SEG_ON : SEG_OFF}
	};
	q74_->SetQPinOutput(pins)
}

void rpicomponents::SevenSegmentDisplay::WriteQ(bool showPoint) const
{
	QPinMap pins = {
		{segments_.segA, SEG_OFF},
		{segments_.segB, SEG_OFF},
		{segments_.segC, SEG_OFF},
		{segments_.segD, SEG_OFF},
		{segments_.segE, SEG_OFF},
		{segments_.segF, SEG_OFF},
		{segments_.segG, SEG_OFF},
		{segments_.segDP, showPoint ? SEG_ON : SEG_OFF}
	};
	q74_->SetQPinOutput(pins)
}

void rpicomponents::SevenSegmentDisplay::WriteR(bool showPoint) const
{
	QPinMap pins = {
		{segments_.segA, SEG_OFF},
		{segments_.segB, SEG_OFF},
		{segments_.segC, SEG_OFF},
		{segments_.segD, SEG_OFF},
		{segments_.segE, SEG_OFF},
		{segments_.segF, SEG_OFF},
		{segments_.segG, SEG_OFF},
		{segments_.segDP, showPoint ? SEG_ON : SEG_OFF}
	};
	q74_->SetQPinOutput(pins)
}

void rpicomponents::SevenSegmentDisplay::WriteS(bool showPoint) const
{
	QPinMap pins = {
		{segments_.segA, SEG_OFF},
		{segments_.segB, SEG_OFF},
		{segments_.segC, SEG_OFF},
		{segments_.segD, SEG_OFF},
		{segments_.segE, SEG_OFF},
		{segments_.segF, SEG_OFF},
		{segments_.segG, SEG_OFF},
		{segments_.segDP, showPoint ? SEG_ON : SEG_OFF}
	};
	q74_->SetQPinOutput(pins)
}

void rpicomponents::SevenSegmentDisplay::WriteT(bool showPoint) const
{
	QPinMap pins = {
		{segments_.segA, SEG_OFF},
		{segments_.segB, SEG_OFF},
		{segments_.segC, SEG_OFF},
		{segments_.segD, SEG_OFF},
		{segments_.segE, SEG_OFF},
		{segments_.segF, SEG_OFF},
		{segments_.segG, SEG_OFF},
		{segments_.segDP, showPoint ? SEG_ON : SEG_OFF}
	};
	q74_->SetQPinOutput(pins)
}

void rpicomponents::SevenSegmentDisplay::WriteU(bool showPoint) const
{
	QPinMap pins = {
		{segments_.segA, SEG_OFF},
		{segments_.segB, SEG_OFF},
		{segments_.segC, SEG_OFF},
		{segments_.segD, SEG_OFF},
		{segments_.segE, SEG_OFF},
		{segments_.segF, SEG_OFF},
		{segments_.segG, SEG_OFF},
		{segments_.segDP, showPoint ? SEG_ON : SEG_OFF}
	};
	q74_->SetQPinOutput(pins)
}

void rpicomponents::SevenSegmentDisplay::WriteMinus(bool showPoint) const
{
	QPinMap pins = {
		{segments_.segA, SEG_OFF},
		{segments_.segB, SEG_OFF},
		{segments_.segC, SEG_OFF},
		{segments_.segD, SEG_OFF},
		{segments_.segE, SEG_OFF},
		{segments_.segF, SEG_OFF},
		{segments_.segG, SEG_OFF},
		{segments_.segDP, showPoint ? SEG_ON : SEG_OFF}
	};
	q74_->SetQPinOutput(pins)
}

void rpicomponents::SevenSegmentDisplay::WriteUnderscore(bool showPoint) const
{
	QPinMap pins = {
		{segments_.segA, SEG_OFF},
		{segments_.segB, SEG_OFF},
		{segments_.segC, SEG_OFF},
		{segments_.segD, SEG_OFF},
		{segments_.segE, SEG_OFF},
		{segments_.segF, SEG_OFF},
		{segments_.segG, SEG_OFF},
		{segments_.segDP, showPoint ? SEG_ON : SEG_OFF}
	};
	q74_->SetQPinOutput(pins)
}

void rpicomponents::SevenSegmentDisplay::WriteEqual(bool showPoint) const
{
	QPinMap pins = {
		{segments_.segA, SEG_OFF},
		{segments_.segB, SEG_OFF},
		{segments_.segC, SEG_OFF},
		{segments_.segD, SEG_OFF},
		{segments_.segE, SEG_OFF},
		{segments_.segF, SEG_OFF},
		{segments_.segG, SEG_OFF},
		{segments_.segDP, showPoint ? SEG_ON : SEG_OFF}
	};
	q74_->SetQPinOutput(pins)
}

void rpicomponents::SevenSegmentDisplay::Write(bool aOn, bool bOn, bool cOn, bool dOn, bool fOn, bool eOn, bool gOn, bool dpOn) const
{
	QPinMap pins = {
		{segments_.segA, aOn},
		{segments_.segB, bOn},
		{segments_.segC, cOn},
		{segments_.segD, dOn},
		{segments_.segE, eOn},
		{segments_.segF, fOn},
		{segments_.segG, gOn},
		{segments_.segDP, dpOn}
	};
	q74_->SetQPinOutput(pins)
}
