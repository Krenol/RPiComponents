#include "component.hpp"
#include <atomic>

#ifndef RPICOMPONENTS_ESC_H
#define RPICOMPONENTS_ESC_H

namespace rpicomponents {
	constexpr const char* COMPONENT_ESC = "esc";
	constexpr const int ESC_MAX_VALUE = 2000, ESC_MIN_VALUE = 700;

	struct EscData {
		EscData(int pin, int esc_min_value = ESC_MIN_VALUE, int esc_max_value = ESC_MAX_VALUE, int softpwm_pulse_width = ESC_SOFTPWM_PULSE_WIDTH) :
			pin{ pin }, esc_min_value{ esc_min_value }, esc_max_value{ esc_max_value }, softpwm_pulse_width{ softpwm_pulse_width }
		{

		}

		EscData(const EscData& data) :
			pin{ data.pin }, esc_min_value{ data.esc_min_value }, esc_max_value{ data.esc_max_value }, softpwm_pulse_width{ data.softpwm_pulse_width }
		{

		}

		const int pin;
		int esc_min_value, esc_max_value;
	};

	class Esc : public Component {
	private:
		EscData escData_;
		std::unique_ptr<pin::Pin> pin_;

		/*
		Initializer for Constructors; reduce redundancy
		*/
		void Initialize(); 

	public:
		/*
		Constructor for ESC
		@param pin: The pin of the ESC
		@param esc_min_value: The min pulse width value of the ESC at which it works; find right value via Calibrate()
		@param esc_max_value: The max pulse width value of the ESC at which it works; find right value via Calibrate(); defines the max softpwm ouput of the pin
		*/
		Esc(int pin, int esc_min_value = ESC_MIN_VALUE, int esc_max_value = ESC_MAX_VALUE);

		/*
		Constructor for ESC
		@param pin: The pin of the ESC
		*/
		Esc(const EscData& escData_);

		/*
		The copy constructor of the ESC
		@param esc: The ESC to be copied
		*/
		Esc(const Esc& esc);

		/*
		Method to calibrate the ESC
		Sets the right esc_min_value and esc_max_value of the ESC
		*/
		void Calibrate();

		/*
		Method to set the output speed of the ESC according to esc_min_value <= speed <= esc_max_value
		*/
		void SetOutputSpeed(int speed);

		/*
		Method to get the currently set ESC speed
		@returns the current ESC speed between esc_min_value <= speed <= esc_max_value or 0 for off
		*/
		int GetEscSpeed() const;

		/*
		Method to turn off ESC output
		*/
		void TurnOff();

		/*
		Method to get the ESC data
		@returns EscData struct containing all ESC information
		*/
		const EscData& GetEscData();
	};
}

#endif