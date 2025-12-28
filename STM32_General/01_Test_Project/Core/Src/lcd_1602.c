// Driver program for the 16x2 LCD display using HAL
//
// Pin mappings : 	PB7 - D7
//					PB6 - D6
//					PB5 - D5
//					PB4 - D4
//					PB3 - EN
//					PB2 - R/W (can also be connected to ground)
//					PB1 - RS
//
// Author : Raunak Kar

// Includes
#include "lcd_1602.h"

// Function declarations (private)

// LCD Display driver functions
// Initialize LCD
void lcd_1602_init(void)
{
	// Provide clock access to LCD Port (GPIO B)

	// We want to set the LED to 4 bit mode to reduce the number of pins

	// Set display to ON mode

	// Set the function bits - data length = 4 bits, Number of display lines = 2 line,

	// Clear the screen
}

// Send command to LCD
void lcd_1602_send_command(char data)
{
	// Set the appropriate pins connecting with the data pins (D7 to D4) and set the appropriate pins for sending instructions
	//
	// For instructions/commands :
	// 		R/W bit should always be set to 0
	//		EN bit should be set at the start of data/instruction transmission (EN bit provides the clock signal), and cleared after transmission
	// 		RS bit must always be set to 0

	// Divide the data into data-upper and data lower, and store them such that both data_upper and data_lowe hold the
	char data_upper = data & 0xF0;
	char data_lower = (data << 4) & 0xF0;

	// Write the data directly to the registers
	// Clear the GPIO B port ODR bits (this also clears the RS bit and so the RS line which sets the register to command register in the LCD)
	GPIOB->ODR  = 0;

	// First we explicitly write the EN bit by setting bit 3
	// data_upper & (0000 0000 1111 0000) ony gives us the bits 7,6,5,4 to be read and all other bits sent in data will be set to 0
	// Finally we clear the EN bit
	GPIOB->ODR |= LCD_SET_EN_bit;
	GPIOB->ODR = data_upper;
	GPIOB->ODR &= ~(LCD_SET_EN_bit);
}

// Sent data to LCD
void lcd_1602_send_data(char data)
{

}
