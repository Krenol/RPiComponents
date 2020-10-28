#include "component.hpp"
#include "pcf.hpp"

#ifndef RPICOMPONENTS_PCF8574_H
#define RPICOMPONENTS_PCF8574_H

namespace rpicomponents {
	constexpr const char* COMPONENT_PCF8574 = "pcf8574";
	constexpr int COMPONENT_PCF8574_READ_PINS = 8, COMPONENT_PCF8574_WRITE_PINS = 8, COMPONENT_PCF8574_MIN_PIN_OFFSET = 0, 
		COMPONENT_PCF8574_MAX_PIN_OFFSET = 7;

	class Pcf8574 : public Pcf {
	private:
		unsigned int data_;
		/*
		Method that sets the pin mode of a pcf pin to in- or output

		@param pcf_pin_no: The pcf pin (between min_pin_offset_ and max_pin_offset_) for which the pin mode should be set
		@param pin_mode: The pin_mode to be set for the pin
		*/
		void SetPinMode(int pcf_pin_no, int pin_mode);
	public:
		/*
		Constructor

		@param address: The i2c address of the pcf8574 (must be greater than 63)
		@param pin_base: The pin base of the i2c component
		*/
		Pcf8574(int address, int pin_base = 64);

		/*
		Constructor

		@param address: The i2c address of the pcf8574 (must be greater than 63)
		@param pin_base: The pin base of the i2c component
		*/
		//Pcf8574(int&& address, int&& pin_base = 64);

		/*
		Constructor

		@param pcf: The pcf to be copied
		*/
		Pcf8574(const Pcf8574& pcf);

		/*
		Method that writes output to a pcf pin

		@param value: The value to be written (0-1)
		@param pcf_pin_no: The pcf pin to be written to
		*/
        void WriteToPcfPin(int pcf_pin_no, unsigned int value);

		/*
		Method that reads the input to a pcf pin

		@param pcf_pin_no: The pcf pin to be read
		@returns: the read digital pin value (0 to 1)
		*/
        int ReadFromPcfPin(int pcf_pin_no);
	};
}

#endif
