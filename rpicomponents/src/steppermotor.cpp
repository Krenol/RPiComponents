#include "steppermotor.hpp"

rpicomponents::Steppermotor::Steppermotor(int pin1, int pin2, int pin3, int pin4, int steps) : Motor(COMPONENT_STEPPERMOTOR), steps_{steps},
	motorPins_{ {pin1, pin2, pin3, pin4} }, pins_{ CreatePinVector(motorPins_) }
{
	AddPins(motorPins_);
}

rpicomponents::Steppermotor::Steppermotor(const std::vector<int>& pins, int steps) : Motor(COMPONENT_STEPPERMOTOR), steps_{ steps },
	motorPins_{ {pins} }, pins_{ CreatePinVector(motorPins_) }
{
	AddPins(motorPins_);
}

rpicomponents::Steppermotor::Steppermotor(const Steppermotor& motor) : Steppermotor(motor.GetMotorPins(), motor.GetMotorSteps())
{
	AddPins(motor.GetMotorPins());
}

std::vector<std::unique_ptr<rpicomponents::pin::Pin>> rpicomponents::Steppermotor::CreatePinVector(const std::vector<int>& pins) const {
	if (pins.size() != 4) throw std::invalid_argument("Steppermotor needs 4 pins!");

    std::vector<std::unique_ptr<rpicomponents::pin::Pin>> pinVec;
    pinVec.emplace_back(pin::PinCreator::CreatePin(pins[0], pin::DIGITAL_MODE));
    pinVec.emplace_back(pin::PinCreator::CreatePin(pins[1], pin::DIGITAL_MODE));
    pinVec.emplace_back(pin::PinCreator::CreatePin(pins[2], pin::DIGITAL_MODE));
    pinVec.emplace_back(pin::PinCreator::CreatePin(pins[3], pin::DIGITAL_MODE));

	return pinVec;
}

void rpicomponents::Steppermotor::Rotate(int steps, bool cw, long stepDelay)
{
	if(steps < 0) throw std::invalid_argument("steps cannot be negative!");
    if(stepDelay < 1) throw std::invalid_argument("stepDelay cannot be lower than 1 ms!");

	auto stepVecSize = stepVector_.size();
	auto cylces = steps / stepVecSize + 1;
    int loopCounter = steps < stepVecSize ? steps : stepVecSize, pos = -1;

	for (int i = 0; i < cylces && loopCounter > 0; i++) {
		for (int j = 0; j < loopCounter; j++) {
            pos = currentCoil_.load();
            pos = (cw ? (pos + j) : (pos - j)) % stepVecSize; // the next coil to be turned on;
			currentCoil_.store(pos);
			for (int k = 0; k < pins_.size(); k++) {
				pins_[k]->Output(stepVector_[pos] == (1 << k));
			}
            rpicomponents::utils::Waiter::SleepMillis(stepDelay);
		}
		steps -= loopCounter;
		loopCounter = steps < stepVecSize ? steps : stepVecSize;
	}
}

void rpicomponents::Steppermotor::Stop() const
{
	for (int i = 0; i < pins_.size(); i++) pins_[i]->OutputOff();
}


int rpicomponents::Steppermotor::GetMotorSteps() const {
	return steps_;
}


const std::vector<int> rpicomponents::Steppermotor::GetMotorPins() const {
	return motorPins_;
}
