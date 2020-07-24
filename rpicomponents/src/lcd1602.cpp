#include <lcd.h>
#include "lcd1602.hpp"
#include <stdexcept>
#include "utils/utils.hpp"


void rpicomponents::Lcd1602::Initialize()
{
	if (lcdHandle_ == -1) {
		throw new std::invalid_argument("error while initializing lcd");
	}
	pcf_->WriteToPcfPin(lcdPins_.rw - lcdPins_.pinBase, 0);
	pcf_->WriteToPcfPin(lcdPins_.led - lcdPins_.pinBase, 1);
}

rpicomponents::Lcd1602::Lcd1602(std::unique_ptr<rpicomponents::Pcf8574> pcf) : Component(COMPONENT_LCD1602), pcf_{pcf}, 
	lcdPins_{LcdPins(pcf->GetPinBase())}, 
	lcdHandle_{ lcdInit(COMPONENT_LCD1602_LINES, COMPONENT_LCD1602_MAX_CHARS, COMPONENT_LCD1602_BITS, lcdPins_.rs, lcdPins_.en, lcdPins_.d4, lcdPins_.d5, lcdPins_.d6, lcdPins_.d7, 0, 0, 0, 0)}
{
	Initialize();
}


rpicomponents::Lcd1602::Lcd1602(const Lcd1602& lcd) : Lcd1602(lcd.GetPcf())
{
}

const std::unique_ptr<rpicomponents::Pcf8574>& rpicomponents::Lcd1602::GetPcf() const
{
	return pcf_;
}

void rpicomponents::Lcd1602::TurnOnBacklight() const
{
	pcf_->WriteToPcfPin(lcdPins_.led - lcdPins_.pinBase, 1);
}

void rpicomponents::Lcd1602::TurnOffBacklight() const
{
	pcf_->WriteToPcfPin(lcdPins_.led - lcdPins_.pinBase, 0);
}

void rpicomponents::Lcd1602::WriteLine(int line, std::string& text, bool moveText) const
{
	if (line < 0 || line >= COMPONENT_LCD1602_LINES) {
		throw new std::invalid_argument("LCD1602 only accepts line values between 0 and " + std::to_string(COMPONENT_LCD1602_LINES - 1));
	}

	lcdPosition(lcdHandle_, 0, line);

	if (text.size() <= COMPONENT_LCD1602_MAX_CHARS && !moveText) {
		lcdPrintf(lcdHandle_, text.c_str());
	}
	else {
		std::string helper;
		while (text.size() > 0) {
			helper = text.substr(0, text.size() > COMPONENT_LCD1602_MAX_CHARS ? COMPONENT_LCD1602_MAX_CHARS : text.size());
			lcdClear(lcdHandle_);
			lcdPrintf(lcdHandle_, helper.c_str());
			text = text.erase(0, 1);
			utils::Waiter::SleepMillis(sleepMs_);
		}
		lcdClear(lcdHandle_);
	}
}
