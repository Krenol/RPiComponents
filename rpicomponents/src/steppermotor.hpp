#include "motor.hpp"
#include <atomic>

#ifndef RPICOMPONENTS_STEPPERMOTOR_H
#define RPICOMPONENTS_STEPPERMOTOR_H

namespace rpicomponents {
	constexpr const char* COMPONENT_STEPPERMOTOR = "steppermotor";

	class Steppermotor : public Motor {
	private:
		const std::vector<int> stepVector_ { 0x01,0x02,0x04,0x08 };
		const int steps_{ 2048 };
		std::atomic_int currentCoil_{ 0 }; //current coil position of the stepper; can have a offset as it starts with 0 and motor could be e.g. at coil 3. 

	public:
		/*
		Constructor for this component

		@param enable_pins The EnablePinStruct struct containing all necessary enable pin information for the l293d
		@param enable_pin2 The InPinStruct struct containing all necessary in pin information for the l293d
		*/
		Steppermotor(const EnablePinStruct& enable_pins, const InPinStruct& in_pins, int steps = 2048);

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
			int in_pin1 = -1, int in_pin2 = -1, int in_pin3 = -1, int in_pin4 = -1, int steps = 2048);

		/*
		Method to let the motor rotate with given speed (motor dependent)
		@param steps: The steps to be rotated
		@param cw: Set to true if motor should step clockwise, else false
		@param stepDelay: The waiting time between each step in ms
		*/
		void Rotate(int steps, bool cw = true, long stepDelay = 3) const;

		/*
		Method to stop the motor
		*/
		void Stop() const;
	};
}

#endif // RPICOMPONENTS_STEPPERMOTOR_H
