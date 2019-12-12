#include "motionsensor.hpp"


void rpicomponents::Motionsensor::Initialize() const {
	
    if(pin_->OutputMode() != rpicomponents::pin::INPUT_MODE) throw new std::invalid_argument("pin must be of type INPUT_MODE");
    AddPin(pin_->GetPin());
}


//rpicomponents::Motionsensor::Motionsensor(int&& pin) : Component(COMPONENT_MOTIONSENSOR),
//pin_{ rpicomponents::pin::PinCreator::CreatePin(pin, rpicomponents::pin::INPUT_MODE) }{
//	Initialize();
//}

rpicomponents::Motionsensor::Motionsensor(const Motionsensor& motionsensor) : Component(COMPONENT_MOTIONSENSOR), 
pin_{ rpicomponents::pin::PinCreator::CreatePin(motionsensor.GetPin(), rpicomponents::pin::INPUT_MODE) }
{
	Initialize();
}

rpicomponents::Motionsensor::Motionsensor(int pin) : Component(COMPONENT_MOTIONSENSOR),
pin_{ rpicomponents::pin::PinCreator::CreatePin(pin, rpicomponents::pin::INPUT_MODE) }{
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
