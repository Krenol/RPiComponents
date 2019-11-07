#include "component.hpp"
#include "q74hc595.hpp"

#ifndef RPICOMPONENTS_SEVENSEGMENTDISPLAY_H
#define RPICOMPONENTS_SEVENSEGMENTDISPLAY_H

namespace rpicomponents {
	constexpr const char* COMPONENT_SEVENSEGMENTDISPLAY = "led";

	struct DisplaySegments {
		DisplaySegments(const int& a = 0, const int& b = 1, const int& c = 2, const int& d = 3, const int& e = 4, const int& f = 5, const int& g = 6, const int& dp = 7) :
			segA{ a }, segB{ b }, segC{ c }, segD{ d }, segE{ e }, segF{ f }, segG{ g }, segDP{ dp }
		{

		}

		const int segA, segB, segC, segD, segE, segF, segG, segDP;
	};

	class SevenSegmentDisplay : public Component {
	private:
		std::unique_ptr<Q74HC595> q74_;
		const DisplaySegments segments_;

		/*
		method to initialize seven segment display
		*/
		void Initialize() const;

	public:
		/*
		Constructor for 7-segment display

		@param ds_pin: Pin number of the ds
		@param stcp_pin: Pin number of the stcp
		@param shcp_pin: Pin number of the shcp
		@param dispSegments: DisplaySegments struct holding the q74 pin to display pin wiring values
		*/
		SevenSegmentDisplay(const int& ds_pin, const int& stcp_pin, const int& shcp_pin, const DisplaySegments& dispSegments);

		/*
		Constructor for 7-segment display

		@param ds_pin: Pin number of the ds
		@param stcp_pin: Pin number of the stcp
		@param shcp_pin: Pin number of the shcp
		@param a: Q74 pin segment A is wired to 
		@param b: Q74 pin segment B is wired to
		@param c: Q74 pin segment C is wired to
		@param d: Q74 pin segment D is wired to
		@param e: Q74 pin segment E is wired to
		@param f: Q74 pin segment F is wired to
		@param g: Q74 pin segment G is wired to
		@param dp: Q74 pin segment DP is wired to
		*/
		SevenSegmentDisplay(const int& ds_pin, const int& stcp_pin, const int& shcp_pin, const int& a = 0, const int& b = 1, 
			const int& c = 2, const int& d = 3, const int& e = 4, const int& f = 5, const int& g = 6, const int& dp = 7);

		/*
		Constructor for 7-segment display

		@param ds_pin: Pin number of the ds
		@param stcp_pin: Pin number of the stcp
		@param shcp_pin: Pin number of the shcp
		@param dispSegments: DisplaySegments struct holding the q74 pin to display pin wiring values
		*/
		SevenSegmentDisplay(int&& ds_pin, int&& stcp_pin, int&& shcp_pin, DisplaySegments&& dispSegments);

		/*
		Constructor for 7-segment display

		@param ds_pin: Pin number of the ds
		@param stcp_pin: Pin number of the stcp
		@param shcp_pin: Pin number of the shcp
		@param a: Q74 pin segment A is wired to
		@param b: Q74 pin segment B is wired to
		@param c: Q74 pin segment C is wired to
		@param d: Q74 pin segment D is wired to
		@param e: Q74 pin segment E is wired to
		@param f: Q74 pin segment F is wired to
		@param g: Q74 pin segment G is wired to
		@param dp: Q74 pin segment DP is wired to
		*/
		SevenSegmentDisplay(int&& ds_pin, int&& stcp_pin, int&& shcp_pin, int&& a = 0, int&& b = 1,
			int&& c = 2, int&& d = 3, int&& e = 4, int&& f = 5, int&& g = 6, int&& dt = 7);

		/* 
		Copy constructor for 7-segment display

		@param sevenSegDisp: The 7-segment display to be copied
		*/
		SevenSegmentDisplay(const SevenSegmentDisplay& sevenSegDisp);


		/*
		Method to get the DS pin number
		@returns the used ds pin
		*/
		const int& GetDsPin() const;

		/*
		Method to get the STCP pin number
		@returns the used stcp pin
		*/
		const int& GetStcpPin() const;

		/*
		Method to get the SHCP pin number
		@returns the used shcp pin
		*/
		const int& GetShcpPin() const;

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

		void Write0(bool showPoint = false) const;
		void Write1(bool showPoint = false) const;
		void Write2(bool showPoint = false) const;
		void Write3(bool showPoint = false) const;
		void Write4(bool showPoint = false) const;
		void Write5(bool showPoint = false) const;
		void Write6(bool showPoint = false) const;
		void Write7(bool showPoint = false) const;
		void Write8(bool showPoint = false) const;
		void Write9(bool showPoint = false) const;
		void WriteA(bool showPoint = false) const;
		void WriteB(bool showPoint = false) const;
		void WriteC(bool showPoint = false) const;
		void WriteD(bool showPoint = false) const;
		void WriteE(bool showPoint = false) const;
		void WriteF(bool showPoint = false) const;
		void WriteG(bool showPoint = false) const;
		void WriteH(bool showPoint = false) const;
		void WriteI(bool showPoint = false) const;
		void WriteJ(bool showPoint = false) const;
		void WriteL(bool showPoint = false) const;
		void WriteO(bool showPoint = false) const;
		void WriteP(bool showPoint = false) const;
		void WriteQ(bool showPoint = false) const;
		void WriteR(bool showPoint = false) const;
		void WriteS(bool showPoint = false) const;
		void WriteT(bool showPoint = false) const;
		void WriteU(bool showPoint = false) const;
		void WriteMinus(bool showPoint = false) const;
		void WriteUnderscore(bool showPoint = false) const;
		void WriteEqual(bool showPoint = false) const;

		void Write(aOn = false, bOn = false, cOn = false, dOn = false, fOn = false, eOn = false, gOn = false, dtOn = false) const;
	};


}
#endif