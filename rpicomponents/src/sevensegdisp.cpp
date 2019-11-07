#include "sevensegdisp.hpp"

void rpicomponents::SevenSegmentDisplay::Initialize() const
{
}

rpicomponents::SevenSegmentDisplay::SevenSegmentDisplay(const int& ds_pin, const int& stcp_pin, const int& shcp_pin, const DisplaySegments& dispSegments) : Component(COMPONENT_SEVENSEGMENTDISPLAY), 
	q74_{std::unique_ptr<Q74HC595>(new Q74HC595(ds_pin, stcp_pin, shcp_pin)}, segments_{ dispSegments }
{
}

rpicomponents::SevenSegmentDisplay::SevenSegmentDisplay(const int& ds_pin, const int& stcp_pin, const int& shcp_pin, const int& a, const int& b, const int& c, 
	const int& d, const int& e, const int& f, const int& g, const int& dp) : Component(COMPONENT_SEVENSEGMENTDISPLAY),
	q74_{ std::unique_ptr<Q74HC595>(new Q74HC595(ds_pin, stcp_pin, shcp_pin) }, segments_{ DisplaySegments(a, b, c, d, e, f, g, dp) }
{
}

rpicomponents::SevenSegmentDisplay::SevenSegmentDisplay(int&& ds_pin, int&& stcp_pin, int&& shcp_pin, DisplaySegments&& dispSegments) : Component(COMPONENT_SEVENSEGMENTDISPLAY),
	q74_{ std::unique_ptr<Q74HC595>(new Q74HC595(ds_pin, stcp_pin, shcp_pin) }, segments_{ dispSegments }
{
}

rpicomponents::SevenSegmentDisplay::SevenSegmentDisplay(int&& ds_pin, int&& stcp_pin, int&& shcp_pin, int&& a, int&& b, int&& c, int&& d, int&& e, int&& f, int&& g, int&& dt) : Component(COMPONENT_SEVENSEGMENTDISPLAY),
	q74_{ std::unique_ptr<Q74HC595>(new Q74HC595(ds_pin, stcp_pin, shcp_pin) }, segments_{ DisplaySegments(a, b, c, d, e, f, g, dp) }
{
}

rpicomponents::SevenSegmentDisplay::SevenSegmentDisplay(const SevenSegmentDisplay& sevenSegDisp) : Component(COMPONENT_SEVENSEGMENTDISPLAY),
	q74_{ std::unique_ptr<Q74HC595>(new Q74HC595(sevenSegDisp.GetDsPin(), sevenSegDisp.GetStcpPin(), sevenSegDisp.GetShcpPin()) }, segments_{ sevenSegDisp.GetDisplaySegments() }
{
}

const int& rpicomponents::SevenSegmentDisplay::GetDsPin() const
{
	return q74_->GetDsPin();
}

const int& rpicomponents::SevenSegmentDisplay::GetStcpPin() const
{
	return q74_->GetStcpPin();
}

const int& rpicomponents::SevenSegmentDisplay::GetShcpPin() const
{
	return q74_->GetShcpPin();
}

const DisplaySegments& rpicomponents::SevenSegmentDisplay::GetDisplaySegments() const
{
	return segments_;
}

void rpicomponents::SevenSegmentDisplay::TurnOffAll() const
{
}

void rpicomponents::SevenSegmentDisplay::TurnOnAll() const
{
}

void rpicomponents::SevenSegmentDisplay::Write0(bool showPoint) const
{
}

void rpicomponents::SevenSegmentDisplay::Write1(bool showPoint) const
{
}

void rpicomponents::SevenSegmentDisplay::Write2(bool showPoint) const
{
}

void rpicomponents::SevenSegmentDisplay::Write3(bool showPoint) const
{
}

void rpicomponents::SevenSegmentDisplay::Write4(bool showPoint) const
{
}

void rpicomponents::SevenSegmentDisplay::Write5(bool showPoint) const
{
}

void rpicomponents::SevenSegmentDisplay::Write6(bool showPoint) const
{
}

void rpicomponents::SevenSegmentDisplay::Write7(bool showPoint) const
{
}

void rpicomponents::SevenSegmentDisplay::Write8(bool showPoint) const
{
}

void rpicomponents::SevenSegmentDisplay::Write9(bool showPoint) const
{
}

void rpicomponents::SevenSegmentDisplay::WriteA(bool showPoint) const
{
}

void rpicomponents::SevenSegmentDisplay::WriteB(bool showPoint) const
{
}

void rpicomponents::SevenSegmentDisplay::WriteC(bool showPoint) const
{
}

void rpicomponents::SevenSegmentDisplay::WriteD(bool showPoint) const
{
}

void rpicomponents::SevenSegmentDisplay::WriteE(bool showPoint) const
{
}

void rpicomponents::SevenSegmentDisplay::WriteF(bool showPoint) const
{
}

void rpicomponents::SevenSegmentDisplay::WriteG(bool showPoint) const
{
}

void rpicomponents::SevenSegmentDisplay::WriteH(bool showPoint) const
{
}

void rpicomponents::SevenSegmentDisplay::WriteI(bool showPoint) const
{
}

void rpicomponents::SevenSegmentDisplay::WriteJ(bool showPoint) const
{
}

void rpicomponents::SevenSegmentDisplay::WriteL(bool showPoint) const
{
}

void rpicomponents::SevenSegmentDisplay::WriteO(bool showPoint) const
{
}

void rpicomponents::SevenSegmentDisplay::WriteP(bool showPoint) const
{
}

void rpicomponents::SevenSegmentDisplay::WriteQ(bool showPoint) const
{
}

void rpicomponents::SevenSegmentDisplay::WriteR(bool showPoint) const
{
}

void rpicomponents::SevenSegmentDisplay::WriteS(bool showPoint) const
{
}

void rpicomponents::SevenSegmentDisplay::WriteT(bool showPoint) const
{
}

void rpicomponents::SevenSegmentDisplay::WriteU(bool showPoint) const
{
}

void rpicomponents::SevenSegmentDisplay::WriteMinus(bool showPoint) const
{
}

void rpicomponents::SevenSegmentDisplay::WriteUnderscore(bool showPoint) const
{
}

void rpicomponents::SevenSegmentDisplay::WriteEqual(bool showPoint) const
{
}

void rpicomponents::SevenSegmentDisplay::Write(aOn, bOn, cOn, dOn, fOn, eOn, gOn, dpOn) const
{
}
