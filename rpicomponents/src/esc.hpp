#include "component.hpp"
#include <atomic>
#include <nlohmann/json.hpp>

#ifndef RPICOMPONENTS_ESC_H
#define RPICOMPONENTS_ESC_H

namespace rpicomponents {
	constexpr const char* COMPONENT_ESC = "esc";
    constexpr const int ESC_MAX_VALUE = 2000, ESC_MIN_VALUE = 700, ESC_ARM_SLEEP_TIME_MS = 100;

	struct EscData {
        EscData(int esc_min_value = ESC_MIN_VALUE, int esc_max_value = ESC_MAX_VALUE) :
            esc_min_value{ esc_min_value }, esc_max_value{ esc_max_value }
		{

		}

		EscData(const EscData& data) :
            esc_min_value{ data.esc_min_value }, esc_max_value{ data.esc_max_value }
		{

		}

        int esc_min_value, esc_max_value;
	};

	void to_json(nlohmann::json& j, const EscData& d) {
        j = nlohmann::json{{"esc_min_value", d.esc_min_value}, {"esc_max_value", d.esc_max_value}};
    }

    void from_json(const nlohmann::json& j, EscData& d) {
        j.at("esc_max_value").get_to(d.esc_max_value);
        j.at("esc_min_value").get_to(d.esc_min_value);
    }

	class Esc : public Component {
	private:
        const EscData escData_;
		const std::shared_ptr<pin::Pin> pin_;

		/*
		Initializer for Constructors; reduce redundancy
		*/
		void Initialize(); 

        /*
         method to arm the ESC
        */
        void Arm() const;

	public:
		/*
		Constructor for ESC
		@param pin: The pin of the ESC
		@param esc_min_value: The min pulse width value of the ESC at which it works; find right value via Calibrate()
		@param esc_max_value: The max pulse width value of the ESC at which it works; find right value via Calibrate(); defines the max softpwm ouput of the pin
		*/
		Esc(std::shared_ptr<pin::Pin> pin, int esc_min_value = ESC_MIN_VALUE, int esc_max_value = ESC_MAX_VALUE);

		/*
		Constructor for ESC
        @param escData: The EscData struct
		*/
        Esc(std::shared_ptr<pin::Pin> pin, const EscData& escData);

		/*
		The copy constructor of the ESC
		@param esc: The ESC to be copied
		*/
		Esc(const Esc& esc);

		/*
		Method to set the output speed of the ESC according to esc_min_value <= speed <= esc_max_value
		*/
        void SetOutputSpeed(int speed) const;

		/*
		Method to get the currently set ESC speed
		@returns the current ESC speed between esc_min_value <= speed <= esc_max_value or 0 for off
		*/
		int GetEscSpeed() const;

		/*
		Method to turn off ESC output
		*/
        void TurnOff() const;

		/*
		Method to get the ESC data
		@returns EscData struct containing all ESC information
		*/
        const EscData& GetEscData() const;

		/*
		Method to load the used pin of the ESC

		@returns reference to used pin as shared_ptr
		*/
		const std::shared_ptr<pin::Pin>& GetPin() const;
	};
}

#endif
