// ==========================================================================================
//
// Driver file containing the required functions for using the 1602 LCD (without I2C module).
//
// This file is written purely using CMSIS.
// HAL has not been used, since simple GPIO operations and register read/write operations would be too long and exhausting.
//
// Pin mappings : 	PB7 - D7
//					PB6 - D6
//					PB5 - D5
//					PB4 - D4
//					PB3 - EN
//					PB2 - R/W (can also be connected to ground)
//					PB1 - RS
//
// References : HD44780U Hitachi Data-sheet, Arduino LiquidCrystal source code (available on github)
//
// Author : Raunak Kar
//
// ==========================================================================================

// Includes
#include "lcd_1602_driver.h"

// Defines (Private)
#ifndef GPIOB_CLK_EN
#define GPIOB_CLK_EN	(1UL << 1)
#endif

// Function declarations (Private)
void lcd_1602_gpio_init(void);

// Driver functions
// Initialize the 1602 LCD
void lcd_1602_init(uint8_t eight_bit_mode, uint8_t cols ,uint8_t lines, uint8_t font)
{
	// Updated Program

	// Initialize the GPIO pins
	lcd_1602_gpio_init();

	// Set the control commands via the various control type and their respective flags to the display control variables
	// Basic initializations (in case we forget to set some important flags or functions), or if parameter values are illegal.
	display_function_flags |= (LCD_4_BIT_MODE | LCD_2_LINE_MODE | LCD_5x8_FONT);

	// Set 4 bit mode or 8 bit mode for function control
	if(eight_bit_mode) display_function_flags |= LCD_8_BIT_MODE;
	else display_function_flags |= LCD_4_BIT_MODE;

	// Set the number of lines and font resolution
	if(lines > 1) display_function_flags |= (LCD_2_LINE_MODE | LCD_5x8_FONT);
	else if(font) display_function_flags |= LCD_1_LINE_MODE | LCD_5x10_FONT;
	else display_function_flags |= LCD_1_LINE_MODE | LCD_5x8_FONT;

	// Initialization process begins - refer page 46 of HD44780U page 46
	//
	// After startup wait for 50 milli-seconds atleast (40 ms for VDD to read 2.7 V or 15 ms for VDD to read 4.5 V - so safe bet is 50 ms
	delay_ms(50);

	// Pull the RS and RW bits low to start writing commands
	GPIOB->BSRR |= (LCD_RS_BIT << 16);
	GPIOB->BSRR |= (LCD_RW_BIT << 16);

	// For 4 bit mode
	if(!(display_function_flags & LCD_8_BIT_MODE))
	{
		// We start in 8 bits trying to set 4 bit mode
		// Set function : set to 8 bit mode
		write_4_bits(LCD_FUNCTION_SET | LCD_8_BIT_MODE);
		delay_ms(5);

		// Try again
		// Set function : set to 8 bit mode
		write_4_bits(LCD_FUNCTION_SET | LCD_8_BIT_MODE);
		delay_ms(5);

		// Final try :-)
		// Set function : set to 8 bit mode
		write_4_bits(LCD_FUNCTION_SET | LCD_8_BIT_MODE);
		delay_ms(5);

		// Now lets set it to 4 bit interface
		// Set function : set to 4 bit mode
		write_4_bits(LCD_FUNCTION_SET | LCD_4_BIT_MODE);

		// Done :-)
	}

	// Set for 8 bit mode
	else
	{
		// No need to set to 8 bits here. We can set all function flags all at once
		// Set function commands along with all the flags set (and wait for more than 4.1 ms)
		lcd_1602_command(LCD_FUNCTION_SET | LCD_8_BIT_MODE);
		delay_ms(5);

		// second try
		// Set function : set to 8 bit mode
		lcd_1602_command(LCD_FUNCTION_SET | LCD_8_BIT_MODE);
		delay_us(150);

		// Third try, final try promise ...
		// Set function : set to 8 bit mode
		lcd_1602_command(LCD_FUNCTION_SET | LCD_8_BIT_MODE);

		// Done :-)
	}

	// Now set the other commands and their respective flags
	// Set the other function flags (num of lines, font)
	lcd_1602_command(LCD_FUNCTION_SET | display_function_flags);

	// Turn the display on without cursor blinking by default
	display_control_flags = (LCD_DISPLAY_ON | LCD_CURSOR_OFF | LCD_BLINK_OFF);
	lcd_1602_display_init();

	// Clear off
	lcd_1602_clear();

	// Set default display mode to start from left
	display_mode_flags |= (LCD_LEFT_ENTRY | LCD_ENTRY_SHIFT_DEC);
	lcd_1602_command(LCD_ENTRY_MODE_SET | display_mode_flags);
}

// Send command to the LCD
void lcd_1602_command(uint8_t command)
{
	lcd_1602_send(command, LOW);
}

// Write some data to the LCD
size_t lcd_1602_write(uint8_t data)
{
	send(data, HIGH);
	return 1;
}

// Send data/command to the LCD -- Private function
void lcd_1602_send(uint8_t value, int rs_state)
{
	// Write the RS mode state
	if(rs_state) GPIOB->BSRR |= LCD_RS_BIT;
	else GPIOB->BSRR &= ~(LCD_RS_BIT);

	// Check bit mode (4 bit mode or 8 bit mode)
	if(display_function & LCD_8_BIT_MODE) write_8_bits(value);
	else
	{
		// First write the higher 4 bits (by bit shifting them), then the lower 4 bits
		write_4_bits(value >> 4);
		write_4_bits(value);
	}
}

// Clear function -- Public Function
void lcd_1602_clear(void)
{
	// Clears the display, and sets the DDRAM address to 0 in the address counter (so cursor goes to 0)
	// Clearing the display takes atleast 1.52 ms
	lcd_1602_command(LCD_CLEAR_DISPLAY);
	delay_ms(2);
}

// Make the cursor go back to the starting position, without clearing the display
void lcd_1602_return_home(void)
{
	// DDRAM contents are not cleared (so contents on screen still remain), but set the address counter to 0,
	// which makes the cursor return to the starting postion
	// Returning to home takes atleast 1.52 ms
	lcd_1602_command(LCD_RETURN_HOME);
	delay_ms(2);
}

// Various settings based functions for the LCD.
// Set the cursor, to a custom position
void lcd_1602_set_cursor(int col, int row)
{
	const size_t max_lines = sizeof(row_offsets) / sizeof(*row_offsets);
}

// Initialize the GPIO for the LCD
void lcd_1602_gpio_init(void)
{
	// Enable clock access to GPIOB
	RCC->AHB1ENR |= GPIOB_CLK_EN;

	// Set the mode of the desired pins to output push-pull mode (set all bits to 0)
	GPIOB->MODER |= (1UL << 14 | 1UL << 12 | 1UL << 10 | 1UL << 8 | 1UL << 6 | 1UL << 4 | 1UL << 2);
	GPIOB->MODER &= ~(1UL << 15 | 1UL << 13 | 1UL << 11 | 1UL << 9 | 1UL << 7 | 1UL << 5 | 1UL << 3);
	GPIOB->OTYPER = 0;
}
