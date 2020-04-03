#include "component.hpp"
#include <map>

#ifndef RPICOMPONENTS_Q74HC595_H
#define RPICOMPONENTS_Q74HC595_H

namespace rpicomponents {

	constexpr const char* COMPONENT_Q74HC595 = "q74hc595";
	constexpr const int COMPONENT_Q74HC595_MAX_Q_PINS = 8;
	typedef std::map<int, bool> QPinMap;

	class Q74HC595 : public Component
	{
	private:
		const std::shared_ptr<pin::Pin> ds_, stcp_, shcp_;
        std::map<int, bool> q_pin_map_;
		static const int out_sleep_{ 1 }; //ms

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
		
		@param ds_pin: Pin of the ds
		@param stcp_pin: Pin of the stcp
		@param shcp_pin: Pin of the shcp
		*/
		Q74HC595(std::shared_ptr<pin::Pin> ds_pin, std::shared_ptr<pin::Pin> stcp_pin, std::shared_ptr<pin::Pin> shcp_pin);

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

		@param pins: QPinMap to turn on/off according to the set bools in the map
		*/
        void SetQPinOutput(const QPinMap& pins);

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
		const std::shared_ptr<pin::Pin>& GetDsPin() const;

		/*
		Method to get the STCP pin number
		@returns the used stcp pin
		*/
		const std::shared_ptr<pin::Pin>& GetStcpPin() const;

		/*
		Method to get the SHCP pin number
		@returns the used shcp pin
		*/
		const std::shared_ptr<pin::Pin>& GetShcpPin() const;
	};
}
#endif
