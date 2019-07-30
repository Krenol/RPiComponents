#include "motionsensor.hpp"


void rpicomponents::Motionsensor::Initialize() const {
	CheckPin(pin_);
	if(pin_->OutputMode() != rpicomponents::pin::INPUT_MODE) throw new std::invalid_argument("pin must be of type INPUT_MODE");
	AddPin(pin_->GetPin());
}


rpicomponents::Motionsensor::Motionsensor(const rpicomponents::pin::Pin* pin) : Component("motionsensor"), pin_{ pin }{
	Initialize();
}

rpicomponents::Motionsensor::Motionsensor(int8_t pin) : Component("motionsensor"), 
pin_{ rpicomponents::pin::PinFactory::CreatePin(pin, rpicomponents::pin::INPUT_MODE) }{
	Initialize();
}

bool rpicomponents::Motionsensor::MotionDetected() const {
	CheckPin(pin_);
	auto val = pin_->ReadPinValue();
	if (val > 0) return true;
	return false;
}