/*
 * Source file for initializing and communicating via USART
 */

// Includes
#include "usart.h"

// Function declarations (private) (delcared static)
static uint16_t compute_baudrate(uint32_t sys_freq, uint16_t baudrate);
static void usart2_write(char data);

// Functions

// Re-direct printf to usart2_write()
// Since this function takes data as integer and not as character we need to adjust accordingly
// to send to usart2_write() function which takes a character
int __io_putchar(int data)
{
	usart2_write((0xFF & data));
	return data;
}

// Initialize USART2
void usart2_init(void)
{
	// Enable clock access to USART2
	RCC->APB1ENR |= USART2_CLK_EN;

	// Initialize the USART pins
	usart2_gpio_init();

	// Set the desired baudrate
	USART2->BRR = compute_baudrate(sys_freq, 9600);

	// Set the transfer direction and enable USART
	// Oversampling (set to 16) and word-length (8 data bits) are set by default (0)
	USART2->CR1 |= USART2_TX_EN | USART2_RX_EN;
	USART2->CR1 |= USART2_EN;
}

// Compute the baudrate (don't know how this works yet)
// Since this is a local function, we declare it to be static
static uint16_t compute_baudrate(uint32_t sys_freq, uint16_t baudrate)
{
	return ((sys_freq + (baudrate / 2UL)) / baudrate);
}

// Write via USART to COM port
static void usart2_write(char data)
{
	// Wait till USART2 transmit data register is empty and data has moved to the shift register
	while(!(USART2->SR & USART2_TXE));

	// Write the data to the data register
	USART2->DR = data;
}

// Read a single byte of data from USART2
char usart2_read(void)
{
	// Wait until RXNE bit is set - i.e. data is yet in the shift register or is being processed
	while(!(USART2->SR & USART2_RXNE));

	// Read data from the data register
	return USART2->DR;
}
