#include "component.hpp"

#ifndef RPICOMPONENTS_L293D_H
#define RPICOMPONENTS_L293D_H

namespace rpicomponents {
	constexpr const char* COMPONENT_L293D = "l293d";

	struct EnablePinStruct {
		//Constructor for const vals
		EnablePinStruct(const int& enable_pin1, const int& enable_pin2, const rpicomponents::pin::PIN_MODE& enable_pin1_mode = rpicomponents::pin::SOFTPWM_MODE,
			const rpicomponents::pin::PIN_MODE& enable_pin2_mode = rpicomponents::pin::SOFTPWM_MODE, const int& max_output_enable_pin1 = 254, const int& max_output_enable_pin2 = 254) :
			enable_pin1_(enable_pin1), enable_pin2_(enable_pin2), enable_pin1_mode_(enable_pin1_mode), enable_pin2_mode_ (enable_pin2_mode), 
			max_output_enable_pin1_(max_output_enable_pin1), max_output_enable_pin2_ (max_output_enable_pin2_){}

		const int enable_pin1_, enable_pin2_;
		const rpicomponents::pin::PIN_MODE enable_pin1_mode_, enable_pin2_mode_;
		const int max_output_enable_pin1_, max_output_enable_pin2_;
	};

	struct InPinStruct {
		//Constructor for const vals
		InPinStruct(const int& in_pin1, const int& in_pin2, const int& in_pin3, const int& in_pin4) :
			in_pin1_(in_pin1), in_pin2_(in_pin2), in_pin3_(in_pin3), in_pin4_(in_pin4) {}

		const int in_pin1_, in_pin2_, in_pin3_, in_pin4_;
	};

	class L293D : Component {
	private:
		const std::unique_ptr<pin::Pin> enable_pin1_, enable_pin2_; //the used enable pins of the l293d
		const std::unique_ptr<pin::Pin> in_pin1_, in_pin2_, in_pin3_, in_pin4_; //the used in pins of the l293d

		/*
		Initiliazer for this component
		*/
		void Initialize() const;

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
		L293D(const int& enable_pin1, const int& enable_pin2, const rpicomponents::pin::PIN_MODE& enable_pin1_mode = rpicomponents::pin::SOFTPWM_MODE,
			const rpicomponents::pin::PIN_MODE& enable_pin2_mode = rpicomponents::pin::SOFTPWM_MODE, const int& max_output_enable_pin1 = 254, const int& max_output_enable_pin2 = 254,
			const int& in_pin1 = -1, const int& in_pin2 = -1, const int& in_pin3 = -1, const int& in_pin4 = -1);

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
		L293D(int&& enable_pin1, int&& enable_pin2, rpicomponents::pin::PIN_MODE&& enable_pin1_mode = rpicomponents::pin::SOFTPWM_MODE,
			rpicomponents::pin::PIN_MODE&& enable_pin2_mode = rpicomponents::pin::SOFTPWM_MODE, int&& max_output_enable_pin1 = 254, int&& max_output_enable_pin2 = 254,
			int&& in_pin1 = -1, int&& in_pin2 = -1, int&& in_pin3 = -1, int&& in_pin4 = -1);

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
		EnablePinStruct GetEnablePins() const;

		/*
		Method to get the in pin parameters

		@returns a InPinStruct containing the parameters of input pin 1, 2, 3 and 4
		*/
		InPinStruct GetInPins() const;

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
		void TurnOnEnablePin1(const int& value) const;

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
		void TurnOnEnablePin2(const int& value) const;

		/*
		Method to turn of the enable pin 2
		*/
		void TurnOffEnablePin2() const;
	};
}

#endif