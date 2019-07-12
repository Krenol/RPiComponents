#include "motionsensor.hpp"



using namespace rpicomponents::pin;

void rpicomponents::Motionsensor::Initialize() const {
	if (pin_ == nullptr) throw new std::invalid_argument("pin cannot be null");
	if(pin_->OutputMode() != pin::utils::INPUT_MODE) throw new std::invalid_argument("pin must be of type INPUT_MODE");
	AddPin(pin_->GetPin());
}


rpicomponents::Motionsensor::Motionsensor(const Pin* pin) : Component("motionsensor"), pin_{ pin }{
	Initialize();
}

rpicomponents::Motionsensor::Motionsensor(int8_t pin) : Component("motionsensor"), pin_{ PinFactory::CreatePin(pin, pin::utils::INPUT_MODE) }{
	Initialize();
}

bool rpicomponents::Motionsensor::MotionDetected() const {
	auto val = pin_->ReadPinValue();
	if (val > 0) return true;
	return false;
}