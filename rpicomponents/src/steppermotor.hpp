#include "motor.hpp"

#ifndef RPICOMPONENTS_STEPPERMOTOR_H
#define RPICOMPONENTS_STEPPERMOTOR_H

namespace rpicomponents {
	constexpr const char* COMPONENT_STEPPERMOTOR = "steppermotor";

	class Steppermotor : public Motor {
	protected:
		

	public:
		/*
		Constructor for this component

		@param enable_pins The EnablePinStruct struct containing all necessary enable pin information for the l293d
		@param enable_pin2 The InPinStruct struct containing all necessary in pin information for the l293d
		*/
		Steppermotor(const EnablePinStruct& enable_pins, const InPinStruct& in_pins);

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
		Steppermotor(int enable_pin1, int enable_pin2, rpicomponents::pin::PIN_MODE enable_pin1_mode = rpicomponents::pin::SOFTPWM_MODE,
			rpicomponents::pin::PIN_MODE enable_pin2_mode = rpicomponents::pin::SOFTPWM_MODE, int max_output_enable_pin1 = 254, int max_output_enable_pin2 = 254,
			int in_pin1 = -1, int in_pin2 = -1, int in_pin3 = -1, int in_pin4 = -1);

		/*
		Method to let the motor rotate with given speed (motor dependent)
		@param steps: The steps to be rotated; if set to -1 motor will step continiously 
		@param cw: Set to true if motor should step clockwise, else false
		@param speed: The waiting time between each step in ms
		*/
		void Rotate(int steps, bool cw = true, long speed = 3) const;

		/*
		Method to stop the motor
		*/
		void Stop() const;
	};
}

#endif // RPICOMPONENTS_STEPPERMOTOR_H
