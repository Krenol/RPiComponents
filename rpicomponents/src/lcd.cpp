#include "lcd.hpp"
#include <unistd.h>
#include <pigpio.h>

namespace rpicomponents
{
    void Lcd::LcdInit() 
    {
		pcf_.WriteToPcfPin(lcd_pins_.rs, 0);
		gpioSetMode(lcd_pins_.rs, PI_OUTPUT);
		pcf_.WriteToPcfPin(lcd_pins_.en, 0);
		gpioSetMode(lcd_pins_.en, PI_OUTPUT);
		for(const auto& pin : data_pins_) {
			pcf_.WriteToPcfPin(pin, 0);
			gpioSetMode(pin, PI_OUTPUT);
		}
		usleep(t_sleep_);
        //init 4 or 8 bit LCD
		if(bits_ == 4) {
            Init4Bit();
        } else {
            Init8Bit();
        }
		// init multiple rows
		if(rows_ > 1) {
            InitMultiRow();
        }
		LcdDisplay(1);
		LcdCursor(0);
		LcdCursorBlink(0);
		LcdClear();
		SendCommand(LCD_ENTRY | LCD_ENTRY_ID);
		SendCommand(LCD_CDSHIFT | LCD_CDSHIFT_RL);
    }
    
    void Lcd::Init4Bit() 
    {
        unsigned char func = LCD_FUNC | LCD_FUNC_DL;
		for(int i = 0; i < 3; ++i){
			Send4BitCommand(func >> 4);
			usleep(t_sleep_);
		}
        func = LCD_FUNC;
        Send4BitCommand(func >> 4);
        usleep(t_sleep_);
    }
    
    void Lcd::Init8Bit() 
    {
        unsigned char func = LCD_FUNC | LCD_FUNC_DL;
		for(int i = 0; i < 3; ++i){
			SendCommand(func);
			usleep(t_sleep_);
		}
    }
    
    void Lcd::InitMultiRow() 
    {
        unsigned char func = LCD_FUNC | LCD_FUNC_DL;
        func |= LCD_FUNC_N;
		SendCommand(func);
		usleep(t_sleep_);
    }
    
    Lcd::~Lcd() 
    {
        
    }
    
    void Lcd::SendCommand(unsigned char cmd) 
    {
        pcf_.WriteToPcfPin(lcd_pins_.rs, 0);
		SendDataCommand(cmd);
		usleep(2000);
    }
    
    void Lcd::SendDataCommand(unsigned char data) 
    {
        unsigned char myData = data;
        if(bits_ == 4) {
            unsigned char d4 = (myData >> 4) & 0x0F;
            for(int i = 0; i < 4; ++i){
                pcf_.WriteToPcfPin(data_pins_[i], (d4 & 1));
                d4 >>= 1;
            }
            ToggleStrobe();
            d4 = myData & 0x0F ;
            for(int i = 0; i < 4; ++i){
                pcf_.WriteToPcfPin(data_pins_[i], (d4 & 1));
                d4 >>= 1;
            }
        } else {
            for(const auto& pin : data_pins_) {
                pcf_.WriteToPcfPin(pin, (myData & 1));
                myData >>= 1;
            }
        }
		ToggleStrobe();
    }
    
    void Lcd::Send4BitCommand(unsigned char cmd) 
    {
        unsigned char d4 = cmd ;
        pcf_.WriteToPcfPin(lcd_pins_.rs, 0);
        for(int i = 0; i < 4; ++i){
            pcf_.WriteToPcfPin(data_pins_[i], (d4 & 1));
            d4 >>= 1;
        }
        ToggleStrobe();
    }
    
    void Lcd::LcdPosition(int x, int y) 
    {
        if(x > cols_ || x < 0) return;
        if(y > rows_ || y < 0 || rows_ > row_offset_.size()) return;
        SendCommand (x + (LCD_DGRAM | row_offset_[y]));
        cx_ = x;
        cy_ = y;
    }
    
    void Lcd::DisplayText(const std::string& text) 
    {
        for(unsigned char c : text) {
            pcf_.WriteToPcfPin(lcd_pins_.rs, 1);
            SendDataCommand(c);
            if(++cx_ > cols_) {
                cx_ = 0;
                if(++cy_ == rows_) {
                    cy_ = 0;
                }
                SendCommand(cx_ + (LCD_DGRAM | row_offset_ [cy_]));
            }
        }
    }
    
    void Lcd::LcdClear() 
    {
        SendCommand(LCD_CLEAR);
		LcdHome();
    }
    
    void Lcd::LcdHome() 
    {
        SendCommand(LCD_HOME);
		cx_ = 0;
		cy_ = 0;
		usleep(5000);
    }
    
    void Lcd::LcdDisplay(bool state) 
    {
        state ? (lcd_control_ |= LCD_DISPLAY_CTRL) : (lcd_control_ &= ~LCD_DISPLAY_CTRL);
		SendCommand(LCD_CTRL | lcd_control_);
    }
    
    void Lcd::LcdCursor(bool state) 
    {
        state ? (lcd_control_ |= LCD_CURSOR_CTRL) : (lcd_control_ &= ~LCD_CURSOR_CTRL);
		SendCommand(LCD_CTRL | lcd_control_);
    }
    
    void Lcd::LcdCursorBlink(bool state) 
    {
        state ? (lcd_control_ |= LCD_BLINK_CTRL) : (lcd_control_ &= ~LCD_BLINK_CTRL);
		SendCommand(LCD_CTRL | lcd_control_);
    }
    
    void Lcd::ToggleStrobe() 
    {
        pcf_.WriteToPcfPin(lcd_pins_.en, 1);
		usleep(50000);
		pcf_.WriteToPcfPin(lcd_pins_.en, 0);
		usleep(50000);
    }
    
    Lcd::Lcd(int rows, int cols, int bits, const Pcf8574& pcf, const std::string& comp_name) : 
        Component(comp_name), lcd_pins_{LcdPins(pcf.GetPinBase())}, rows_{rows}, cols_{cols}, bits_{bits}, pcf_{pcf}
    {
        LcdInit();
    }

    const Pcf8574& Lcd::GetPcf() const
	{
		return pcf_;
	}

}