#include "component.hpp"
#include <map>

#ifndef RPICOMPONENTS_Q74HC595_H
#define RPICOMPONENTS_Q74HC595_H

namespace rpicomponents {

	struct Q_Pin {
		const int pin_no{ 0 };
		bool turn_on{ false };
	};

	constexpr const char* COMPONENT_Q74HC595 = "q74hc595";

	class Q74HC595 : public Component
	{
	private:
		const std::unique_ptr<pin::Pin> ds_, stcp_, shcp_;
		const int max_q_pin_no_{ 8 };
		mutable std::map<int, Q_Pin> q_pin_map_;

		/*
		Initializer for Constructors; reduce redundancy
		*/
		void Initialize() const;

		/*
		Method to check whether a q_pin matches the required pin range of q74hc595
		
		@param q_pin: Q_Pin to be checked
		@returns true if 0 <= Q_Pin.pin_no < max_q_pin_no_ else false
		*/
		bool ValidQPin(Q_Pin q_pin) const;

		/*
		Method to get a Q_Pin from the q_pin_map_
		
		@param pin_no: q pin number to be retrieved
		@returns The Q_Pin from the map or throws an error for invalid input
		*/
		Q_Pin GetQPin(const int& pin_no);

		/*
		Method to set a Q_Pin of the q_pin_map_
		throws an error for wrong pin_no outside range 0 <= pin_no < max_q_pin_no_
		
		@param pin_no: q pin number to be retrieved
		@param is_on: bool whether Q_Pin is on or off
		*/
		void SetQPin(const int& pin_no, bool is_on);

		/*
		Method to turn on/off a Q_Pin
		throws an error for wrong Q_Pin.pin_no outside range 0 <= pin_no < max_q_pin_no_
		
		@param q_pin: Q_Pin to be tunred on/off
		*/
		void WriteToQPin(const Q_Pin& q_pin);

		/*
		Method to write to the q74hc595
		In order to create output all max_q_pin_no_ pins must be written to
		If q_values size > max_q_pin_no_ an error is thrown
		If q_values size < max_q_pin_no_ missing values will be filled values of q_pin_map_
		If ininvalid Q_Pin is passed an error is thrown
		

		@param pin: Pointer to the pin of the button
		@returns true if 0 <= Q_Pin.pin_no < max_q_pin_no_ else false
		*/
		void WriteToPins(const std::vector<Q_Pin>& q_values) const;

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
		Method to create a valid Q_Pin
		
		@param pin_no: Q_Pin in number in range 0 <= pin_no < max_q_pin_no_
		@param turn_on: bool if pin is to be turned on or off
		@returns a valid Q_Pin if input was correct else throws an error
		*/
		Q_Pin CreateQPin(const int& pin_no, bool turn_on);

		/*
		Method to set a vector of Q_Pins on or off
		Wrong Q_Pins throw an error
		
		
		@param q_values: Vector of Q_Pins to be turned on/off according to boolean turn_on
		*/
		void SetQPinOutput(const std::vector<Q_Pin>& q_values) const;

		/*
		Method to set a vector of Q_Pins on or off
		Wrong input throws an error
		
		
		@param q_pin: Q_Pin to be turned on/off according to boolean turn_on
		*/
		void SetQPinOutput(const Q_Pin& q_pin) const;

		/*
		Method to turn off all Q_Pins
		
		*/
		void TurnOn() const;

		/*
		Method to turn off all Q_Pins
		
		*/
		void TurnOff() const;
	};
}
#endif
