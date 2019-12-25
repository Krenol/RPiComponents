#include "motor.hpp"
#include <atomic>

#ifndef RPICOMPONENTS_STEPPERMOTOR_H
#define RPICOMPONENTS_STEPPERMOTOR_H

namespace rpicomponents {
	constexpr const char* COMPONENT_STEPPERMOTOR = "steppermotor";

	class Steppermotor : public Motor {
	private:
		const std::vector<int> stepVector_ { 0x01,0x02,0x04,0x08 }, motorPins_;
        const std::vector<std::unique_ptr<pin::Pin>> pins_;
		const int steps_{ 2048 };
        std::atomic_int currentCoil_{ 0 }; //current coil position of the stepper; can have a offset as it starts with 0 and motor could be e.g. at coil 3.

        std::vector<std::unique_ptr<pin::Pin>> CreatePinVector(const std::vector<int>& pins) const;

	public:
		/*
		Constructor for this component

		@param pin1 The first pin of the stepper motor
		@param pin2 The second pin of the stepper motor
		@param pin3 The third pin of the stepper motor
		@param pin4 The fourth pin of the stepper motor
		@param steps The amount of steps the motor has
		*/
		Steppermotor(int pin1, int pin2, int pin3, int pin4, int steps = 2048);

		/*
		Constructor for this component

		@param pins Vector holding the four GPIO pins of the stepper motor
		@param steps The amount of steps the motor has
		*/
		Steppermotor(const std::vector<int> &pins, int steps = 2048);

		/*
		Copy constructor
		@param motor The motor to be copied
		*/
		Steppermotor(const Steppermotor& motor);

		/*
		Method to let the motor rotate with given speed (motor dependent)
		@param steps: The steps to be rotated
		@param cw: Set to true if motor should step clockwise, else false
		@param stepDelay: The waiting time between each step in ms
		*/
        void Rotate(int steps, bool cw = true, long stepDelay = 3);

		/*
		Method to stop the motor
		*/
        void Stop();

		/*
		Method to get the amount of steps of the motor

		@returns the step count of the motor
		*/
		int GetMotorSteps() const;

		/*
		Method to get the used motor pins of the stepper motor

		@returns the used motor pins in a vector
		*/
		const std::vector<int> GetMotorPins() const;
	};
}

#endif // RPICOMPONENTS_STEPPERMOTOR_H
