#include "ultrasonicsensor.hpp"
#include <cmath>
#include <unistd.h>

const std::map<rpicomponents::DISTANCE_UNIT, float> rpicomponents::UltrasonicSensor::convert_values_ = { {UNIT_M, 1.0f},  {UNIT_CM, 1e-2f}, {UNIT_MM, 1e-3f}, {UNIT_M, 1e-6f} };



float rpicomponents::UltrasonicSensor::GetEchoTime() const
{
    trigger_pin_->OutputOn();
	usleep(1000);
    trigger_pin_->OutputOff();
	clock_t start = clock();
	while (clock() - start < max_delay_time_)
	{
        if (echo_pin_->ReadPinValue() == 1)
		{
			start = clock();
            while (echo_pin_->ReadPinValue() && clock() - start < max_delay_time_) {}
			return (float)(clock() - start) / CLOCKS_PER_SEC;
		}
	}
	return INFINITY;
}

rpicomponents::UltrasonicSensor::UltrasonicSensor(int trigger_pin, int echo_pin) : 
	Component(COMPONENT_ULTRASONIC_SENSOR)
{
	trigger_pin_ = pin::PinCreator::CreateDigitalPin(trigger_pin, pin::DIGITAL_MODE_MAX_VAL);
	echo_pin_ = pin::PinCreator::CreateInputPin(echo_pin, pin::DIGITAL_MODE_MAX_VAL);
}


rpicomponents::UltrasonicSensor::UltrasonicSensor(const UltrasonicSensor& uss): UltrasonicSensor(uss.GetTriggerPin(), uss.GetEchoPin())
{

}

float rpicomponents::UltrasonicSensor::MeasureDistance() const
{
	return MeasureDistance(std_temperature_, std_unit_);
}

float rpicomponents::UltrasonicSensor::MeasureDistance(float  temperature) const
{
	return MeasureDistance(temperature, std_unit_);
}

float rpicomponents::UltrasonicSensor::MeasureDistance(DISTANCE_UNIT unit) const
{
	return MeasureDistance(std_temperature_, unit);
}

float rpicomponents::UltrasonicSensor::MeasureDistance(float  temperature, DISTANCE_UNIT unit) const
{
	auto vs = CalculateSpeedOfSound(temperature, unit); //[unit/s]
	auto ping = GetEchoTime() / 2; //[s]

	return ping * vs;
}

float rpicomponents::UltrasonicSensor::CalculateSpeedOfSound() const
{	
	return CalculateSpeedOfSound(std_temperature_, std_unit_);
}

float rpicomponents::UltrasonicSensor::CalculateSpeedOfSound(float  temperature) const
{
	return CalculateSpeedOfSound(temperature, std_unit_);
}

float rpicomponents::UltrasonicSensor::CalculateSpeedOfSound(DISTANCE_UNIT unit) const
{
	return CalculateSpeedOfSound(std_temperature_, unit);
}

float rpicomponents::UltrasonicSensor::CalculateSpeedOfSound(float  temperature, DISTANCE_UNIT unit) const
{
	auto val = 331.5f + 0.6f * temperature;
	val = UnitConverter(val, UNIT_M, unit);
	return val;
}

float rpicomponents::UltrasonicSensor::UnitConverter(float  value, DISTANCE_UNIT inUnit, DISTANCE_UNIT outUnit) const
{
	float outVal = INFINITY;
	try {
		outVal = value * convert_values_.at(inUnit) / convert_values_.at(outUnit);
	}
	catch (std::exception e) {
		std::string err("passed inUnit or outUnit are not valid ", e.what());
		throw std::invalid_argument(err.c_str());
	}
	return outVal;
}

int rpicomponents::UltrasonicSensor::GetTriggerPin() const
{
	return trigger_pin_->GetPin();
}

int rpicomponents::UltrasonicSensor::GetEchoPin() const
{
	return echo_pin_->GetPin();
}
