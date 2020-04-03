#include "motionsensor.hpp"


void rpicomponents::Motionsensor::Initialize() {
	
    if(pin_->OutputMode() != rpicomponents::pin::INPUT_MODE) throw new std::invalid_argument("pin must be of type INPUT_MODE");
    AddPin(pin_->GetPin());
}


rpicomponents::Motionsensor::Motionsensor(const Motionsensor& motionsensor) : Motionsensor(motionsensor.GetPin())
{
	
}

rpicomponents::Motionsensor::Motionsensor(std::shared_ptr<pin::Pin> pin) : Component(COMPONENT_MOTIONSENSOR),
pin_{ pin }{
    Initialize();
}

bool rpicomponents::Motionsensor::MotionDetected() const {
	
    auto val = pin_->ReadPinValue();
	if (val > 0) return true;
	return false;
}

const std::shared_ptr<rpicomponents::pin::Pin>& rpicomponents::Motionsensor::GetPin() const
{
	return pin_;
}
