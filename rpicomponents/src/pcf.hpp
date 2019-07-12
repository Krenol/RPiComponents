#include "component.hpp"

#ifndef RPICOMPONENTS_PCF_H
#define RPICOMPONENTS_PCF_H

namespace rpicomponents {

	class Pcf : public Component
	{
	private:
		/*
		 * Method to initilaize the pcf
		*/
		void Initialize() const;

	protected:
		const int16_t pin_base_{ 64 }, address_{ 0x48 }, resolution_{ 0 };
		const int8_t min_pin_offset_{ 0 }, max_pin_offset_{ 1 };
		virtual ~Pcf() = 0; //virtual protected destructor to make class abstract

	public:
		/*
		* Constructor
		* @param address: The i2c address of the pcf (must be greater than 63)
		* @param pin_base: The pin base of the i2c component
		* @param min_pin_offset: The min pin offset of the pcf to the pin base
		* @param max_pin_offset: The max pin offset to the pin base
		* @param comp_name: The name of the child component; e.g. pcf8574
		*/
		Pcf(int16_t address, int16_t pin_base = 64, int8_t min_pin_offset = 0, int8_t max_pin_offset = 1, std::string comp_name = "pcf");

		/*
		* Method that checks if a pcf pin is inside the valid pin range (between min_pin_offset_ and max_pin_offset_)
		* NON BLOCKING
		* @param pcf_pin_no: The pcf pin to be checked
		*/
		bool CheckIfPcfPin(int8_t pcf_pin_no) const;

		/*
		* Method that writes output to a pcf pin
		* BLOCKING
		* @param pcf_pin_no: The pcf pin to be written to
		* @param value: The value to be written (0 to resolution_)
		*/
		virtual void WriteToPcfPin(int8_t pcf_pin_no, int16_t value) const = 0;

		/*
		* Method that reads the input to a pcf pin
		* BLOCKING
		* @param pcf_pin_no: The pcf pin to be read
		* @returns: the read digital pin value (0 to resolution_)
		*/
		virtual int16_t ReadFromPcfPin(int8_t pcf_pin_no) const = 0;

		/*
		* Method that returns the resolution of the pcf
		* NON BLOCKING
		* @returns: the resolution_ integer
		*/
		int16_t GetResolution() const;

		/*
		* Method that returns the amount of pins that can be read from
		* NON BLOCKING
		* @returns: the amount of read pins 
		*/
		virtual int8_t AmountReadPins() const = 0;

		/*
		* Method that returns the amount of pins that can be written to
		* NON BLOCKING
		* @returns: the amount of write pins 
		*/
		virtual int8_t AmountWritePins() const = 0;
	};
}
#endif