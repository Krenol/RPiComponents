#include "motor.hpp"
#include "l293d.hpp"
#include <nlohmann/json.hpp>

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

		int enablePin, inCW, inCCW;
	};

	void to_json(nlohmann::json& j, const BidirectionalmotorData& d) {
        j = nlohmann::json{{"enablePin", d.enablePin}, {"inCW", d.inCW}, {"inCCW", d.inCCW}};
    }

    void from_json(const nlohmann::json& j, BidirectionalmotorData& d) {
        j.at("enablePin").get_to(d.enablePin);
        j.at("inCW").get_to(d.inCW);
        j.at("inCCW").get_to(d.inCCW);
    }

	class Bidirectionalmotor : public Motor
	{
	private:
        const std::shared_ptr<L293D> l293d_;
		const BidirectionalmotorData usedPins_;
		
		/*
		Method to initialize the component
		*/
		void Initialize();

	public:
		/*
		Constructor for this component

        @param l293d The l293d used for this component
		@param enablePin The enable pin of the L293D that is connected to the motor
		@param inPinCW The in pin of the L293D that lets the motor turn clockwise
		@param inPinCCW The in pin of the L293D that lets the motor turn counter clockwise
		*/
        Bidirectionalmotor(std::shared_ptr<L293D> l293d, int enablePin, int inPinCW, int inPinCCW);

		/*
		Constructor for this component

        @param l293d The l293d used for this component
		@param usedL293DPins A BidirectionalmotorData containing the used L293D pins
		*/
        Bidirectionalmotor(std::shared_ptr<L293D>, const BidirectionalmotorData& usedL293DPins);

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
		Method that returns the used L293D pins of the motor
		@returns the used L293D pins as BidirectionalmotorData struct
		*/
		const BidirectionalmotorData& GetUsedL293DPins() const;

        /*
         Method to get the used L293D
         @returns reference to used L293D
        */
        const std::shared_ptr<L293D>& GetL293D() const;
	};
}
#endif
