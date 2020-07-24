#include "servomotor.hpp"
#include <iostream>
#include "utils/utils.hpp"

void rpicomponents::Servomotor::Initialize()
{
	Stop();
	if (pin_->OutputMode() != pin::SOFTPWM_MODE && pin_->OutputMode() != pin::PWM_MODE) {
		throw new std::invalid_argument("servo motor needs a pwm or softpwm pin!");
	}
	if (pin_->GetMaxOutValue() != COMPONENT_SERVOMOTOR_DEFAULT_PWM_VALUE) {
		std::cout << "-------------------------------------" << std::endl;
		std::cout << "WARNING: Servomotor pin max output value should be set to " << std::to_string(COMPONENT_SERVOMOTOR_DEFAULT_PWM_VALUE) << "!" << std::endl;
		std::cout << "-------------------------------------" << std::endl;
	}

	AddPin(pin_->GetPin());
}

int rpicomponents::Servomotor::GetTurnTime(int angle) const
{
	if (angle < 0) throw std::invalid_argument("angle cannot be negative!");
	if (angle > servoData_.maxAngle) throw std::invalid_argument("angle cannot be greater than the servo maxAngle!");

	auto val = servoData_.minPulseDuration + servoData_.pulseOffset +
		(servoData_.maxPulseDuration - servoData_.minPulseDuration) * angle / servoData_.maxAngle;
	return val;
}

rpicomponents::Servomotor::Servomotor(std::unique_ptr<pin::Pin> pin, int maxAngle, int minPulseDuration, int maxPulseDuration, int pulseOffset) : 
	Motor(COMPONENT_SERVOMOTOR),
	servoData_{ ServomotorData (maxAngle, minPulseDuration, maxPulseDuration, pulseOffset)}, 
	pin_{ pin }
{
	Initialize();
}

rpicomponents::Servomotor::Servomotor(std::unique_ptr<pin::Pin> pin, const ServomotorData& data) : 
	Motor(COMPONENT_SERVOMOTOR), servoData_{ data }, pin_{ pin }
{
	Initialize();
}

rpicomponents::Servomotor::Servomotor(const Servomotor& motor) : Servomotor(motor.GetPin(), motor.GetServoData())
{
}

const rpicomponents::ServomotorData& rpicomponents::Servomotor::GetServoData() const
{
	return servoData_;
}

int rpicomponents::Servomotor::GetServoAngle() const
{
    auto angle = angle_.load();
	return angle;
}

void rpicomponents::Servomotor::Rotate(int angle)
{
	auto time = GetTurnTime(angle);
	pin_->Output(time);
	angle_.store(angle);
	utils::Waiter::SleepMillis(50);
}

void rpicomponents::Servomotor::Stop()
{
    Rotate(0);
}

const std::unique_ptr<pin::Pin>& rpicomponents::Servomotor::GetPin() const {
	return pin_;
}
