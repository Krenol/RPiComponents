#include "component.hpp"

#ifndef RPICOMPONENTS_L293D_H
#define RPICOMPONENTS_L293D_H

namespace rpicomponents {
	constexpr const char* COMPONENT_L293D = "l293d";
	constexpr const int L293D_INPIN_COUNT = 4, L293D_ENABLEPIN_COUNT = 2;

	struct EnablePinStruct {
		//Constructor for const vals
		EnablePinStruct(int enable_pin1, int enable_pin2, rpicomponents::pin::PIN_MODE enable_pin1_mode = rpicomponents::pin::SOFTPWM_MODE,
			rpicomponents::pin::PIN_MODE enable_pin2_mode = rpicomponents::pin::SOFTPWM_MODE, int max_output_enable_pin1 = 254, int max_output_enable_pin2 = 254) :
			enable_pin1_(enable_pin1), enable_pin2_(enable_pin2), enable_pin1_mode_(enable_pin1_mode), enable_pin2_mode_ (enable_pin2_mode), 
			max_output_enable_pin1_(max_output_enable_pin1), max_output_enable_pin2_ (max_output_enable_pin2){}

		EnablePinStruct(const EnablePinStruct& enablePins) :
			enable_pin1_(enablePins.enable_pin1_), enable_pin2_(enablePins.enable_pin2_), enable_pin1_mode_(enablePins.enable_pin1_mode_), enable_pin2_mode_(enablePins.enable_pin2_mode_),
			max_output_enable_pin1_(enablePins.max_output_enable_pin1_), max_output_enable_pin2_(enablePins.max_output_enable_pin2_) {}

		const int enable_pin1_, enable_pin2_;
		const rpicomponents::pin::PIN_MODE enable_pin1_mode_, enable_pin2_mode_;
		const int max_output_enable_pin1_, max_output_enable_pin2_;
	};

	struct InPinStruct {
		//Constructor for const vals
		InPinStruct(int in_pin1, int in_pin2, int in_pin3, int in_pin4) :
			in_pin1_(in_pin1), in_pin2_(in_pin2), in_pin3_(in_pin3), in_pin4_(in_pin4) {}

		InPinStruct(const InPinStruct& inPins) :
			in_pin1_(inPins.in_pin1_), in_pin2_(inPins.in_pin2_), in_pin3_(inPins.in_pin3_), in_pin4_(inPins.in_pin4_) {}

		const int in_pin1_, in_pin2_, in_pin3_, in_pin4_;
	};

	class L293D : Component {
	private:
		const std::unique_ptr<pin::Pin> enable_pin1_, enable_pin2_; //the used enable pins of the l293d
		const std::unique_ptr<pin::Pin> in_pin1_, in_pin2_, in_pin3_, in_pin4_; //the used in pins of the l293d
        const InPinStruct inPins_;
        const EnablePinStruct enablePins_;
		/*
		Initiliazer for this component
		*/
        void Initialize();

	public:
		/*
		 Constructor for this component

		 @param enable_pin1 The first enable pin of the l293d
		 @param enable_pin2 The second enable pin of the l293d
		 @param enable_pin1_mode The pin mode of the first pin
		 @param enable_pin2_mode The pin mode of the second pin
		 @param max_output_enable_pin1 The max output value of the first pin
		 @param max_output_enable_pin2 The max output value of the second pin
		 @param in_pin1 The first input pin
		 @param in_pin2 The second input pin
		 @param in_pin3 The third input pin
		 @param in_pin4 The fourth input pin
		*/
		L293D(int enable_pin1, int enable_pin2, rpicomponents::pin::PIN_MODE enable_pin1_mode = rpicomponents::pin::SOFTPWM_MODE,
			rpicomponents::pin::PIN_MODE enable_pin2_mode = rpicomponents::pin::SOFTPWM_MODE, int max_output_enable_pin1 = 254, int max_output_enable_pin2 = 254,
			int in_pin1 = -1, int in_pin2 = -1, int in_pin3 = -1, int in_pin4 = -1);

		/*
		 Constructor for this component

		 @param enable_pins The EnablePinStruct struct containing all necessary enable pin information for the l293d
		 @param in_pins The InPinStruct struct containing all necessary in pin information for the l293d
		 */
		L293D(const EnablePinStruct& enable_pins, const InPinStruct& in_pins);

		/*
		 Copy constructor for this component

		 @param l293d The to be copied L293D
		*/
		L293D(const L293D& l293d);

		/*
		Method to get the enable pin parameters

		@returns a EnablePinStruct containing the parameters of enable pin 1 and 2
		*/
        const EnablePinStruct& GetEnablePins() const;

		/*
		Method to get the in pin parameters

		@returns a InPinStruct containing the parameters of input pin 1, 2, 3 and 4
		*/
        const InPinStruct& GetInPins() const;

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
		bool WriteToInPin(int pinNo, bool turnOn) const;

		/*
		Method to turn on/off to a specific enable pin
		@param pinNo: The enable pin to be turned on/off; between 1 and 2
		@param turnOn: If true pin is tunrned on, else off
		*/
		bool WriteToEnablePin(int pinNo, bool turnOn) const;

		/*
		Method to turn on/off to a specific enable pin
		@param pinNo: The enable pin to be turned on/off; between 1 and 2
		@param value: The value to which the pin should be turned on to
		*/
		bool WriteToEnablePin(int pinNo, int value) const;
	};
}

#endif
