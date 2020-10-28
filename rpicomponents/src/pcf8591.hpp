#include "pcf.hpp"

#ifndef RPICOMPONENTS_PCF8591_H
#define RPICOMPONENTS_PCF8591_H

namespace rpicomponents {
	constexpr const char* COMPONENT_PCF8591 = "pcf8591";
	constexpr int COMPONENT_PCF8591_READ_PINS = 4, COMPONENT_PCF8591_WRITE_PINS = 1, COMPONENT_PCF8591_MIN_PIN_OFFSET = 0,
		COMPONENT_PCF8591_MAX_PIN_OFFSET = 3;
	class Pcf8591 : public Pcf
	{
	public:
		/*
		Constructor

		@param address: The i2c address of the pcf8591 (must be greater than 63)
		@param pin_base: The pin base of the i2c component
		*/
		Pcf8591(int address, int pin_base = 64);

		/*
		Constructor

		@param address: The i2c address of the pcf8591 (must be greater than 63)
		@param pin_base: The pin base of the i2c component
		*/
		//Pcf8591(int&& address, int&& pin_base = 64);

		/*
		Constructor

		@param pcf: The pcf to be copied
		*/
		Pcf8591(const Pcf8591& pcf);

		/*
		Method that writes output to a pcf pin

		@param value: The value to be written (0-255)
		*/
		void WriteToPcfPin(int pcf_pin_no, unsigned int value);

		/*
		Method that reads the input to a pcf pin

		@param pcf_pin_no: The pcf pin to be read
		@returns: the read pin value (0 to 255)
		*/
		int ReadFromPcfPin(int pcf_pin_no);
	};
}
#endif
