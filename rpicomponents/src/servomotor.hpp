#include "motor.hpp"
#include <atomic>

#ifndef RPICOMPONENTS_SERVOMOTOR_H
#define RPICOMPONENTS_SERVOMOTOR_H

namespace rpicomponents {
	constexpr const char* COMPONENT_SERVOMOTOR = "servomotor";
	constexpr int COMPONENT_SERVOMOTOR_DEFAULT_PWM_VALUE = 200;

	struct ServomotorData {
		ServomotorData(int pin, int maxAngle = 180, int minPulseDuration = 5, int maxPulseDuration = 25, int pulseOffset = 3) :
			maxAngle{ maxAngle }, minPulseDuration{ minPulseDuration }, maxPulseDuration{ maxPulseDuration }, pulseOffset{ pulseOffset }
		{

		}

		ServomotorData(const ServomotorData& data) : 
			maxAngle{ data.maxAngle }, minPulseDuration{ data.minPulseDuration }, maxPulseDuration{ data.maxPulseDuration }, pulseOffset{ data.pulseOffset }
		{

		}

		const int maxAngle, minPulseDuration, maxPulseDuration, pulseOffset;
	};

	class Servomotor : public Motor {
	private:
		const ServomotorData servoData_;
		std::atomic_int angle_{ 0 };
		std::unique_ptr<pin::Pin> pin_;

		/*
		Method to init component
		*/
		void Initialize();

		int GetTurnTime(int angle) const;

	public:
		/*
		Constructor for this component

		@param pin The used pin of the servo
		@param pin_mode The pin mode
		@param pin_max_value The max value of the pin
		@param maxAngle The maximum angle the servo can reach
		@param minPulseDuration The minimum pulse duration of the servo in ms
		@param maxPulseDuration The maximum pulse duration of the servo in ms
		@param pulseOffset The pulse offset before motor is turned in ms
		*/
		Servomotor(int pin, pin::PIN_MODE pin_mode = pin::PULSE_MODE, int pin_max_value = COMPONENT_SERVOMOTOR_DEFAULT_PWM_VALUE, int maxAngle = 180, int minPulseDuration = 5, int maxPulseDuration = 25, int pulseOffset = 3);

		/*
		Constructor for this component
		@param pin The used pin of the servo
		@param pin_mode The pin mode
		@param pin_max_value The max value of the pin
		@param data The ServomotorData struct containing all information for the servo
		*/
		Servomotor(const ServomotorData& data, int pin, pin::PIN_MODE pin_mode = pin::PULSE_MODE, int pin_max_value = COMPONENT_SERVOMOTOR_DEFAULT_PWM_VALUE);

		/*
		Constructor for this component
		@param pindata: The pin_data struct of the used pin
		@param data The ServomotorData struct containing all information for the servo
		*/
		Servomotor(pin::pin_data pindata, const ServomotorData& data);

		/*
		Copy constructor
		@param motor The motor to be copied
		*/
		Servomotor(const Servomotor& motor);

		/*
		method to return the servo data as ServomotorData struct
		@returns a ServomotorData struct
		*/
		const ServomotorData& GetServoData() const;

		/*
		Method to get the angle of the servo

		@returns the angle of the servo in degree (between 0 and given maxAngle)
		*/
		int GetServoAngle() const;

		/*
		method to let the servo rotate for a certain angle
		@param angle The angle the servo should rotate
		*/
		void Rotate(int angle);

		/*
		Method to stop the motor and reset it to 0 degree
		*/
        void Stop();

		/*
		Method to get the used pin

		@returns the used pin
		*/
		int GetPin() const;

		/*
		* Method to get the pin mode
		*
		* @returns the pin mode
		*/
		pin::PIN_MODE GetPinMode() const;

		/*
		* Method to get the pin max value
		*
		* @returns the pin max value
		*/
		int GetMaxOutValue() const;
	};
}

#endif
