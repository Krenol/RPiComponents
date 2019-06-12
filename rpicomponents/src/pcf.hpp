#include "component.hpp"
#include <wiringPiI2C.h>

#ifndef RPICOMPONENTS_PCF_H
#define RPICOMPONENTS_PCF_H

namespace rpicomponents {

	class PCF : public Component
	{
	private:
		/*
		 * Method to initilaize the pcf
		*/
		void Initialize() const;

	protected:
		const int pin_base_{ 64 }, address_{ 0x48 }, resolution_{ 0 }, min_pin_offset_{ 0 }, max_pin_offset_{ 1 };
		virtual ~PCF() = 0; //virtual protected destructor to make class abstract

		/*
		* Method that checks if a pcf pin is inside the valid pin range (between min_pin_offset_ and max_pin_offset_)
		* @param pcf_pin_no: The pcf pin to be checked
		*/
		bool CheckPcfPin(int pcf_pin_no) const;

	public:
		/*
		* Constructor
		* @param address: The i2c address of the pcf (must be greater than 63)
		* @param pin_base: The pin base of the i2c component
		* @param min_pin_offset: The min pin offset of the pcf to the pin base
		* @param max_pin_offset: The max pin offset to the pin base
		* @param comp_name: The name of the child component; e.g. pcf8574
		*/
		PCF(int address, int pin_base = 64, int min_pin_offset = 0, int max_pin_offset = 1, std::string comp_name = "pcf");

		/*
		* Method that writes output to a pcf pin
		* BLOCKING
		* @param pcf_pin_no: The pcf pin to be written to
		* @param value: The value to be written (0 to resolution_)
		*/
		virtual void WriteToPcfPin(int pcf_pin_no, int value) const = 0;

		/*
		* Method that reads the input to a pcf pin
		* BLOCKING
		* @param pcf_pin_no: The pcf pin to be read
		* @returns: the read digital pin value (0 to resolution_)
		*/
		virtual int ReadFromPcfPin(int pcf_pin_no) const = 0;

		/*
		* Method that returns the resolution of the pcf
		* @returns: the resolution_ integer
		*/
		int GetResolution() const;

		/*
		* Method that returns the amount of pins that can be read from
		* @returns: the amount of read pins 
		*/
		virtual int AmountReadPins() const = 0;

		/*
		* Method that returns the amount of pins that can be written to
		* @returns: the amount of write pins 
		*/
		virtual int AmountWritePins() const = 0;
	};
}
#endif