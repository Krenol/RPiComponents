#include "component.hpp"
#include "pcf8591.hpp"

#ifndef RPICOMPONENTS_PHOTORESISTOR_H
#define RPICOMPONENTS_PHOTORESISTOR_H

namespace rpicomponents {
	constexpr const char* COMPONENT_PHOTORESISTOR = "photoresistor";
	class Photoresistor : Component {
	private:
		const std::shared_ptr<rpicomponents::Pcf8591> pcf_;
		const int pcf_pin_{ -1 };
		const float voltage_{ 3.3f }; //in V
		static const std::vector<float> allowed_voltages_;
		/*
		generic motion sensor initializer to avoid code duplication
		*/
        void Initialize();

	public:

		/*
		 Constructor for the photoresistor

		 @param pcf The pcf8591 shared_ptr
		 @param read_pin the pin of the pcf the output of the photoresistor can be read from
		 @param voltage the voltage at the pcf; either 3.3 V or 5 V
		*/
		Photoresistor(std::shared_ptr <rpicomponents::Pcf8591> pcf,  int read_pin = 0, float  voltage = 3.3);

		/*
		 Copy Constructor for the photoresistor

		 @param photoresistor The photoresistor to be copied
		*/
		Photoresistor(const Photoresistor& photoresistor);

		/*
		 Method to check if the motion sensor has detected a motion or not

		 @returns true if a motion has been detected else false
		*/
		int GetPhotoresistorValue() const;

		/*
		 Method to check if the motion sensor has detected a motion or not

		 @returns true if a motion has been detected else false
		*/
		float GetPhotoresistorVoltage() const;

		/*
		Method to get the pcf 
		@returns the pcf 
		*/
		const std::shared_ptr <rpicomponents::Pcf8591>& GetPcf() const;

		/*
		Method to get the pcf pin of the photoresistor
		@returns the pcf pin of the photoresistor
		*/
		int GetPcfPin() const;

		/*
		Method to get the voltage of this photoresistor
		@returns the set voltage of this photoresistor
		*/
		float GetVoltage() const;
	};
}

#endif
