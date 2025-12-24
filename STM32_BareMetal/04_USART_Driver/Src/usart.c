// Driver program for USART2 of STM32F446RE

// Includes
#include "usart.h"

// Function declarations (local functions)

// Functions
void usart2_init()
{
	// Enable clock access to the USART2 peripheral
	if(!(RCC->APB1ENR & (USART2_CLK_EN))) RCC->APB1ENR |= (USART2_CLK_EN);
	if(!(RCC->AHB1ENR & (GPIOA_CLK_EN))) RCC->AHB1ENR |= (GPIOA_CLK_EN);

	// Set the GPIO pins to alternate mode for USART2 RX and TX
	// PA2 -> AF7 for USART2_TX and PA3-> AF7 for USART3_RX
	GPIOA->MODER &= ~(1UL << 4 | 1UL << 6);
	GPIOA->MODER |= (1UL << 5 | 1UL << 7);
	GPIOA->AFR[0] = 0x000;	// Clear the bits
	GPIOA->AFR[0] = 0x7700;	// Set the required bits

	// Disable the USART by clearing the USART enable bit in control register 1
	USART2->CR1 &= ~(USART2_EN);

	// Set the OVERSAMPLING rate (OVER8) (to 0), character size (to 0) and enable transmit and recieve in the control register 1
	USART2->CR1 = 0x000C;

	// Configure the STOP bits in USART 2 (generally we set it to 1 stop bit which is the default reset state) in control register 2
	// (Set tthe entire register to 0)
	USART2->CR2 = 0x0000;

	// Configure baud rate for USART 2
	// We first needed to have the system clock frequency (or leave it as default - 16MHz)
	// We then need to configure the OVER8 bit in the USART control register 1, according to which the baudrate will be determined
	// Finally we need to set the USARTDIV value to the BRR (Baud rate register) according to which the baudrate will be set
	// Formula : Desired USARTDIV = (Clock_freq/(8 * (2-OVER8)) * baud_rate)
	// Following the formula above, we set the variables accordingly to set the appropriate baud-rate
	USART2->BRR = 0x0043;

	// Configure control register 3 for disabling hardware flow control (set the entire register to 0)
	USART2->CR3 = 0x0000;

	// Once all the setup is done, enable USART by setting the USART enable bit in control register 1
	USART2->CR1 |= (USART2_EN);
}

void usart2_write(char *data)
{
	int len = strlen(data);

	// Send the entire data using a loop
	for(int i = 0; i < len; i++)
	{
		// Wait until the transmit empty (TXE) bit is set (data register empty, shift register full for transmitting data)
		while(!(USART2->SR & (1UL << 7)));

		// Write data[i] to the data register
		USART2->DR = data[i];
	}

	// Finally we check if the transfer complete bit is set (both data register and shift register are empty)
	if(USART2->SR & (1UL << 6)) return;
	/*else
	{
		raise_error(5);
		return;
	}*/
}

char usart2_read()
{
	// Wait for the RXNE bit to be set (data regsiter not empty and shift register is empty)
	while(!(USART2->SR & (1UL << 5)));
	return USART2->DR;
}
