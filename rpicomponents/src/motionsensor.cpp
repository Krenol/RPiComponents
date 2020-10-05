#include "motionsensor.hpp"


rpicomponents::Motionsensor::Motionsensor(const Motionsensor& motionsensor) : Motionsensor(motionsensor.GetPin())
{
}

rpicomponents::Motionsensor::Motionsensor(int pin) : Component(COMPONENT_MOTIONSENSOR) {
    pin_ = pin::PinCreator::CreateInputPin(pin, 1);
    AddPin(pin);
    Initialize();
}

bool rpicomponents::Motionsensor::MotionDetected() const {
	
    auto val = pin_->ReadPinValue();
	if (val > 0) return true;
	return false;
}

int rpicomponents::Motionsensor::GetPin() const
{
	return pin_->GetPin();
}
