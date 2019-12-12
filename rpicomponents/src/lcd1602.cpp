#include <lcd.h>
#include "lcd1602.hpp"
#include <stdexcept>


void rpicomponents::Lcd1602::Initialize() const
{
	if (lcdHandle_ == -1) {
		throw new std::invalid_argument("error while initializing lcd");
	}
	pcf_->WriteToPcfPin(lcdPins_.rw - lcdPins_.pinBase, 0);
	pcf_->WriteToPcfPin(lcdPins_.led - lcdPins_.pinBase, 1);
}

rpicomponents::Lcd1602::Lcd1602(int pcf_address, int pin_base) : Component(COMPONENT_LCD1602), pcf_{std::unique_ptr<Pcf8574>(new Pcf8574(pcf_address, pin_base))}, 
	lcdPins_{LcdPins(pin_base)}, lcdHandle_{ lcdInit(2, 16, 4, lcdPins_.rs, lcdPins_.en, lcdPins_.d4, lcdPins_.d5, lcdPins_.d6, lcdPins_.d7, 0, 0, 0, 0)}
{
	Initialize();
}

//rpicomponents::Lcd1602::Lcd1602(int&& pcf_address, int&& pin_base) : Component(COMPONENT_LCD1602), pcf_{ std::unique_ptr<Pcf8574>(new Pcf8574(pcf_address, pin_base)) },
//lcdPins_{ LcdPins(pin_base) }, lcdHandle_{ lcdInit(2, 16, 4, lcdPins_.rs, lcdPins_.en, lcdPins_.d4, lcdPins_.d5, lcdPins_.d6, lcdPins_.d7, 0, 0, 0, 0) }
//{
//	Initialize();
//}

rpicomponents::Lcd1602::Lcd1602(const Lcd1602& lcd) : Lcd1602(lcd.GetPcfAddress(), lcd.GetPcfBase())
{
}

int rpicomponents::Lcd1602::GetPcfBase() const
{
	pcf_->GetPinBase();
}

int rpicomponents::Lcd1602::GetPcfAddress() const
{
	pcf_->GetPcfAddress();
}

void rpicomponents::Lcd1602::TurnOnBacklight() const
{
	pcf_->WriteToPcfPin(lcdPins_.led - lcdPins_.pinBase, 1);
}

void rpicomponents::Lcd1602::TurnOffBacklight() const
{
	pcf_->WriteToPcfPin(lcdPins_.led - lcdPins_.pinBase, 0);
}

void rpicomponents::Lcd1602::WriteLine(int line, std::string text, bool moveText) const
{
	if (line < 0 || line >= lines_) {
		throw new std::invalid_argument("LCD1602 only accepts line values between 0 and " + std::to_string(lines_ - 1));
	}

	lcdPosition(lcdHandle_, 0, line);

	if (text.size() <= maxChars_ && !moveText) {
		lcdPrintf(lcdHandle_, text.c_str());
	}
	else {
		std::string helper;
		while (text.size() > 0) {
			helper = text.substr(0, text.size() > maxChars_ ? maxChars_ : text.size());
			lcdClear(lcdHandle_);
			lcdPrintf(lcdHandle_, helper.c_str());
			text = text.erase(0, 1);
			utils::Waiter::SleepMillis(sleepMs_);
		}
		lcdClear(lcdHandle_);
	}
}
