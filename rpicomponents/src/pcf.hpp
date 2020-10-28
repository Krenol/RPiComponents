#include "component.hpp"

#ifndef RPICOMPONENTS_PCF_H
#define RPICOMPONENTS_PCF_H

namespace rpicomponents {
	constexpr const char* COMPONENT_PCF = "pcf";

	class Pcf : public Component
	{
	private:
		/*
		Method to initilaize the pcf
		*/
        void Initialize();

	protected:
		const int pin_base_{ 64 }, address_{ 0x48 }, resolution_{ 0 }, handle_;
		const int min_pin_offset_{ 0 }, max_pin_offset_{ 1 }, read_pin_count_{ 0 }, write_pin_count_{ 0 };
		~Pcf(); //virtual protected destructor to make class abstract

	public:
		/*
		Constructor
		@param address: The i2c address of the pcf (must be greater than 63)
		@param pin_base: The pin base of the i2c component
		@param read_pin_count: The amount of read pins of the pcf
		@param write_pin_count: The amount of write pins of the pcf
		@param min_pin_offset: The min pin offset of the pcf to the pin base
		@param max_pin_offset: The max pin offset to the pin base
		@param comp_name: The name of the child component; e.g. pcf8574
		*/
		Pcf(int address, int pin_base = 64, int read_pin_count = 0, int write_pin_count = 0, 
			int min_pin_offset = 0, int max_pin_offset = 1, const std::string& comp_name = COMPONENT_PCF);

		/*
		Copy Constructor

		@param pcf Pcf to be copied
		*/
		Pcf(const Pcf& pcf);

		/*
		Method that checks if a pcf pin is inside the valid pin range (between min_pin_offset_ and max_pin_offset_)
	
		@param pcf_pin_no: The pcf pin to be checked
		*/
		bool CheckIfPcfPin(int pcf_pin_no) const;

		/*
		Method that writes output to a pcf pin

		@param pcf_pin_no: The pcf pin to be written to
		@param value: The value to be written (0 to resolution_)
		*/
        virtual void WriteToPcfPin(int pcf_pin_no, unsigned int value) = 0;

		/*
		Method that reads the input to a pcf pin

		@param pcf_pin_no: The pcf pin to be read
		@returns: the read digital pin value (0 to resolution_)
		*/
        virtual int ReadFromPcfPin(int pcf_pin_no) = 0;

		/*
		Method that returns the resolution of the pcf

		@returns: the resolution_ integer
		*/
		int GetResolution() const;

		/*
		Method that returns the amount of pins that can be read from

		@returns: the amount of read pins 
		*/
		int AmountReadPins() const;

		/*
		Method that returns the amount of pins that can be written to

		@returns: the amount of write pins 
		*/
		int AmountWritePins() const;

		/*
		Get the pcf address

		@returns the pcf address
		*/
		int GetPcfAddress() const;

		/*
		Get the PCF pin base
		@returns the pin base of the pcf
		*/
		int GetPinBase() const;

		/*
		Get the min pin offset of the pcf
		@returns the min pin offset
		*/
		int GetMinPinOffset() const;

		/*
		Get the max pin offset of the pcf
		@returns the max pin offset
		*/
		int GetMaxPinOffset() const;
	};
}
#endif
