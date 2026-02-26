//
// Simple program to run the 1602 LCD display.
// This is just a test program and cannot be used as a driver program for other programs.
//
// Pins used : 	PB7 - D7
//				PB6 - D6
//				PB5 - D5
//				PB4 - D4
//				PB3 - EN
//				PB2 - RW
//				PB1 - RS
//
// Works Successfully !!!

// Includes
#include <stm32f4xx.h>

// Defines
// System
#define SYS_FREQ		16000000
// Clock accesses
#define GPIOB_CLK_EN	(1UL << 1)
// SysTick Timer
#define SYSTICK_CLK_INT	(1UL << 2)
#define SYSTICK_EN		(1UL << 0)
#define SYSTICK_CNT		(1UL << 16)
// Pins
#define D7_PIN			(1UL << 7)
#define D6_PIN			(1UL << 6)
#define D5_PIN			(1UL << 5)
#define D4_PIN			(1UL << 4)
#define EN_PIN			(1UL << 3)
#define RW_PIN			(1UL << 2)
#define RS_PIN			(1UL << 1)

// Function declarations
void lcd_1602_pins_init();
void lcd_1602_start();
void lcd_1602_command(char command);
void lcd_1602_write(char message);
void delay_ms(int ms);
void delay_us(int us);

// Main
int main(void)
{
	// Start the LCD
	lcd_1602_start();

	// Write to LCD
	lcd_1602_write('H');
	lcd_1602_write('E');
	lcd_1602_write('L');
	lcd_1602_write('L');
	lcd_1602_write('O');
	lcd_1602_write(' ');
	lcd_1602_write('D');
	lcd_1602_write('U');
	lcd_1602_write('D');
	lcd_1602_write('E');

	while(1)
	{
	}
}

// Initiate the LCD
void lcd_1602_start()
{
	// For 4 bit init process refer page 46 of HD44780U

	// Initiate the pins needed for LCD data/command transmission.
	lcd_1602_pins_init();

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

// Initiate the pins for data transmission
void lcd_1602_pins_init()
{
	// Enable clock access to GPIOB
	RCC->AHB1ENR |= GPIOB_CLK_EN;

	// Set the modes of the pin to output mode
	GPIOB->MODER |= (1UL << 2 | 1UL << 4 | 1UL << 6 | 1UL << 8 | 1UL << 10 | 1UL << 12 | 1UL << 14);
	GPIOB->MODER &= ~(1UL << 3 | 1UL << 5 | 1UL << 7 | 1UL << 9 | 1UL << 11 | 1UL << 13 | 1UL << 15);
}

// Delay functions
// Milli-second delay
void delay_ms(int ms)
{
	// Initialize SysTick timer
	//
	// Reset the SysTick timer
	SysTick->CTRL = 0;

	// Set the clock source to system clock
	SysTick->CTRL |= SYSTICK_CLK_INT;

	// Set the Load Value Register
	SysTick->LOAD = (SYS_FREQ / 1000) - 1;

	// Reset the Current Value Register
	SysTick->VAL = 0;

	// Enable SysTick
	SysTick->CTRL |= SYSTICK_EN;

	// Loop till the desired time duration is reached
	for(int i = 0; i < ms; i++)
	{
		while(!(SysTick->CTRL & SYSTICK_CNT));
	}
}

// Micro-second delay
void delay_us(int us)
{
	// Initialize SysTick timer.
	//
	// Reset the SysTick timer.
	SysTick->CTRL = 0;

	// Set the clock source to system clock
	SysTick->CTRL |= SYSTICK_CLK_INT;

	// Set the Load Value Register
	SysTick->LOAD = (SYS_FREQ / 1000000) - 1;

	// Reset the Current Value Register
	SysTick->VAL = 0;

	// Enable SysTick
	SysTick->CTRL |= SYSTICK_EN;

	// Loop till the desired time duration is reached
	for(int i = 0; i < us; i++)
	{
		while(!(SysTick->CTRL & SYSTICK_CNT));
	}
}
