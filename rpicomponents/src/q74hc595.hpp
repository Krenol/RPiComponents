#include "component.hpp"
#include <map>

#ifndef RPICOMPONENTS_Q74HC595_H
#define RPICOMPONENTS_Q74HC595_H

namespace rpicomponents {

	constexpr const char* COMPONENT_Q74HC595 = "q74hc595";

	class Q74HC595 : public Component
	{
	private:
		const std::shared_ptr<pin::Pin> ds_, stcp_, shcp_;
        const int max_q_pin_no_{ 8 };
        std::map<int, bool> q_pin_map_;

		/*
		Initializer for Constructors; reduce redundancy
		*/
        void Initialize();

		/*
		Method to check whether a pin number matches the required pin range of q74hc595

		@param pin_no: pin_no to be checked
		@returns true if 0 <= pin_no < max_q_pin_no_ else false
		*/
		bool ValidQPin(int pin_no) const;

		/*
		Method to write to the q74hc595 q_pins with values stored in the q_pin_map_

		*/
        void WriteToQPins();

	public:
		/*
		Constructor for creating a Q74HC595
		
		@param ds_pin: Pin number of the ds
		@param stcp_pin: Pin number of the stcp
		@param shcp_pin: Pin number of the shcp
		*/
		Q74HC595(int ds_pin, int stcp_pin, int shcp_pin);

		/*
		Constructor for creating a Q74HC595
		
		@param ds_pin: Pin number of the ds
		@param stcp_pin: Pin number of the stcp
		@param shcp_pin: Pin number of the shcp
		*/
		/*Q74HC595(int&& ds_pin, int&& stcp_pin, int&& shcp_pin);*/

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
        void SetQPinOutput(int pin, bool turn_on);

		/*
		Method to set a q_pin on or off
		Wrong input throws an error

		@param pins: map of Q_Pins to be turned on/off according to the set bools in the map
		*/
        void SetQPinOutput(const std::map<int, bool>& pins);

		/*
		Method to get the status of a q_pin
		Wrong input throws an error

		@param pin: Q_Pin for whcih status is to be returned
		@returns true if pin is on, else false
		*/
        bool GetQPinOutput(int pin);

		/*
		Method to turn off all Q_Pins
		*/
        void TurnOn();

		/*
		Method to turn off all Q_Pins
		*/
        void TurnOff();

		/*
		Method to get the DS pin number
		@returns the used ds pin
		*/
		int GetDsPin() const;

		/*
		Method to get the STCP pin number
		@returns the used stcp pin
		*/
		int GetStcpPin() const;

		/*
		Method to get the SHCP pin number
		@returns the used shcp pin
		*/
		int GetShcpPin() const;

		/*
		Method to get the max count of q pins for this component
		*/
        int GetMaxQPinCount() const;
	};
}
#endif
