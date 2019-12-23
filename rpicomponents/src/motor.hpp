#include "component.hpp"
#include "l293d.hpp"

#ifndef RPICOMPONENTS_MOTOR_H
#define RPICOMPONENTS_MOTOR_H

namespace rpicomponents {
    constexpr const char* COMPONENT_MOTOR = "motor";

	class Motor : public Component {
	protected:
        const std::unique_ptr<L293D> l293d_;

		/*
		Method to check if the passed pin is an enable pin of the L293D
		@param pin: The pin to be checked
		@returns true if enablePin 1 or 2 of L293D else false
		*/
		bool ValidEnablePin(int pin) const;

		/*
		Method to check if passed pin is a valid inPin of the L293D
		@param pin: The pin to be checked
		@returns true if given pin is part of the L293D inPins else false
		*/
		bool ValidInPin(int pin) const;

		virtual ~Motor() = 0; //virtual protected destructor to make class abstract

		/*
		Constructor for this component

		@param enable_pins The EnablePinStruct struct containing all necessary enable pin information for the l293d
		@param enable_pin2 The InPinStruct struct containing all necessary in pin information for the l293d
		*/
		Motor(const EnablePinStruct& enable_pins, const InPinStruct& in_pins);

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
		Motor(int enable_pin1, int enable_pin2, rpicomponents::pin::PIN_MODE enable_pin1_mode = rpicomponents::pin::SOFTPWM_MODE,
			rpicomponents::pin::PIN_MODE enable_pin2_mode = rpicomponents::pin::SOFTPWM_MODE, int max_output_enable_pin1 = 254, int max_output_enable_pin2 = 254,
			int in_pin1 = -1, int in_pin2 = -1, int in_pin3 = -1, int in_pin4 = -1);

	public:
		/*
		Method to let the motor rotate at full pace (motor dependent)
		*/
		virtual void Rotate() const = 0;

		/*
		Method to let the motor rotate with given speed (motor dependent)
		@param speed: The speed with which the motor should rotate
		*/
		virtual void Rotate(int speed) const = 0;

		/*
		Method to stop the motor
		*/
		virtual void Stop() const = 0;

		/*
		Method to get the enable pin parameters of the used l293d

		@returns a EnablePinStruct containing the parameters of enable pin 1 and 2
		*/
        const EnablePinStruct& GetEnablePins() const;

		/*
		Method to get the in pin parameters of the used l293d

		@returns a InPinStruct containing the parameters of input pin 1, 2, 3 and 4
		*/
        const InPinStruct& GetInPins() const;
	};
}

#endif // RPICOMPONENTS_MOTOR_H
