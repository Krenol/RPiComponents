#include "ultrasonicsensor.hpp"

using namespace std;
using namespace rpicomponents;
using namespace rpicomponents::pin;
using namespace rpicomponents::pin::utils;

const map<DISTANCE_UNIT, float> UltrasonicSensor::convert_values_ = { {UNIT_M, 1.0f},  {UNIT_CM, 1e-2f}, {UNIT_MM, 1e-3f}, {UNIT_M, 1e-6f} };

void UltrasonicSensor::Initialize() const
{
	auto mode = trigger_pin_->OutputMode();
	if (mode != DIGITAL_MODE) throw new invalid_argument("given trigger pin is not in digital mode; it must be on digital mode for a ultrasonsic sensor!");
	mode = echo_pin_->OutputMode();
	if (mode != INPUT_MODE) throw new invalid_argument("given echo pin is not in input mode; it must be on input mode for a ultrasonsic sensor!");
	AddPin(trigger_pin_->GetPin());
	AddPin(echo_pin_->GetPin());
}

float UltrasonicSensor::GetEchoTime() const
{
	lock_guard<mutex> lck(mtx_);
	trigger_pin_->OutputOn();
	rpicomponents::utils::Waiter::SleepNanos(10);
	trigger_pin_->OutputOff();
	clock_t start = clock();
	while (clock() - start < max_delay_time_)
	{
		if (echo_pin_->ReadPinValue() == HIGH)
		{
			start = clock();
			while (echo_pin_->ReadPinValue() && clock() - start < max_delay_time_) {}
			return (float)(clock() - start) / CLOCKS_PER_SEC;
		}
	}
	return INFINITY;
}

UltrasonicSensor::UltrasonicSensor(const pin::Pin* trigger_pin, const pin::Pin* echo_pin) : Component("ultrasonic_sensor"), trigger_pin_{ trigger_pin }, echo_pin_{ echo_pin }
{
	Initialize();
}

UltrasonicSensor::UltrasonicSensor(int8_t trigger_pin, int8_t echo_pin) :
	Component("ultrasonic_sensor"), trigger_pin_{ PinFactory::CreatePin(trigger_pin, DIGITAL_MODE) }, echo_pin_{ PinFactory::CreatePin(echo_pin, INPUT_MODE) }
{
	Initialize();
}

float UltrasonicSensor::MeasureDistance() const
{
	return MeasureDistance(std_temperature_, std_unit_);
}

float UltrasonicSensor::MeasureDistance(float temperature) const
{
	return MeasureDistance(temperature, std_unit_);
}

float UltrasonicSensor::MeasureDistance(DISTANCE_UNIT unit) const
{
	return MeasureDistance(std_temperature_, unit);
}

float UltrasonicSensor::MeasureDistance(float temperature, DISTANCE_UNIT unit) const
{
	auto vs = CalculateSpeedOfSound(temperature, unit); //[unit/s]
	auto ping = GetEchoTime() / 2; //[s]

	return ping * vs;
}

float UltrasonicSensor::CalculateSpeedOfSound() const
{	
	return CalculateSpeedOfSound(std_temperature_, std_unit_);
}

float UltrasonicSensor::CalculateSpeedOfSound(float temperature) const
{
	return CalculateSpeedOfSound(temperature, std_unit_);
}

float UltrasonicSensor::CalculateSpeedOfSound(DISTANCE_UNIT unit) const
{
	return CalculateSpeedOfSound(std_temperature_, unit);
}

float UltrasonicSensor::CalculateSpeedOfSound(float temperature, DISTANCE_UNIT unit) const
{
	auto val = 331.5f + 0.6f * temperature;
	val = UnitConverter(val, UNIT_M, unit);
	return val;
}

float UltrasonicSensor::UnitConverter(float value, DISTANCE_UNIT inUnit, DISTANCE_UNIT outUnit) const
{
	try {
		value *= convert_values_.at(inUnit) / convert_values_.at(outUnit);
	}
	catch (exception e) {
		string err("passed inUnit or outUnit are not valid ", e.what());
		throw invalid_argument(err.c_str());
	}
}
