#include "motor.hpp"
#include "l293d.hpp"

#ifndef RPICOMPONENTS_BIDIRECTIONALMOTOR_H
#define RPICOMPONENTS_BIDIRECTIONALMOTOR_H

namespace rpicomponents {
	constexpr const char* COMPONENT_BIDIRECTIONALMOTOR = "bidirectionalmotor";

	struct BidirectionalmotorData {
		BidirectionalmotorData(int enablePin, int inPinCW, int inPinCCW) : 
			enablePin{ enablePin }, inCW{ inPinCW }, inCCW{ inPinCCW }
		{

		}

		BidirectionalmotorData(const BidirectionalmotorData& data) :
			enablePin{ data.enablePin }, inCW{ data.inCW }, inCCW{ data.inCCW }
		{

		}

		const int enablePin, inCW, inCCW;
	};

	class Bidirectionalmotor : public Motor
	{
	private:
		const std::unique_ptr<L293D> l293d_;
		const BidirectionalmotorData usedPins_;
		
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
		@param inPinCW The in pin of the L293D that lets the motor turn clockwise
		@param inPinCCW The in pin of the L293D that lets the motor turn counter clockwise
		*/
		Bidirectionalmotor(const EnablePinStruct& enable_pins, const InPinStruct& in_pins, int enablePin, int inPinCW, int inPinCCW);

		/*
		Constructor for this component

		@param enable_pins The EnablePinStruct struct containing all necessary enable pin information for the l293d
		@param in_pins The InPinStruct struct containing all necessary in pin information for the l293d
		@param usedL293DPins A BidirectionalmotorData containing the used L293D pins
		*/
		Bidirectionalmotor(const EnablePinStruct& enable_pins, const InPinStruct& in_pins, const BidirectionalmotorData& usedL293DPins);

		/*
		Constructor for this component
		@param motor: The motor to be copied
		*/
		Bidirectionalmotor(const Bidirectionalmotor& motor);

		/*
		Method to let the motor rotate with given speed (motor dependent)
		@param speed: The rotation speed according to the range 0 <= speed < max output value of the enable pin struct
		@param cw: Set to true if motor should step clockwise, else false
		*/
		void Rotate(int speed, bool cw = true);

		/*
		Method to stop the motor
		*/
        void Stop();

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
		@returns the used L293D pins as BidirectionalmotorData struct
		*/
		const BidirectionalmotorData& GetUsedL293DPins() const;
	};
}
#endif
