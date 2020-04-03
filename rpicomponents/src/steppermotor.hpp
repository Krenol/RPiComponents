#include "motor.hpp"
#include <atomic>

#ifndef RPICOMPONENTS_STEPPERMOTOR_H
#define RPICOMPONENTS_STEPPERMOTOR_H

namespace rpicomponents {
	constexpr const char* COMPONENT_STEPPERMOTOR = "steppermotor";
	typedef std::map<int, std::shared_ptr<pin::Pin>> StepperPinMap;

	class Steppermotor : public Motor {
	private:
		const std::vector<int> stepVector_ { 0x01,0x02,0x04,0x08 }, motorPins_;
        const StepperPinMap pins_;
		const int steps_;
        std::atomic_int currentCoil_; //current coil position of the stepper; can have a offset as it starts with 0 and motor could be e.g. at coil 3.

        void Initialize();

	public:
		/*
		Constructor for this component

		@param pin1 The first pin of the stepper motor
		@param pin2 The second pin of the stepper motor
		@param pin3 The third pin of the stepper motor
		@param pin4 The fourth pin of the stepper motor
		@param steps The amount of steps the motor has
		*/
		Steppermotor(std::shared_ptr<pin::Pin> pin1, std::shared_ptr<pin::Pin> pin2, std::shared_ptr<pin::Pin> pin3, std::shared_ptr<pin::Pin> pin4, int steps = 2048);

		/*
		Constructor for this component

		@param pins StepperPinMap holding the four pins of the stepper motor
		@param steps The amount of steps the motor has
		*/
		Steppermotor(const StepperPinMap &pins, int steps = 2048);

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

		@returns the used motor pins in a StepperPinMap
		*/
		const StepperPinMap& GetMotorPins() const;
	};
}

#endif // RPICOMPONENTS_STEPPERMOTOR_H
