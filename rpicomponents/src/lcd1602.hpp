#include "lcd.hpp"
#include <vector>


#ifndef RPICOMPONENTS_LCD1602_H
#define RPICOMPONENTS_LCD1602_H

namespace rpicomponents {

	constexpr const char* COMPONENT_LCD1602 = "lcd1602";
	constexpr const int COMPONENT_LCD1602_MAX_CHARS = 16, COMPONENT_LCD1602_LINES = 2, COMPONENT_LCD1602_BITS = 4;

	class Lcd1602 : public Lcd
	{
	private:
		const useconds_t sleep_ = 30000;
	public:
		/*
		Constructor for Lcd1602 component

		@param pcf The used pcf of the LCD
		*/
		Lcd1602(const Pcf8574& pcf);

		/*
		Copy Constructor for Lcd1602 component

		@param lcd The lcd to be copied
		*/
		Lcd1602(const Lcd1602& lcd);

		/*
		Method to turn on the lcd's backlight
		*/
		void TurnOnBacklight();

		/*
		Method to turn off the lcd's backlight
		*/
		void TurnOffBacklight();

		/*
		Method to write a line to the lcd
		@param line The line to be written to
		@param text The text to be written
		@param moveText If true the current text is moved to the right else it is overwritten
		*/
		void WriteLine(int line, std::string& text, bool moveText = false);
	};
}

#endif
