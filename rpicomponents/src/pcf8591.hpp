#include "component.hpp"
#include <pcf8591.h>
#include <wiringPiI2C.h>

#ifndef RPICOMPONENTS_PCF8591_H
#define RPICOMPONENTS_PCF8591_H

namespace rpicomponents {

	class PCF8591 : public Component
	{
	private:
		const int pin_base_{ 64 }, address_{ 0x48 }, resolution_{ 256 }, min_pin_offset_{ 0 }, max_pin_offset_{ 3 };
		void Initialize() const; 
		bool CheckPin(int pin) const;

	public:
		PCF8591(int address = 0x48, int pinBase = 64); 

		~PCF8591(); 

		void AnalogWriteToPin(int pcf_pin_no, int value) const; 

		int AnalogReadFromPin(int pcf_pin_no) const;

		int AmountReadPins() const;

		int AmountWritePins() const;

		int GetResolution() const;
	};
}
#endif