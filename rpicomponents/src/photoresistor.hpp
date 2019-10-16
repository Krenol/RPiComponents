#include "component.hpp"
#include "pcf8591.hpp"

#ifndef RPICOMPONENTS_PHOTORESISTOR_H
#define RPICOMPONENTS_PHOTORESISTOR_H

namespace rpicomponents {

	class Photoresistor : Component {
	private:
		const rpicomponents::Pcf8591* pcf_;
		const int pcf_pin_{ -1 };
		const float voltage_{ 3.3f }; //in V
		static const std::vector<float> allowed_voltages_;
		/*
		 * generic motion sensor initializer to avoid code duplication
		*/
		void Initialize() const;

	public:

		/*
		 * Constructor for the photoresistor
		 * @param pcf constant pointer to the pcf8591 the photoresistor is connected to
		 * @param pcf_pin the pin of the pcf the output of the photoresistor can be read from
		 * @param voltage the voltage at the pcf; either 3.3 V or 5 V
		*/
		Photoresistor(const rpicomponents::Pcf8591* pcf, int pcf_pin = 0, float voltage = 3.3);

		/*
		 * Method to check if the motion sensor has detected a motion or not
		 * NON BLOCKING
		 * @returns true if a motion has been detected else false
		*/
		int GetPhotoresistorValue() const;

		/*
		 * Method to check if the motion sensor has detected a motion or not
		 * NON BLOCKING
		 * @returns true if a motion has been detected else false
		*/
		float GetPhotoresistorVoltage() const;
	};
}

#endif