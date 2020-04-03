#include "component.hpp"
#include <map>
#ifndef RPICOMPONENTS_L293D_H
#define RPICOMPONENTS_L293D_H

namespace rpicomponents {
	constexpr const char* COMPONENT_L293D = "l293d";
	constexpr const int L293D_INPIN_COUNT = 4, L293D_ENABLEPIN_COUNT = 2;
	typedef std::map<int, std::shared_ptr<pin::Pin>> EnablePinMap;
	typedef std::map<int, std::shared_ptr<pin::Pin>> InPinMap;

    class L293D : public Component {
	private:
		const EnablePinMap enablePins_;
		const InPinMap inPins_;

		/*
		Initiliazer for this component
		*/
        void Initialize();

	public:
		/*
		 Constructor for this component

		 @param enable_pin1 The first enable pin of the l293d (Software PWM or Hardware PWM)
		 @param enable_pin2 The second enable pin of the l293d (Software PWM or Hardware PWM)
		 @param in_pin1 The first input pin
		 @param in_pin2 The second input pin
		 @param in_pin3 The third input pin
		 @param in_pin4 The fourth input pin
		*/
		L293D(std::shared_ptr<pin::Pin> enable_pin1, std::shared_ptr<pin::Pin> enable_pin2, std::shared_ptr<pin::Pin> in_pin1, 
			std::shared_ptr<pin::Pin> in_pin2, std::shared_ptr<pin::Pin> in_pin3, std::shared_ptr<pin::Pin> in_pin4);

		L293D(const EnablePinMap& enablePins, const InPinMap& inPins);

		/*
		 Copy constructor for this component

		 @param l293d The to be copied L293D
		*/
		L293D(const L293D& l293d);

		/*
		Method to get the enable pin parameters

		@returns a EnablePinStruct containing the parameters of enable pin 1 and 2
		*/
        const EnablePinMap& GetEnablePins() const;

		/*
		Method to get the in pin parameters

		@returns a InPinStruct containing the parameters of input pin 1, 2, 3 and 4
		*/
        const InPinMap& GetInPins() const;

		/*
		Method to turn on in pin 1
		*/
		void TurnOnIn1() const;

		/*
		Method to turn on in pin 2
		*/
		void TurnOnIn2() const;

		/*
		Method to turn on in pin 3
		*/
		void TurnOnIn3() const;

		/*
		Method to turn on in pin 4
		*/
		void TurnOnIn4() const;

		/*
		Method to turn off in pin 1
		*/
		void TurnOffIn1() const;

		/*
		Method to turn off in pin 2
		*/
		void TurnOffIn2() const;

		/*
		Method to turn off in pin 3
		*/
		void TurnOffIn3() const;

		/*
		Method to turn off in pin 4
		*/
		void TurnOffIn4() const;

		/*
		Method to turn on the enable pin 1 to it's max value
		*/
		void TurnOnEnablePin1() const;

		/*
		Method to turn on the enable pin 1

		@param value The value to which the pin should be turned on to
		*/
		void TurnOnEnablePin1(int value) const;

		/*
		Method to turn of the enable pin 1
		*/
		void TurnOffEnablePin1() const;

		/*
		Method to turn on the enable pin 2 to it's max value
		*/
		void TurnOnEnablePin2() const;

		/*
		Method to turn on the enable pin 2

		@param value The value to which the pin should be turned on to
		*/
		void TurnOnEnablePin2(int value) const;

		/*
		Method to turn of the enable pin 2
		*/
		void TurnOffEnablePin2() const;

		/*
		Method to get the current output value of enable pin 1

		@returns the output value of enable pin 1 as int
		*/
		int EnablePin1OutputValue() const;

		/*
		Method to get the current output value of enable pin 2

		@returns the output value of enable pin 2 as int
		*/
		int EnablePin2OutputValue() const;

		/*
		Method that returns whether in pin 1 is on (output 1) or not (output 0)

		@returns true if pin is on else false
		*/
		bool InPin1On() const;

		/*
		Method that returns whether in pin 2 is on (output 1) or not (output 0)

		@returns true if pin is on else false
		*/
		bool InPin2On() const;

		/*
		Method that returns whether in pin 3 is on (output 1) or not (output 0)

		@returns true if pin is on else false
		*/
		bool InPin3On() const;

		/*
		Method that returns whether in pin 4 is on (output 1) or not (output 0)

		@returns true if pin is on else false
		*/
		bool InPin4On() const;

		/*
		Method to turn on/off to a specific inPin
		@param pinNo: The inPin to be turned on/off; between 1 and 4
		@param turnOn: If true pin is tunrned on, else off
		*/
		void WriteToInPin(int pinNo, bool turnOn) const;

		/*
		Method to turn on/off to a specific enable pin
		@param pinNo: The enable pin to be turned on/off; between 1 and 2
		@param turnOn: If true pin is tunrned on, else off
		*/
		void WriteToEnablePin(int pinNo, bool turnOn) const;

		/*
		Method to turn on/off to a specific enable pin
		@param pinNo: The enable pin to be turned on/off; between 1 and 2
		@param value: The value to which the pin should be turned on to
		*/
		void WriteToEnablePin(int pinNo, int value) const;

		/*
		Method that returns true if given pin is on else false
		@param pinNo: The inPin to be turned on/off; between 1 and 4
		@returns true if pin is on else false
		*/
		bool InPinIsOn(int pinNo) const;

		/*
		method to get the output value of an enable pin
		@param pinNo: The inPin to be turned on/off; between 1 and 4
		@returns the output value of the passed enable pin as int
		*/
		int EnablePinOutputValue(int pinNo) const;

		/*
		Method to check if a pin is a valid enable pin

		@param pinNo: The pin to be checked

		@returns true if valid enable pin, else false
		*/
		bool ValidEnablePin(int pinNo) const;

		/*
		Method to check if a pin is a valid in pin

		@param pinNo: The pin to be checked

		@returns true if valid in pin, else false
		*/
		bool ValidInPin(int pinNo) const;
	};
}

#endif
