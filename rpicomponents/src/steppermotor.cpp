#include "steppermotor.hpp"

rpicomponents::Steppermotor::Steppermotor(const EnablePinStruct& enable_pins, const InPinStruct& in_pins, int steps) : 
	Motor(COMPONENT_STEPPERMOTOR, enable_pins, in_pins), steps_{steps}
{
}

rpicomponents::Steppermotor::Steppermotor(int enable_pin1, int enable_pin2, rpicomponents::pin::PIN_MODE enable_pin1_mode, 
	rpicomponents::pin::PIN_MODE enable_pin2_mode, int max_output_enable_pin1, int max_output_enable_pin2, 
	int in_pin1, int in_pin2, int in_pin3, int in_pin4, int steps) :
	Motor(COMPONENT_STEPPERMOTOR, enable_pin1, enable_pin2, enable_pin1_mode, enable_pin2_mode,
        max_output_enable_pin1, max_output_enable_pin2, in_pin1, in_pin2, in_pin3, in_pin4), steps_{ steps }
{
}

void rpicomponents::Steppermotor::Rotate(int steps, bool cw, long stepDelay)
{
	if(steps < 0) throw std::invalid_argument("steps cannot be negative!");
    if(stepDelay < 1) throw std::invalid_argument("stepDelay cannot be lower than 1!");

	auto stepVecSize = stepVector_.size();
	auto cylces = steps / stepVecSize + 1;
    int loopCounter = steps < stepVecSize ? steps : stepVecSize, pos = -1;

	for (int i = 0; i < cylces && loopCounter > 0; i++) {
		for (int j = 0; j < loopCounter; j++) {
            pos = currentCoil_.load();
            pos = (cw ? (pos + j) : (pos - j)) % stepVecSize; // the next coil to be turned on;
			for (int k = 0; k < L293D_INPIN_COUNT; k++) {
                l293d_->WriteToInPin(k, stepVector_[pos] == (1 << k));
			}
            currentCoil_.store(pos);
            rpicomponents::utils::Waiter::SleepNanos(stepDelay);
		}
		steps -= loopCounter;
		loopCounter = steps < stepVecSize ? steps : stepVecSize;
	}
}

void rpicomponents::Steppermotor::Stop() const
{
	l293d_->TurnOffIn1();
	l293d_->TurnOffIn2();
	l293d_->TurnOffIn3();
	l293d_->TurnOffIn4();
}
