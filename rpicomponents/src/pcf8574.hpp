#include "component.hpp"
#include <pcf8574.h>
#include <wiringPiI2C.h>

#ifndef RPICOMPONENTS_PCF8574_H
#define RPICOMPONENTS_PCF8574_H

namespace rpicomponents {
	class PCF8574 : public Component {
	private:
		const int pin_base_{ 64 }, address_{ 0x48 }, min_pin_offset_{ 0 }, max_pin_offset_{ 7 }, resolution_{ 1 };
		/* 
		 * Method to initilaize the pcf8574
		*/
		void Initialize() const;

		/*
		* Method that sets the pin mode of a pcf pin to in- or output
		* @param pcf_pin_no: The pcf pin (between min_pin_offset_ and max_pin_offset_) for which the pin mode should be set
		* @param pin_mode: The pin_mode to be set for the pin
		*/
		void SetPinMode(int pcf_pin_no, int pin_mode) const;

		/*
		* Method that checks if a pcf pin is inside the valid pin range (between min_pin_offset_ and max_pin_offset_) 
		* @param pcf_pin_no: The pcf pin to be checked
		*/
		bool CheckPcfPin(int pcf_pin_no) const;

	public:
		/*
		* Constructor
		* @param address: The i2c address of the pcf8574 (must be greater than 63)
		* @param pin_base: The pin base of the i2c component
		*/
		PCF8574(int address, int pin_base = 64);

		/*
		* Method that writes output to a pcf pin
		* @param pcf_pin_no: The pcf pin to be written to
		* @param value: The value to be written (must be digital, so 0 or 1)
		*/
		void WriteToPcfPin(int pcf_pin_no, int value) const;

		/*
		* Method that reads the input to a pcf pin
		* @param pcf_pin_no: The pcf pin to be written to
		* @returns: the read digital pin value (0 or 1)
		*/
		int ReadFromPcfPin(int pcf_pin_no) const;

		/*
		* Method that returns the resolution of the pcf8574
		* @returns: the resolution (1)
		*/
		int GetResolution() const;
	};
}

#endif