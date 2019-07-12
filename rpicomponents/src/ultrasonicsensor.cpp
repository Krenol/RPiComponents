#include "ultrasonicsensor.hpp"
#include <cmath>



using namespace rpicomponents::pin;
using namespace rpicomponents::pin::utils;

const std::map<rpicomponents::DISTANCE_UNIT, float> rpicomponents::UltrasonicSensor::convert_values_ = { {UNIT_M, 1.0f},  {UNIT_CM, 1e-2f}, {UNIT_MM, 1e-3f}, {UNIT_M, 1e-6f} };

void rpicomponents::UltrasonicSensor::Initialize() const
{
	auto mode = trigger_pin_->OutputMode();
	if (mode != DIGITAL_MODE) throw new std::invalid_argument("given trigger pin is not in digital mode; it must be on digital mode for a ultrasonsic sensor!");
	mode = echo_pin_->OutputMode();
	if (mode != INPUT_MODE) throw new std::invalid_argument("given echo pin is not in input mode; it must be on input mode for a ultrasonsic sensor!");
	AddPin(trigger_pin_->GetPin());
	AddPin(echo_pin_->GetPin());
}

float rpicomponents::UltrasonicSensor::GetEchoTime() const
{
	std::lock_guard<std::mutex> lck(mtx_);
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

rpicomponents::UltrasonicSensor::UltrasonicSensor(const pin::Pin* trigger_pin, const pin::Pin* echo_pin) : Component("ultrasonic_sensor"), trigger_pin_{ trigger_pin }, echo_pin_{ echo_pin }
{
	Initialize();
}

rpicomponents::UltrasonicSensor::UltrasonicSensor(int8_t trigger_pin, int8_t echo_pin) :
	Component("ultrasonic_sensor"), trigger_pin_{ PinFactory::CreatePin(trigger_pin, DIGITAL_MODE) }, echo_pin_{ PinFactory::CreatePin(echo_pin, INPUT_MODE) }
{
	Initialize();
}

float rpicomponents::UltrasonicSensor::MeasureDistance() const
{
	return MeasureDistance(std_temperature_, std_unit_);
}

float rpicomponents::UltrasonicSensor::MeasureDistance(float temperature) const
{
	return MeasureDistance(temperature, std_unit_);
}

float rpicomponents::UltrasonicSensor::MeasureDistance(DISTANCE_UNIT unit) const
{
	return MeasureDistance(std_temperature_, unit);
}

float rpicomponents::UltrasonicSensor::MeasureDistance(float temperature, DISTANCE_UNIT unit) const
{
	auto vs = CalculateSpeedOfSound(temperature, unit); //[unit/s]
	auto ping = GetEchoTime() / 2; //[s]

	return ping * vs;
}

float rpicomponents::UltrasonicSensor::CalculateSpeedOfSound() const
{	
	return CalculateSpeedOfSound(std_temperature_, std_unit_);
}

float rpicomponents::UltrasonicSensor::CalculateSpeedOfSound(float temperature) const
{
	return CalculateSpeedOfSound(temperature, std_unit_);
}

float rpicomponents::UltrasonicSensor::CalculateSpeedOfSound(DISTANCE_UNIT unit) const
{
	return CalculateSpeedOfSound(std_temperature_, unit);
}

float rpicomponents::UltrasonicSensor::CalculateSpeedOfSound(float temperature, DISTANCE_UNIT unit) const
{
	auto val = 331.5f + 0.6f * temperature;
	val = UnitConverter(val, UNIT_M, unit);
	return val;
}

float rpicomponents::UltrasonicSensor::UnitConverter(float value, DISTANCE_UNIT inUnit, DISTANCE_UNIT outUnit) const
{
	try {
		value *= convert_values_.at(inUnit) / convert_values_.at(outUnit);
	}
	catch (std::exception e) {
		std::string err("passed inUnit or outUnit are not valid ", e.what());
		throw std::invalid_argument(err.c_str());
	}
}
