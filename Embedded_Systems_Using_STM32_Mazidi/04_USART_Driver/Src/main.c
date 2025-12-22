// Program to send and recieve data from the computer via USART

// Includes
#include "stm32f4xx.h"
#include "usart.h"
#include "misc.h"

// Defines
#define GPIOA_CLK_EN	(1UL << 0)

// Function declarations

// Main function
int main(void)
{
	// Enable the external clock and provide clock access to the LED pin
	// We enable the external clock by setting the HSEON bit in RCC_CR (Clock control register)
	// Until the HSE is stabilized and ready (HSERDY - HSE ready bit is set in the RCC_CR register) we wait
	// We then choose the external clock as the clock source in the clock configuration register, by setting the SW (system clock switch bits to 01)
	RCC->CR |= (1UL << 16);				// Enable the external clock
	while(!(RCC->CR & (1UL << 17)));	// Wait until the exteral clock is ready

	RCC->CFGR |= (1UL << 0);			// Switch the system clock to use the external oscillator (HSE)
	RCC->CFGR &= ~(1UL << 1);


	if((RCC->CFGR & (1UL << 2)) && (RCC->CFGR & ~(1UL << 3)))
	{

		// Enable clock access to GPIOA
		RCC->AHB1ENR |= (1UL << 0);

		// Set the output pin for LED
		GPIOA->MODER |= (1UL << 10);
		GPIOA->MODER &= ~(1UL << 11);

		usart2_init();

		while(1)
		{
			// Transmit something to the PC via USART
			usart2_write("\n\rHello my name is Raunak Kar");
			delay_ms(1000);
			usart2_write("\n\rThis is a message from stm32f446re\n\r");
			delay_ms(1000);
/*
			// Read some data from the PC via USART
			char data = usart2_read();
			if(data >= '0' && data <='9')
			{
				for(int i = 0; i < data-48; i++)
				{
					GPIOA->ODR |= (1UL << 5);
					delay_ms(500);
					GPIOA->ODR &= ~(1UL << 5);
					delay_ms(500);
				}
			}*/
		}
	}
}
