#include "component.hpp"
#include <pcf.hpp>

#ifndef RPICOMPONENTS_PCF8574_H
#define RPICOMPONENTS_PCF8574_H

namespace rpicomponents {
	class Pcf8574 : public Pcf {
	private:
		/*
		* Method that sets the pin mode of a pcf pin to in- or output
		* @param pcf_pin_no: The pcf pin (between min_pin_offset_ and max_pin_offset_) for which the pin mode should be set
		* @param pin_mode: The pin_mode to be set for the pin
		*/
		void SetPinMode(int8_t pcf_pin_no, int8_t pin_mode) const;
	public:
		/*
		* Constructor
		* @param address: The i2c address of the pcf8574 (must be greater than 63)
		* @param pin_base: The pin base of the i2c component
		*/
		Pcf8574(int16_t address, int16_t pin_base = 64);

		/*
		* Method that writes output to a pcf pin
		* BLOCKING
		* @param value: The value to be written (0-1)
		* @param pcf_pin_no: The pcf pin to be written to
		*/
		void WriteToPcfPin(int8_t pcf_pin_no, int16_t value) const;

		/*
		* Method that reads the input to a pcf pin
		* BLOCKING
		* @param pcf_pin_no: The pcf pin to be read
		* @returns: the read digital pin value (0 to 1)
		*/
		int16_t ReadFromPcfPin(int8_t pcf_pin_no) const;

		/*
		* Method that returns the amount of pins that can be read from
		* @returns: the amount of read pins (8)
		*/
		int8_t AmountReadPins() const;

		/*
		* Method that returns the amount of pins that can be written to
		* @returns: the amount of write pins (8)
		*/
		int8_t AmountWritePins() const;
	};
}

#endif