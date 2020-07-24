#include "component.hpp"
#include "pcf8574.hpp"


#ifndef RPICOMPONENTS_LCD1602_H
#define RPICOMPONENTS_LCD1602_H

namespace rpicomponents {

	constexpr const char* COMPONENT_LCD1602 = "lcd1602";
	constexpr const int COMPONENT_LCD1602_MAX_CHARS = 16, COMPONENT_LCD1602_LINES = 2, COMPONENT_LCD1602_BITS = 4;

	struct LcdPins {
		LcdPins(int pinBase) : pinBase{ pinBase }, rs{ pinBase }, rw(pinBase + 1), en{ pinBase + 2 }, led(pinBase + 3), d4{ pinBase + 4 }, d5{ pinBase + 5 }, d6{ pinBase + 6 }, d7{ pinBase + 7 }
		{

		}
		const int pinBase, rs, rw, en, led, d4, d5, d6, d7;
	};

	class Lcd1602 : public Component
	{
	private:
		std::unique_ptr<Pcf8574> pcf_;
		const int lcdHandle_{ -1 };
		const LcdPins lcdPins_;
		const long sleepMs_{ 300 };

		/*
		Method to init component
		*/
        void Initialize();

	public:
		/*
		Constructor for Lcd1602 component

		@param pcf The used pcf of the LCD
		*/
		Lcd1602(std::unique_ptr<Pcf8574> pcf);

		/*
		Copy Constructor for Lcd1602 component

		@param lcd The lcd to be copied
		*/
		Lcd1602(const Lcd1602& lcd);

		/*
		Method to get the pcf 

		@returns const ref to pcf 
		*/
		const std::unique_ptr<Pcf8574>& GetPcf() const;

		/*
		Method to turn on the lcd's backlight
		*/
		void TurnOnBacklight() const;

		/*
		Method to turn off the lcd's backlight
		*/
		void TurnOffBacklight() const;

		/*
		Method to write a line to the lcd
		@param line The line to be written to
		@param text The text to be written
		@param moveText If true the current text is moved to the right else it is overwritten
		*/
		void WriteLine(int line, std::string& text, bool moveText = false) const;
	};
}

#endif
