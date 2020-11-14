#include "steppermotor.hpp"
#include <unistd.h>

//http://www.lonecpluspluscoder.com/2015/08/13/an-elegant-way-to-extract-keys-from-a-c-map/
template<typename TK, typename TV>
std::vector<TK> ExtractKeys(std::map<TK, TV> const& input_map) {
	std::vector<TK> retval;
	for (auto const& element : input_map) {
		retval.push_back(element.first);
	}
	return retval;
}

rpicomponents::Steppermotor::Steppermotor(int pin1, int pin2, int pin3, int pin4, int steps) : 
	Motor(COMPONENT_STEPPERMOTOR), steps_{steps}
{	
	pin1_ = pin::PinCreator::CreateDigitalPin(pin1, pin::DIGITAL_MODE_MAX_VAL);
	pin2_ = pin::PinCreator::CreateDigitalPin(pin2, pin::DIGITAL_MODE_MAX_VAL);
	pin3_ = pin::PinCreator::CreateDigitalPin(pin3, pin::DIGITAL_MODE_MAX_VAL);
	pin4_ = pin::PinCreator::CreateDigitalPin(pin4, pin::DIGITAL_MODE_MAX_VAL);
	pin_map_ = {{1, pin1_->GetPinData()}, {2, pin2_->GetPinData()}, {3, pin3_->GetPinData()}, {4, pin4_->GetPinData()}};
	pins_ = {{1, pin1_}, {2, pin2_}, {3, pin3_}, {4, pin4_}};
	AddPins({pin1, pin2, pin3, pin4});
}

rpicomponents::Steppermotor::Steppermotor(const std::map<int, pin::pin_data>& pin_map, int steps) : 
	Motor(COMPONENT_STEPPERMOTOR), steps_{steps}
{
	int pin1 = pin_map.at(1).pin, pin2 = pin_map.at(2).pin, pin3 = pin_map.at(3).pin, pin4 = pin_map.at(4).pin;
	pin1_ = pin::PinCreator::CreateDigitalPin(pin1, pin::DIGITAL_MODE_MAX_VAL);
	pin2_ = pin::PinCreator::CreateDigitalPin(pin2, pin::DIGITAL_MODE_MAX_VAL);
	pin3_ = pin::PinCreator::CreateDigitalPin(pin3, pin::DIGITAL_MODE_MAX_VAL);
	pin4_ = pin::PinCreator::CreateDigitalPin(pin4, pin::DIGITAL_MODE_MAX_VAL);
	pin_map_ = {{1, pin1_->GetPinData()}, {2, pin2_->GetPinData()}, {3, pin3_->GetPinData()}, {4, pin4_->GetPinData()}};
	pins_ = {{1, pin1_}, {2, pin2_}, {3, pin3_}, {4, pin4_}};
	AddPins({pin1, pin2, pin3, pin4});
}

rpicomponents::Steppermotor::Steppermotor(const Steppermotor& motor) : Steppermotor(motor.GetMotorPins(), motor.GetMotorSteps())
{

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
            for(auto it = pins_.begin(); it != pins_.end(); ++it) {
                it->second->Output(stepVector_[pos] == (1 << std::distance(pins_.begin(), it)));
            }
            usleep(stepDelay);
		}
		steps -= loopCounter;
		loopCounter = steps < stepVecSize ? steps : stepVecSize;
	}
}

void rpicomponents::Steppermotor::Stop()
{
	for (auto it : pins_) {
		it.second->OutputOff();
	}
}


int rpicomponents::Steppermotor::GetMotorSteps() const {
	return steps_;
}


const std::map<int, pin::pin_data>& rpicomponents::Steppermotor::GetMotorPins() const {
	return pin_map_;
}
