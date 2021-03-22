#include "component.hpp"
#include "q74hc595.hpp"

#ifndef RPICOMPONENTS_SEVENSEGMENTDISPLAY_H
#define RPICOMPONENTS_SEVENSEGMENTDISPLAY_H

namespace rpicomponents {
	constexpr const char* COMPONENT_SEVENSEGMENTDISPLAY = "sevensegmentdisplay";

	struct DisplaySegments {
		DisplaySegments(int a = 0, int b = 1, int c = 2, int d = 3, int e = 4, int f = 5, int g = 6, int dp = 7) :
			segA{ a }, segB{ b }, segC{ c }, segD{ d }, segE{ e }, segF{ f }, segG{ g }, segDP{ dp }
		{

		}

		DisplaySegments(const DisplaySegments& disSegments) : segA{ disSegments.segA }, segB{ disSegments.segB }, segC{ disSegments.segC }, 
			segD{ disSegments.segD }, segE{ disSegments.segE }, segF{ disSegments.segF }, segG{ disSegments.segF }, segDP{ disSegments.segDP }
		{

		}

		const int segA, segB, segC, segD, segE, segF, segG, segDP;
	};

	constexpr bool SEG_ON = false, SEG_OFF = true;

	class SevenSegmentDisplay : public Component {
	private:
		std::unique_ptr<Q74HC595> q74_;
		const DisplaySegments segments_;

	public:
		/*
		Constructor for 7-segment display

		@param q74hc595: The used Q74HC595 of the 7 seg display
		@param dispSegments: DisplaySegments struct holding the q74 pin to display pin wiring values
		*/
		SevenSegmentDisplay(std::unique_ptr<Q74HC595> q74hc595, const DisplaySegments& dispSegments);

		/*
		Constructor for 7-segment display

		@param q74hc595: The used Q74HC595 of the 7 seg display
		@param a: Q74 pin segment A is wired to 
		@param b: Q74 pin segment B is wired to
		@param c: Q74 pin segment C is wired to
		@param d: Q74 pin segment D is wired to
		@param e: Q74 pin segment E is wired to
		@param f: Q74 pin segment F is wired to
		@param g: Q74 pin segment G is wired to
		@param dp: Q74 pin segment DP is wired to
		*/
		SevenSegmentDisplay(std::unique_ptr<Q74HC595> q74hc595, int a = 0, int b = 1,
			int c = 2, int d = 3, int e = 4, int f = 5, int g = 6, int dp = 7);

		/* 
		Copy constructor for 7-segment display

		@param sevenSegDisp: The 7-segment display to be copied
		*/
		SevenSegmentDisplay(const SevenSegmentDisplay& sevenSegDisp);


		/*
		Method to get the DS pin number
		@returns the used ds pin
		*/
		const std::unique_ptr<Q74HC595>& GetQ74HC595() const;


		/*
		Method to get the display segments of this 7-segment display

		@returns the DisplaySegments struct holding the 8 segment values
		*/
		const DisplaySegments& GetDisplaySegments() const;

		/*
		Method to turn off the 7-segment display
		*/
		void TurnOffAll() const;

		/*
		Method to turn on all segments of the 7-segment display
		*/
		void TurnOnAll() const;

		/*
		Method to write a 0 on the display
		*/
		void Write0(bool showPoint = false) const;

		/*
		Method to write a 1 on the display
		*/
		void Write1(bool showPoint = false) const;

		/*
		Method to write a 2 on the display
		*/
		void Write2(bool showPoint = false) const;

		/*
		Method to write a 3 on the display
		*/
		void Write3(bool showPoint = false) const;

		/*
		Method to write a 4 on the display
		*/
		void Write4(bool showPoint = false) const;

		/*
		Method to write a 5 on the display
		*/
		void Write5(bool showPoint = false) const;

		/*
		Method to write a 6 on the display
		*/
		void Write6(bool showPoint = false) const;

		/*
		Method to write a 7 on the display
		*/
		void Write7(bool showPoint = false) const;

		/*
		Method to write a 8 on the display
		*/
		void Write8(bool showPoint = false) const;

		/*
		Method to write a 9 on the display
		*/
		void Write9(bool showPoint = false) const;

		/*
		Method to write an A on the display
		*/
		void WriteA(bool showPoint = false) const;

		/*
		Method to write a B on the display
		*/
		void WriteB(bool showPoint = false) const;

		/*
		Method to write a C on the display
		*/
		void WriteC(bool showPoint = false) const;

		/*
		Method to write a D on the display
		*/
		void WriteD(bool showPoint = false) const;

		/*
		Method to write a E on the display
		*/
		void WriteE(bool showPoint = false) const;

		/*
		Method to write a F on the display
		*/
		void WriteF(bool showPoint = false) const;

		/*
		Method to write a G on the display
		*/
		void WriteG(bool showPoint = false) const;

		/*
		Method to write a H on the display
		*/
		void WriteH(bool showPoint = false) const;

		/*
		Method to write a I on the display
		*/
		void WriteI(bool showPoint = false) const;

		/*
		Method to write a J on the display
		*/
		void WriteJ(bool showPoint = false) const;

		/*
		Method to write a L on the display
		*/
		void WriteL(bool showPoint = false) const;

		/*
		Method to write a O on the display
		*/
		void WriteO(bool showPoint = false) const;

		/*
		Method to write a P on the display
		*/
		void WriteP(bool showPoint = false) const;

		/*
		Method to write a Q on the display
		*/
		void WriteQ(bool showPoint = false) const;

		/*
		Method to write a R on the display
		*/
		void WriteR(bool showPoint = false) const;

		/*
		Method to write a S on the display
		*/
		void WriteS(bool showPoint = false) const;

		/*
		Method to write a T on the display
		*/
		void WriteT(bool showPoint = false) const;

		/*
		Method to write a U on the display
		*/
		void WriteU(bool showPoint = false) const;

		/*
		Method to write a minus on the display
		*/
		void WriteMinus(bool showPoint = false) const;

		/*
		Method to write an underscore on the display
		*/
		void WriteUnderscore(bool showPoint = false) const;

		/*
		Method to write a = on the display
		*/
		void WriteEqual(bool showPoint = false) const;


		/*
		Method to turn on/off each segment by choice

		@param aOn: Segment A is to be set on (true) or off (false)
		@param bOn: Segment B is to be set on (true) or off (false)
		@param cOn: Segment C is to be set on (true) or off (false)
		@param dOn: Segment D is to be set on (true) or off (false)
		@param eOn: Segment E is to be set on (true) or off (false)
		@param fOn: Segment F is to be set on (true) or off (false)
		@param gOn: Segment G is to be set on (true) or off (false)
		@param dpOn: Segment DT is to be set on (true) or off (false)
		*/
		void Write(bool aOn = false, bool bOn = false, bool cOn = false, bool  dOn = false, bool fOn = false, bool eOn = false, bool gOn = false, bool dpOn = false) const;
	};


}
#endif