#include "motor.hpp"
#include "l293d.hpp"

#ifndef RPICOMPONENTS_UNDIRECTIONALMOTOR_H
#define RPICOMPONENTS_UNDIRECTIONALMOTOR_H

namespace rpicomponents {
	constexpr const char* COMPONENT_UNDIRECTIONALMOTOR = "undirectionalmotor";

	struct UndirectionalmotorData {
		UndirectionalmotorData(int enablePin, int inPin) :
			enablePin{ enablePin }, inPin{ inPin }
		{

		}

		UndirectionalmotorData(const UndirectionalmotorData& data) :
			enablePin{ data.enablePin }, inPin{ data.inPin }
		{

		}

		const int enablePin, inPin;
	};

	class Undirectionalmotor : public Motor {
	private:
		const std::unique_ptr<L293D> l293d_;
		const UndirectionalmotorData usedPins_;

		/*
		Method to initialize the component
		*/
		void Initialize();

	public:
		/*
		Constructor for this component

		@param enable_pins The EnablePinStruct struct containing all necessary enable pin information for the l293d
		@param in_pins The InPinStruct struct containing all necessary in pin information for the l293d
		@param enablePin The enable pin of the L293D that is connected to the motor
		@param inPin The in pin of the L293D that lets the motor turn
		*/
		Undirectionalmotor(const EnablePinStruct& enable_pins, const InPinStruct& in_pins, int enablePin, int inPin);

		/*
		Constructor for this component

		@param enable_pins The EnablePinStruct struct containing all necessary enable pin information for the l293d
		@param in_pins The InPinStruct struct containing all necessary in pin information for the l293d
		@param usedL293DPins A UndirectionalmotorData containing the used L293D pins
		*/
		Undirectionalmotor(const EnablePinStruct& enable_pins, const InPinStruct& in_pins, const UndirectionalmotorData& usedL293DPins);

		/*
		Constructor for this component
		@param motor: The motor to be copied
		*/
		Undirectionalmotor(const Undirectionalmotor& motor);

		/*
		Method to let the motor rotate with given speed (motor dependent)
		@param speed: The rotation speed according to the range 0 <= speed < max output value of the enable pin struct
		*/
		void Rotate(int speed);

		/*
		Method to stop the motor
		*/
		void Stop() const;

		/*
		Method to get the enable pins of the l293d
		@returns a EnablePinStruct containing all enable pin information of the l293d
		*/
		const EnablePinStruct& GetL293DEnablePins() const;

		/*
		Method to get the in pins of the l293d
		@returns a EnablePinStruct containing all in pin information of the l293d
		*/
		const InPinStruct& GetL293DInPins() const;

		/*
		Method that returns the used L293D pins of the motor
		@returns the used L293D pins as UndirectionalmotorData struct
		*/
		const UndirectionalmotorData& GetUsedL293DPins() const;
	};
}

#endif