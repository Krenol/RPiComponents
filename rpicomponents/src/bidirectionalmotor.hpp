#include "motor.hpp"

#ifndef RPICOMPONENTS_BIDIRECTIONALMOTOR_H
#define RPICOMPONENTS_BIDIRECTIONALMOTOR_H

namespace rpicomponents {
	constexpr const char* COMPONENT_BIDIRECTIONALMOTOR = "bidirectionalmotor";

	class Bidirectionalmotor : public Motor
	{
	private:
		const std::unique_ptr<L293D> l293d_;
		const int enablePin_, inCW_, inCCW_;

	public:
		/*
		Constructor for this component

		@param enable_pins The EnablePinStruct struct containing all necessary enable pin information for the l293d
		@param in_pins The InPinStruct struct containing all necessary in pin information for the l293d
		@param enablePin The enable pin of the L293D that is connected to the motor
		@param inPinCW The in pin of the L293D that lets the motor turn clockwise
		@param inPinCCW The in pin of the L293D that lets the motor turn counter clockwise
		*/
		Bidirectionalmotor(const EnablePinStruct& enable_pins, const InPinStruct& in_pins, int enablePin, int inPinCW, int inPinCCW);

		/*
		Method to let the motor rotate with given speed (motor dependent)
		@param speed: The rotation speed according to the range 0 <= speed < max output value of the enable pin struct
		@param cw: Set to true if motor should step clockwise, else false
		*/
		void Rotate(int speed, bool cw = true);

		/*
		Method to stop the motor
		*/
		void Stop() const;
	};
}
#endif