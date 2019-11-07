#include "component.hpp"
#include <map>

#ifndef RPICOMPONENTS_Q74HC595_H
#define RPICOMPONENTS_Q74HC595_H

namespace rpicomponents {

	constexpr const char* COMPONENT_Q74HC595 = "q74hc595";

	class Q74HC595 : public Component
	{
	private:
		const std::unique_ptr<pin::Pin> ds_, stcp_, shcp_;
        const int max_q_pin_no_{ 8 };
		mutable std::map<int, bool> q_pin_map_;

		/*
		Initializer for Constructors; reduce redundancy
		*/
		void Initialize() const;

		/*
		Method to check whether a pin number matches the required pin range of q74hc595

		@param pin_no: pin_no to be checked
		@returns true if 0 <= pin_no < max_q_pin_no_ else false
		*/
		bool ValidQPin(const int& pin_no) const;

		/*
		Method to set a Q_Pin of the q_pin_map_
		throws an error for wrong pin_no outside range 0 <= pin_no < max_q_pin_no_
		
		@param pin_no: q pin number to be retrieved
		@param turn_on: bool whether Q_Pin is to be turned on or off
		*/
        void SetQPin(const int& pin_no, bool turn_on) const;

		/*
		Method to write to the q74hc595 q_pins with values stored in the q_pin_map_

		*/
		void WriteToQPins() const;

	public:
		/*
		Constructor for creating a Q74HC595
		
		@param ds_pin: Pin number of the ds
		@param stcp_pin: Pin number of the stcp
		@param shcp_pin: Pin number of the shcp
		*/
		Q74HC595(const int& ds_pin, const int& stcp_pin, const int& shcp_pin);

		/*
		Constructor for creating a Q74HC595
		
		@param ds_pin: Pin number of the ds
		@param stcp_pin: Pin number of the stcp
		@param shcp_pin: Pin number of the shcp
		*/
		Q74HC595(int&& ds_pin, int&& stcp_pin, int&& shcp_pin);

		/*
		Copy Constructor for Q74HC595

		@param q74hc595 q74hc595 to be copied
		*/
		Q74HC595(const Q74HC595& q74hc595);

		/*
		Method to set a q_pin on or off
		Wrong input throws an error
		
		@param pin: Q_Pin to be turned on/off according to boolean turn_on
		@param turn_on: Turn on or off the passed pin
		*/
		void SetQPinOutput(const int& pin, bool turn_on) const;

		/*
		Method to get the status of a q_pin
		Wrong input throws an error

		@param pin: Q_Pin for whcih status is to be returned
		@returns true if pin is on, else false
		*/
		bool GetQPinOutput(const int& pin) const;

		/*
		Method to turn off all Q_Pins
		*/
		void TurnOn() const;

		/*
		Method to turn off all Q_Pins
		*/
		void TurnOff() const;

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
		Method to get the max count of q pins for this component
		*/
        const int& GetMaxQPinCount() const;
	};
}
#endif
