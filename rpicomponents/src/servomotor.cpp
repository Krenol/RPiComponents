#include "servomotor.hpp"

void rpicomponents::Servomotor::Initialize()
{
	Stop();
	AddPin(servoData_.pin);
}

int rpicomponents::Servomotor::GetTurnTime(int angle) const
{
	if (angle < 0) throw std::invalid_argument("angle cannot be negative!");
	if (angle > servoData_.maxAngle) throw std::invalid_argument("angle cannot be greater than the servo maxAngle!");

	auto val = servoData_.minPulseDuration + servoData_.pulseOffset +
		(servoData_.maxPulseDuration - servoData_.minPulseDuration) * angle / servoData_.maxAngle;
	return val;
}

rpicomponents::Servomotor::Servomotor(int pin, int maxAngle, int minPulseDuration, int maxPulseDuration, int pulseOffset, int pwmVal) : Motor(COMPONENT_SERVOMOTOR),
	servoData_{ ServomotorData (pin, maxAngle, minPulseDuration, maxPulseDuration, pulseOffset, pwmVal)},
	pin_{ pin::PinCreator::CreatePin(servoData_.pin, pin::SOFTPWM_MODE, servoData_.pwmVal)}
{
	Initialize();
}

rpicomponents::Servomotor::Servomotor(const ServomotorData& data) : Motor(COMPONENT_SERVOMOTOR), servoData_{ data }, 
pin_{ pin::PinCreator::CreatePin(servoData_.pin, pin::SOFTPWM_MODE, , servoData_.pwmVal) }
{
	Initialize();
}

rpicomponents::Servomotor::Servomotor(const Servomotor& motor) : Servomotor(motor.GetServoData())
{
}

const rpicomponents::ServomotorData& rpicomponents::Servomotor::GetServoData() const
{
	return servoData_;
}

int rpicomponents::Servomotor::GetServoAngle() const
{
	auto angle = angle_.load()
	return angle;
}

void rpicomponents::Servomotor::Rotate(int angle)
{
	auto time = GetTurnTime(angle);
	pin_->Output(time);
	angle_.store(angle);
	utils::Waiter::SleepMillis(50);
}

void rpicomponents::Servomotor::Stop() const
{
	Rotate(0);
}
