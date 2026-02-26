//
// Driver program for 1602 LCD
//

// Includes
#include "lcd_1602.h"

// Function declarations (private)

// Functions
// Initiate the LCD
void lcd_1602_start()
{
	// For 4 bit init process refer page 46 of HD44780U

	// Initiate the pins needed for LCD data/command transmission.
	gpio_lcd_1602_init();

	// Clear the RW pin
	GPIOB->ODR &= ~(RW_PIN);

	// Send a series of commands, for starting the LCD in 4 bit mode.
	// After power on, wait for max 50 ms
	delay_ms(50);

	// Function set : Set to 8 bit mode, and wait for more than 4.1 ms
	lcd_1602_command(0x30);
	delay_ms(5);

	// Function set : Set to 8 bit mode (2nd try), and wait for more than 100us
	lcd_1602_command(0x30);
	delay_us(200);

	// Function set : Set to 8 bit mode (3rd try)
	lcd_1602_command(0x30);

	// From now on the delays after each command do not need to be mentioned explicitly and are handled by lcd_1602_command()
	// Function set : Set to 4 bit mode
	lcd_1602_command(0x20);

	// Function set : Set to 4 bit mode, 1 line(0) and font to 5x8(0)
	lcd_1602_command(0x28);

	// Display OFF
	lcd_1602_command(0x08);

	// Display Clear
	lcd_1602_command(0x01);

	// Entry mode set, increment set and no shift
	lcd_1602_command(0x06);

	// Turn on display and set cursor blinking
	lcd_1602_command(0x0F);

	// Init ends
}

// Send command to the LCD
void lcd_1602_command(char command)
{
	// Clear the ODR
	GPIOB->ODR &= ~(0xF0);

	// Clear the RS bit, to select the instruction register
	GPIOB->ODR &= ~(RS_PIN);

	// In 4 bit mode, transfer the higher 4 bits, then the lower 4 bits of command.
	// Load the ODR of GPIOB accordingly.
	//
	// Send the higher 4 bits first.
	GPIOB->ODR |= (command & 0xF0);

	// Enable clock pulse for sending the command
	GPIOB->ODR |= EN_PIN;
	delay_us(50);

	// Disable clock pulse
	GPIOB->ODR &= ~(EN_PIN);
	delay_us(50);

	// Clear the ODR
	GPIOB->ODR &= ~(0xF0);

	// Send the lower 4 bits.
	GPIOB->ODR |= ((command << 4) & 0xF0);

	// Enable clock pulse for sending the command
	GPIOB->ODR |= EN_PIN;
	delay_us(50);

	// Disable clock pulse
	GPIOB->ODR &= ~(EN_PIN);
	delay_us(50);

	// Delay for the appropriate time (refer page 24)
	if(command < 0x04) delay_ms(2);
	else delay_us(50);
}

// Write data to the LCD
void lcd_1602_write(char data)
{
	// Clear the ODR
	GPIOB->ODR &= ~(0xF0);

	// Enable the RS bit
	GPIOB->ODR |= RS_PIN;

	// In 4 bits mode, write the higher 4 bits, then the lower 4 bits of each byte of data.
	// Load the higher 4 bits into the ODR
	GPIOB->ODR |= (data & 0xF0);

	// Enable clock pulse
	GPIOB->ODR |= EN_PIN;
	delay_us(50);

	// Disable clock pulse
	GPIOB->ODR &= ~(EN_PIN);
	delay_us(50);

	// Clear the ODR
	GPIOB->ODR &= ~(0xF0);

	// Load the lower 4 bits into the ODR
	GPIOB->ODR |= ((data << 4) & 0xF0);

	// Enable clock pulse
	GPIOB->ODR |= EN_PIN;
	delay_us(50);

	// Disable clock pulse
	GPIOB->ODR &= ~(EN_PIN);
	delay_us(50);

	// Delay after each write
	delay_us(50);
}

