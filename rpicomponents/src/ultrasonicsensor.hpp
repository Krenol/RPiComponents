#include "component.hpp"
#include <ctime>
#include <thread>
#include <map>
#include "../utils/include/rpicomponents/utils/rpicomponents_utils.hpp"

#ifndef RPICOMPONENTS_ULTRASONIC_SENSOR_H
#define RPICOMPONENTS_ULTRASONIC_SENSOR_H

namespace rpicomponents {
	/**
	* Enumeration holding all available distance units
	*/
	enum DISTANCE_UNIT {
		UNIT_M, UNIT_CM, UNIT_MM, UNIT_NM
	};
    constexpr const char* COMPONENT_ULTRASONIC_SENSOR= "ultrasonic_sensor";
	class UltrasonicSensor : public Component {
	private:
        const std::unique_ptr<pin::Pin> trigger_pin_; //the used trigger pin of the sensor
        const std::unique_ptr<pin::Pin>  echo_pin_; //the used echo pin of the sensor
		const clock_t max_delay_time_ = 10 * 1e-3 * CLOCKS_PER_SEC; //ms
		const float std_temperature_ = 20.0f;
		const DISTANCE_UNIT std_unit_ = UNIT_MM;
		static const std::map<DISTANCE_UNIT, float> convert_values_;

		/*
		Initializer for Constructors; reduce redundancy
		*/
		void Initialize() const;

		/*
		Method to measure the ping time to an object

		@returns The ping time to an object in seconds or INFINITY if above the max_delay_time_
		*/
		float GetEchoTime() const;

	public:
		/*
		Constructor for creating a ultrasonic sensor
		
		@param trigger_pin: Pointer to the pin of the ultrasonic sensor to trigger a measurement
		@param echo_pin: Pointer to the pin of the ultrasonic sensor to measure the inbound wave
		*/
        UltrasonicSensor(int trigger_pin, int echo_pin);

		/*
		Constructor for creating a ultrasonic sensor
		
		@param trigger_pin: pin of the ultrasonic sensor to trigger a measurement
		@param echo_pin: pin of the ultrasonic sensor to measure the inbound wave
		*/
		//UltrasonicSensor(int&& trigger_pin, int&& echo_pin);

        /*
        Copy Constructor for creating a ultrasonic sensor
        
        @param trigger_pin: pin of the ultrasonic sensor to trigger a measurement
        @param echo_pin: pin of the ultrasonic sensor to measure the inbound wave
        */
        UltrasonicSensor(const UltrasonicSensor &uss);

		/*
		Method to measure the distance to an object
		
		@returns the distance to a object in UNIT_MM, or INFINITY if nothing is measured
		*/
		float MeasureDistance() const;

		/*
		Method to measure the distance to an object
		
		@param temperature: the temperature of air (influences the speed of sound)
		@returns the distance to a object in UNIT_MM, or INFINITY if nothing is measured
		*/
		float MeasureDistance(float  temperature) const;

		/*
		Method to measure the distance to an object
		
		@param unit: the unit of the to be returned distance value
		@returns the distance to a object in DISTANCE_UNIT, or INFINITY if nothing is measured
		*/
		float MeasureDistance(DISTANCE_UNIT unit) const;

		/*
		Method to measure the distance to an object
		
		@param temperature: the temperature of air (influences the speed of sound)
		@param unit: the unit of the to be returned distance value
		@returns the distance to a object in DISTANCE_UNIT, or INFINITY if nothing is measured
		*/
		float MeasureDistance(float  temperature, DISTANCE_UNIT unit) const;

		/*
		Method to measure the distance to an object
		
		@param temperature: the temperature of air (influences the speed of sound)
		@returns the speed of sound to a object in mm/s
		*/
		float CalculateSpeedOfSound() const;

		/*
		Method to measure the distance to an object
		
		@param temperature: the temperature of air (influences the speed of sound)
		@returns the speed of sound to a object in mm/s for a given temperature
		*/
		float CalculateSpeedOfSound(float  temperature) const;

		/*
		Method to measure the distance to an object
		
		@param unit: the unit of the to be returned speed of sound value
		@returns the speed of sound to a object in DISTANCE_UNIT/s
		*/
		float CalculateSpeedOfSound(DISTANCE_UNIT unit) const;

		/*
		Method to measure the distance to an object
		
		@param temperature: the temperature of air (influences the speed of sound)
		@param unit: the unit of the to be returned speed of sound value
		@returns the speed of sound to a object in DISTANCE_UNIT/s
		*/
		float CalculateSpeedOfSound(float  temperature, DISTANCE_UNIT unit) const;

		/*
		Method to convert one unit to the other
		
		@param value: float of the to be converted value
		@param inUnit: the unit of the passed value
		@param outUnit: the unit of the return value
		@returns the converted value in outUnit
		*/
		float UnitConverter(float  value, DISTANCE_UNIT inUnit, DISTANCE_UNIT outUnit) const;

		/*
		Method to get the used trigger pin
		
		@returns the used pin of the component
		*/
		int GetTriggerPin() const;

		/*
		Method to get the used echo pin
		
		@returns the used pin of the component
		*/
		int GetEchoPin() const;
	};
}

#endif
