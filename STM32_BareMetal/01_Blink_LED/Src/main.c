// Simple program to blink the external LED (connected to PA6) using F446RE

// Includes
#include <stm32f4xx.h>

// Defines
#define GPIOA_CLK_EN	(1UL << 0)

// Function declarations
void delay_ms(int ms);

// Main functions
int main(void)
{
	// Enable clock access to the pin PA5
	RCC->AHB1ENR |= GPIOA_CLK_EN;

	// Set the pin PA6 to output mode and set it to push-pull
	GPIOA->MODER |= (1UL << 10);
	GPIOA->MODER &= ~(1UL << 11);
	GPIOA->OTYPER &= ~(1UL << 5);	// Not needed, since it is the default reset state, coded in just to show the functionality.

	// Super loop
	while(1)
	{
		// Toggle LED using the ODR (output data register)
		GPIOA->ODR |= (1UL << 5);
		delay_ms(1000);
		GPIOA->ODR &= ~(1UL << 5);
		delay_ms(1000);

		// Toggle LED using the BSRR (bit set/reset register)
	}

	return 0;
}

// Delay in micro-seconds
void delay_ms(int ms)
{
	for(int i = ms; i > 0; i--)
	{
		for(int j = 0; j < 1300; j++);
	}
}
