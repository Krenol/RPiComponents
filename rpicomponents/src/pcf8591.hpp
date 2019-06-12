#include "pcf.hpp"
#include <pcf8591.h>

#ifndef RPICOMPONENTS_PCF8591_H
#define RPICOMPONENTS_PCF8591_H

namespace rpicomponents {

	class PCF8591 : public PCF
	{
	private:
		/*
		* DUMMY do avoid being abstract
		*/
		void WriteToPcfPin(int pcf_pin_no, int value) const;

	public:
		/*
		* Constructor
		* @param address: The i2c address of the pcf8591 (must be greater than 63)
		* @param pin_base: The pin base of the i2c component
		*/
		PCF8591(int address, int pin_base = 64);

		/*
		* Method that writes output to a pcf pin
		* BLOCKING
		* @param value: The value to be written (0-255)
		*/
		void WriteToPcfPin(int value) const;

		/*
		* Method that reads the input to a pcf pin
		* BLOCKING
		* @param pcf_pin_no: The pcf pin to be written to
		* @returns: the read digital pin value (0 to 255)
		*/
		int ReadFromPcfPin(int pcf_pin_no) const;

		/*
		* Method that returns the amount of pins that can be read from
		* @returns: the amount of read pins (4)
		*/
		int AmountReadPins() const;

		/*
		* Method that returns the amount of pins that can be written to
		* @returns: the amount of write pins (1)
		*/
		int AmountWritePins() const;
	};
}
#endif