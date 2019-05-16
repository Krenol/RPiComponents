#include "component.hpp"
#include <ctime>

#ifndef RPICOMPONENTS_COMPONENT_ULTRASONIC_SENSOR_H
#define RPICOMPONENTS_COMPONENT_ULTRASONIC_SENSOR_H

namespace rpicomponents {
	/**
	* Enumeration holding all available distance units
	*/
	enum DISTANCE_UNIT {
		UNIT_M, UNIT_CM, UNIT_MM, UNIT_NM
	};

	class UltrasonicSensor : public Component {
	private:
		const pin::Pin* trigger_pin_; //the used trigger pin of the sensor
		const pin::Pin* echo_pin_; //the used echo pin of the sensor
		const clock_t maxDelay = 10 * 1e-3 * CLOCKS_PER_SEC; //ms
		const float room_temperature_ = 20;

		/**
		* Initializer for Constructors; reduce redundancy
		*/
		void Initialize() const;

	public:
		/**
		* Constructor for creating a ultrasonic sensor
		*
		* @param trigger_pin: Pointer to the pin of the ultrasonic sensor to trigger a measurement
		* @param echo_pin: Pointer to the pin of the ultrasonic sensor to measure the inbound wave
		*/
		UltrasonicSensor(const pin::Pin* trigger_pin, const pin::Pin* echo_pin);

		/**
		* Constructor for creating a ultrasonic sensor
		*
		* @param trigger_pin: pin of the ultrasonic sensor to trigger a measurement
		* @param echo_pin: pin of the ultrasonic sensor to measure the inbound wave
		*/
		UltrasonicSensor(int trigger_pin, int echo_pin);

		/**
		* Method to measure the distance to an object
		*
		* @returns the distance to a object in UNIT_MM, or INFINITY if nothing is measured
		*/
		float MeasureDistance() const;

		/**
		* Method to measure the distance to an object
		*
		* @param temperature: the temperature of air (influences the speed of sound)
		* @returns the distance to a object in UNIT_MM, or INFINITY if nothing is measured
		*/
		float MeasureDistance(float temperature) const;

		/**
		* Method to measure the distance to an object
		*
		* @param unit: the unit of the to be returned distance value
		* @returns the distance to a object in DISTANCE_UNIT, or INFINITY if nothing is measured
		*/
		float MeasureDistance(DISTANCE_UNIT unit) const;

		/**
		* Method to measure the distance to an object
		*
		* @param temperature: the temperature of air (influences the speed of sound)
		* @param unit: the unit of the to be returned distance value
		* @returns the distance to a object in DISTANCE_UNIT, or INFINITY if nothing is measured
		*/
		float MeasureDistance(float temperature, DISTANCE_UNIT unit) const;

		/**
		* Method to measure the distance to an object
		*
		* @param temperature: the temperature of air (influences the speed of sound)
		* @returns the speed of sound to a object in mm/s
		*/
		float CalculateSpeedOfSound();

		/**
		* Method to measure the distance to an object
		*
		* @param temperature: the temperature of air (influences the speed of sound)
		* @returns the speed of sound to a object in mm/s for a given temperature
		*/
		float CalculateSpeedOfSound(float temperature);

		/**
		* Method to measure the distance to an object
		*
		* @param unit: the unit of the to be returned speed of sound value
		* @returns the speed of sound to a object in DISTANCE_UNIT/s
		*/
		float CalculateSpeedOfSound(DISTANCE_UNIT unit) const;

		/**
		* Method to measure the distance to an object
		*
		* @param temperature: the temperature of air (influences the speed of sound)
		* @param unit: the unit of the to be returned speed of sound value
		* @returns the speed of sound to a object in DISTANCE_UNIT/s
		*/
		float CalculateSpeedOfSound(float temperature, DISTANCE_UNIT unit) const;
	};
}

#endif