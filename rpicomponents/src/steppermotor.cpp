#include "steppermotor.hpp"
#include "utils/utils.hpp"

//http://www.lonecpluspluscoder.com/2015/08/13/an-elegant-way-to-extract-keys-from-a-c-map/
template<typename TK, typename TV>
std::vector<TK> ExtractKeys(std::map<TK, TV> const& input_map) {
	std::vector<TK> retval;
	for (auto const& element : input_map) {
		retval.push_back(element.first);
	}
	return retval;
}

void rpicomponents::Steppermotor::Initialize() {
    AddPins(motorPins_);
    for(auto it : pins_) {
        if(it.second->OutputMode() != pin::DIGITAL_MODE) {
            throw std::invalid_argument("Steppermotor pins can only be of DIGITAL_MODE!");
        }
    }
}

rpicomponents::Steppermotor::Steppermotor(int pin1, int pin2, int pin3, int pin4, int steps) : 
	Motor(COMPONENT_STEPPERMOTOR), steps_{steps},
	motorPins_{ {pin1->GetPin(), pin2->GetPin(), pin3->GetPin(), pin4->GetPin()} },
	pins_{ {{1, pin1}, {2, pin2}, {3, pin3}, {4, pin4}} }
{
    Initialize();
}

rpicomponents::Steppermotor::Steppermotor(const StepperPinMap& pins, int steps) : Motor(COMPONENT_STEPPERMOTOR), steps_{ steps },
	motorPins_{ ExtractKeys<int,int>(pins) }, pins_{ pins }
{
    Initialize();
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
            utils::Waiter::SleepMillis(stepDelay);
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


const rpicomponents::StepperPinMap& rpicomponents::Steppermotor::GetMotorPins() const {
	return pins_;
}
