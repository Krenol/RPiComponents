#include "motionsensor.hpp"

using namespace std;
using namespace rpicomponents;
using namespace rpicomponents::pin;

void Motionsensor::Initialize() const {
	if (pin_ == nullptr) throw new invalid_argument("pin cannot be null");
	if(pin_->OutputMode() != pin::utils::INPUT_MODE) throw new invalid_argument("pin must be of type INPUT_MODE");
	AddPin(pin_->GetPin());
}


Motionsensor::Motionsensor(const Pin* pin) : Component("motionsensor"), pin_{ pin }{
	Initialize();
}

Motionsensor::Motionsensor(int8_t pin) : Component("motionsensor"), pin_{ PinFactory::CreatePin(pin, pin::utils::INPUT_MODE) }{
	Initialize();
}

bool Motionsensor::MotionDetected() const {
	auto val = pin_->ReadPinValue();
	if (val > 0) return true;
	return false;
}