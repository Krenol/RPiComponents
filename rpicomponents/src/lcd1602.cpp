#include "lcd1602.hpp"
#include <stdexcept>
#include <unistd.h>

namespace rpicomponents
{

	Lcd1602::Lcd1602(const Pcf8574& pcf) : Lcd(COMPONENT_LCD1602_LINES, COMPONENT_LCD1602_MAX_CHARS, COMPONENT_LCD1602_BITS, pcf, COMPONENT_LCD1602)
	{
		pcf_.WriteToPcfPin(lcd_pins_.rw - lcd_pins_.pinBase, 0);
		pcf_.WriteToPcfPin(lcd_pins_.led - lcd_pins_.pinBase, 1);
	}


	Lcd1602::Lcd1602(const Lcd1602& lcd) : Lcd1602(lcd.GetPcf())
	{
	}


	void Lcd1602::TurnOnBacklight()
	{
		pcf_.WriteToPcfPin(lcd_pins_.led - lcd_pins_.pinBase, 1);
	}

	void Lcd1602::TurnOffBacklight()
	{
		pcf_.WriteToPcfPin(lcd_pins_.led - lcd_pins_.pinBase, 0);
	}

	void Lcd1602::WriteLine(int line, std::string& text, bool moveText)
	{
		if (line < 0 || line >= COMPONENT_LCD1602_LINES) {
			throw new std::invalid_argument("LCD1602 only accepts line values between 0 and " + std::to_string(COMPONENT_LCD1602_LINES - 1));
		}

		LcdPosition(0, line);

		if (text.size() <= COMPONENT_LCD1602_MAX_CHARS && !moveText) {
			DisplayText(text);
		}
		else {
			std::string helper;
			while (text.size() > 0) {
				helper = text.substr(0, text.size() > COMPONENT_LCD1602_MAX_CHARS ? COMPONENT_LCD1602_MAX_CHARS : text.size());
				LcdClear();
				DisplayText(helper);
				text = text.erase(0, 1);
				usleep(sleep_);
			}
			LcdClear();
		}
	}
}