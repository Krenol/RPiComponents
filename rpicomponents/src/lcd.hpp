#include "component.hpp"
#include <vector>
#include "pcf8574.hpp"

#ifndef RPICOMPONENTS_LCD_H
#define RPICOMPONENTS_LCD_H

// HD44780U Commands

#define	LCD_CLEAR	0x01
#define	LCD_HOME	0x02
#define	LCD_ENTRY	0x04
#define	LCD_CTRL	0x08
#define	LCD_CDSHIFT	0x10
#define	LCD_FUNC	0x20
#define	LCD_CGRAM	0x40
#define	LCD_DGRAM	0x80

// Bits in the entry register

#define	LCD_ENTRY_SH		0x01
#define	LCD_ENTRY_ID		0x02

// Bits in the control register

#define	LCD_BLINK_CTRL		0x01
#define	LCD_CURSOR_CTRL		0x02
#define	LCD_DISPLAY_CTRL	0x04

// Bits in the function register

#define	LCD_FUNC_F	0x04
#define	LCD_FUNC_N	0x08
#define	LCD_FUNC_DL	0x10

#define	LCD_CDSHIFT_RL	0x04

namespace rpicomponents {
	constexpr const char* COMPONENT_LCD = "lcd";

	struct LcdPins {
		LcdPins(int pinBase) : pinBase{ pinBase }, rs{ pinBase }, rw{pinBase + 1}, en{ pinBase + 2 }, led{pinBase + 3}, d4{ pinBase + 4 }, d5{ pinBase + 5 }, d6{ pinBase + 6 }, d7{ pinBase + 7 }
		{

		}

		LcdPins(const LcdPins& pins): pinBase{ pins.pinBase }, rs{ pins.rs }, rw{pins.rw}, en{ pins.en }, led{pins.led}, d4{ pins.d4 }, d5{ pins.d5 }, d6{ pins.d6 }, d7{ pins.d7 }
		{

		}
		int pinBase, rs, rw, en, led, d4, d5, d6, d7;
	};

	class Lcd : public Component
	{
    private:
        const useconds_t t_sleep_ = 35000;
        int cx_{0}, cy_{0}, lcd_control_;
		const std::vector<int> data_pins_, row_offset_{0x00, 0x40, 0x14, 0x54};
        const int rows_, cols_, bits_;

        /**
		 * Method to initalize the LCD
		 * Adapted from wiringPi
		 * @returns handle to the LCD; -1 on error
		 */
		void LcdInit();

        /**
         * Init 4 bit LCD
         */
        void Init4Bit();

        /**
         * Init 8 bit LCD
         */
        void Init8Bit();

        /**
         * Init multi row LCD
         */
        void InitMultiRow();

	protected:
		const LcdPins lcd_pins_;
		Pcf8574 pcf_;

        ~Lcd(); //virtual protected destructor to make class abstract

		/**
		 * Method to send a command to the LCD
		 * @param cmd The command to be send
		 */
		void SendCommand(unsigned char cmd);

        /**
		 * Method to send data 4 bit commands to the LCD
		 * @param data: The data to be send
		 */
		void Send4BitCommand(unsigned char cmd);

		/**
		 * Method to send data commands to the LCD
		 * @param data: The data to be send
		 */
		void SendDataCommand(unsigned char data);

        

		/**
		 * Move cursor on LCD in x and y direction (y = new line)
		 * @param x Move in x direction
		 * @param y Move in y direction
		 */
		void LcdPosition(int x, int y);
		
		/**
		 * Method to display text on LCD
		 * @param text The text to be displayed
		 */
		void DisplayText(const std::string& text);

		/**
		 * Method to clear the LCD
		 */
		void LcdClear();

		/**
		 * Method to move LCD cursor to home position
		 */
		void LcdHome();

		/**
		 * Method to turn the display on/off
		 * @param state: Bool if display is to be turned on (true) or off (false)
		 */
		void LcdDisplay(bool state);

		/**
		 * Method to turn the cursor on/off
		 * @param state: Bool if cursor is to be turned on (true) or off (false)
		 */
		void LcdCursor(bool state);

		/**
		 * Method to turn the cursor blinking on/off
		 * @param state: Bool if cursor blinking is to be turned on (true) or off (false)
		 */
		void LcdCursorBlink(bool state);

		/**
		 * Method to toggle the strobe pin
		 */
		void ToggleStrobe();

	public:
        /**
         * Init LCD
         * @param rows The number of rows of the display
         * @param cols The number of columns (chars per line) the display can handle
         * @param bits The bits of the display
         * @param pcf Pcf8574 uses for the LCD
         * @param comp_name The name of this component
         */
		Lcd(int rows, int cols, int bits, const Pcf8574& pcf, const std::string& comp_name);

		/*
		Method to get the pcf 

		@returns const ref to pcf 
		*/
		const Pcf8574& GetPcf() const;
	};
}

#endif
