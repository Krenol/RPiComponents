#include "motor.hpp"
#include <atomic>

#ifndef RPICOMPONENTS_SERVOMOTOR_H
#define RPICOMPONENTS_SERVOMOTOR_H

namespace rpicomponents {
	constexpr const char* COMPONENT_SERVOMOTOR = "servomotor";
	constexpr int DEFAULT_SERVO_PWM_VALUE = 200;

	struct ServomotorData {
		ServomotorData(int pin, int maxAngle = 180, int minPulseDuration = 5, int maxPulseDuration = 25, int pulseOffset = 3, int pwmVal = DEFAULT_SERVO_PWM_VALUE) :
			pin{ pin }, maxAngle{ maxAngle }, minPulseDuration{ minPulseDuration }, maxPulseDuration{ maxPulseDuration }, pulseOffset{ pulseOffset }, pwmVal{ pwmVal }
		{

		}

		ServomotorData(const ServomotorData& data) : 
			pin{ data.pin }, maxAngle{ data.maxAngle }, minPulseDuration{ data.minPulseDuration }, maxPulseDuration{ data.maxPulseDuration }, pulseOffset{ data.pulseOffset }, 
			pwmVal{ data.pwmVal }
		{

		}

		const int pin, maxAngle, minPulseDuration, maxPulseDuration, pulseOffset, pwmVal{ DEFAULT_SERVO_PWM_VALUE };
	};

	class Servomotor : public Motor {
	private:
		const ServomotorData servoData_;
		std::atomic_int angle_{ 0 };
		const std::shared_ptr<pin::Pin> pin_;

		/*
		Method to init component
		*/
		void Initialize();

		int GetTurnTime(int angle) const;

	public:
		/*
		Constructor for this component

		@param pin The used pin of the servo
		@param maxAngle The maximum angle the servo can reach
		@param minPulseDuration The minimum pulse duration of the servo in ms
		@param maxPulseDuration The maximum pulse duration of the servo in ms
		@param pulseOffset The pulse offset before motor is turned in ms
		@param pwmVal The SoftPWM value of the GPIO; should be left at DEFAULT_SERVO_PWM_VALUE!
		*/
		Servomotor(int pin, int maxAngle = 180, int minPulseDuration = 5, int maxPulseDuration = 25, int pulseOffset = 3, int pwmVal = DEFAULT_SERVO_PWM_VALUE);

		/*
		Constructor for this component
		@param data The ServomotorData struct containing all information for the servo
		*/
		Servomotor(const ServomotorData& data);

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
	};
}

#endif
