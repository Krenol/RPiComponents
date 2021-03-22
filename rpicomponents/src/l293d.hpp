#include "component.hpp"
#include <map>
#ifndef RPICOMPONENTS_L293D_H
#define RPICOMPONENTS_L293D_H

namespace rpicomponents {
	constexpr const char* COMPONENT_L293D = "l293d";
	constexpr const int L293D_INPIN_COUNT = 4, L293D_ENABLEPIN_COUNT = 2;

    class L293D : public Component {
	private:
		std::unique_ptr<pin::Pin> enable1_, enable2_, in1_, in2_, in3_, in4_;
		std::map <int, std::unique_ptr<pin::Pin>&> inPins_, enablePins_;

		/*
		Initiliazer for this component
		*/
        void Initialize();

	public:
		/*
		 Constructor for this component

		 @param enable_pin1 The first enable pin of the l293d 
		 @param enable_pin1_mode: The mode of the first enable pin
		 @param enable_pin1_max: Max value of the first enable pin
		 @param enable_pin2 The second enable pin of the l293d
		 @param enable_pin2_mode: The mode of the second enable pin
		 @param enable_pin2_max: Max value of the second enable pin
		 @param in_pin1 The first input pin
		 @param in_pin2 The second input pin
		 @param in_pin3 The third input pin
		 @param in_pin4 The fourth input pin
		*/
		L293D(int enable_pin1, pin::PIN_MODE enable_pin1_mode, int enable_pin1_max, int enable_pin2, pin::PIN_MODE enable_pin2_mode, int enable_pin2_max, int in_pin1, 
			int in_pin2, int in_pin3, int in_pin4);

		/*
		 Copy constructor for this component

		 @param l293d The to be copied L293D
		*/
		L293D(const L293D& l293d);

		/*
		 Constructor for this component

		 @param enable_pin1 The first enable pin of the l293d 
		 @param enable_pin2 The second enable pin of the l293d 
		 @param in_pin1 The first input pin
		 @param in_pin2 The second input pin
		 @param in_pin3 The third input pin
		 @param in_pin4 The fourth input pin
		*/
		L293D(const pin::pin_data& enable_pin1, const pin::pin_data& enable_pin2, int in_pin1, 
			int in_pin2, int in_pin3, int in_pin4);

		/**
		 * Method to get the pin_data of all enable pins
		 * @returns a map containing the pin_data of each enable pin
		 */
		std::map<int, pin::pin_data> GetEnablePins() const;

		/**
		 * Method to get the pin_data of all in pins
		 * @returns a map containing the pin_data of each in pin
		 */
		std::map<int, pin::pin_data> GetInPins() const;

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
