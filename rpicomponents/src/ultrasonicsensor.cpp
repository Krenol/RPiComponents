#include "ultrasonicsensor.hpp"

using namespace std;
using namespace rpicomponents;
using namespace rpicomponents::pin;

void UltrasonicSensor::Initialize() const
{
	auto mode = trigger_pin_->OutputMode();
	if (mode != DIGITAL_MODE) throw new invalid_argument("given trigger pin is not in digital mode; it must be on digital mode for a ultrasonsic sensor!");
	mode = echo_pin_->OutputMode();
	if (mode != INPUT_MODE) throw new invalid_argument("given echo pin is not in input mode; it must be on input mode for a ultrasonsic sensor!");
	AddPin(trigger_pin_->GetPin());
	AddPin(echo_pin_->GetPin());
}

UltrasonicSensor::UltrasonicSensor(const pin::Pin* trigger_pin, const pin::Pin* echo_pin) : Component("ultrasonic_sensor"), trigger_pin_{ trigger_pin }, echo_pin_{ echo_pin }
{
	Initialize();
}

UltrasonicSensor::UltrasonicSensor(int trigger_pin, int echo_pin) : 
	Component("ultrasonic_sensor"), trigger_pin_{ PinFactory::CreatePin(trigger_pin, DIGITAL_MODE) }, echo_pin_{ PinFactory::CreatePin(echo_pin, INPUT_MODE) }
{
	Initialize();
}

float UltrasonicSensor::MeasureDistance() const
{
	return 0.0f;
}

float UltrasonicSensor::MeasureDistance(float temperature) const
{
	return 0.0f;
}

float UltrasonicSensor::MeasureDistance(DISTANCE_UNIT unit) const
{
	return 0.0f;
}

float UltrasonicSensor::MeasureDistance(float temperature, DISTANCE_UNIT unit) const
{
	return 0.0f;
}

float UltrasonicSensor::CalculateSpeedOfSound()
{
	return 0.0f;
}

float UltrasonicSensor::CalculateSpeedOfSound(float temperature)
{
	return 0.0f;
}

float UltrasonicSensor::CalculateSpeedOfSound(DISTANCE_UNIT unit) const
{
	return 0.0f;
}

float UltrasonicSensor::CalculateSpeedOfSound(float temperature, DISTANCE_UNIT unit) const
{
	return 0.0f;
}
