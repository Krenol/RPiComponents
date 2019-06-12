#include "component.hpp"
#include <pcf.hpp>
#include <pcf8574.h>

#ifndef RPICOMPONENTS_PCF8574_H
#define RPICOMPONENTS_PCF8574_H

namespace rpicomponents {
	class PCF8574 : public PCF {
	private:
		/*
		* Method that sets the pin mode of a pcf pin to in- or output
		* @param pcf_pin_no: The pcf pin (between min_pin_offset_ and max_pin_offset_) for which the pin mode should be set
		* @param pin_mode: The pin_mode to be set for the pin
		*/
		void SetPinMode(int pcf_pin_no, int pin_mode) const;
	public:
		/*
		* Constructor
		* @param address: The i2c address of the pcf8574 (must be greater than 63)
		* @param pin_base: The pin base of the i2c component
		*/
		PCF8574(int address, int pin_base = 64);

		/*
		* Method that writes output to a pcf pin
		* BLOCKING
		* @param value: The value to be written (0-1)
		* @param pcf_pin_no: The pcf pin to be written to
		*/
		void WriteToPcfPin(int pcf_pin_no, int value) const;

		/*
		* Method that reads the input to a pcf pin
		* BLOCKING
		* @param pcf_pin_no: The pcf pin to be written to
		* @returns: the read digital pin value (0 to 1)
		*/
		int ReadFromPcfPin(int pcf_pin_no) const;

		/*
		* Method that returns the amount of pins that can be read from
		* @returns: the amount of read pins (8)
		*/
		int AmountReadPins() const;

		/*
		* Method that returns the amount of pins that can be written to
		* @returns: the amount of write pins (8)
		*/
		int AmountWritePins() const;
	};
}

#endif