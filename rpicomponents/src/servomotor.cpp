#include "servomotor.hpp"
#include <iostream>
#include <unistd.h>

void rpicomponents::Servomotor::Initialize()
{
	Stop();
	auto mode = pin_->OutputMode();
	if (mode != pin::PWM_MODE && mode != pin::PULSE_MODE) {
		throw new std::invalid_argument("servo motor needs a pwm or pulse pin!");
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

rpicomponents::Servomotor::Servomotor(int pin, pin::PIN_MODE pin_mode, int pin_max_value, int maxAngle, int minPulseDuration, int maxPulseDuration, int pulseOffset) : 
	Motor(COMPONENT_SERVOMOTOR),
	servoData_{ ServomotorData (maxAngle, minPulseDuration, maxPulseDuration, pulseOffset)}
{
	pin_ = pin::PinCreator::CreatePin(pin, pin_mode, pin_max_value);
	Initialize();
}

rpicomponents::Servomotor::Servomotor(const ServomotorData& data, int pin, pin::PIN_MODE pin_mode, int pin_max_value) : 
	Motor(COMPONENT_SERVOMOTOR), servoData_{ data }
{
	pin_ = pin::PinCreator::CreatePin(pin, pin_mode, pin_max_value);
	Initialize();
}


rpicomponents::Servomotor::Servomotor(pin::pin_data pindata, const ServomotorData& data) : Motor(COMPONENT_SERVOMOTOR), servoData_{ data } 
{
	pin_ = pin::PinCreator::CreatePin(pindata);
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
	usleep(50);
}

void rpicomponents::Servomotor::Stop()
{
    Rotate(0);
}

int rpicomponents::Servomotor::GetPin() const {
	return pin_->GetPin();
}

pin::PIN_MODE rpicomponents::Servomotor::GetPinMode() const
{
	return pin_->OutputMode();
}

int rpicomponents::Servomotor::GetMaxOutValue() const {
	return pin_->GetMaxOutValue();
}