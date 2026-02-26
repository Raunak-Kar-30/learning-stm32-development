// Simple program to blink the external LED (connected to PA6) using F446RE

// Includes
#include <stm32f4xx.h>

// Defines
#define SYS_FREQ		16000000
#define GPIOA_CLK_EN	(1UL << 0)
#define SYSTICK_EN		(1UL << 0)
#define SYSTICK_CNT		(1UL << 16)
#define SYSTICK_CLK_INT	(1UL << 2)

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
		/*
		// Toggle LED using the ODR (output data register)
		GPIOA->ODR |= (1UL << 5);
		delay_ms(1000);
		GPIOA->ODR &= ~(1UL << 5);
		delay_ms(1000);*/

		// Toggle LED using the BSRR (bit set/reset register)
		GPIOA->BSRR |= (1UL << 5);
		delay_ms(1000);
		GPIOA->BSRR |= (1UL << (5+16));
		delay_ms(1000);
	}

	return 0;
}

// Delay in micro-seconds
void delay_ms(int ms)
{
	// Disable the Sytick timer
	SysTick->CTRL &= ~(SYSTICK_EN);

	// Load the max value in Systick Load register and clear the current value register.
	SysTick->LOAD = (SYS_FREQ / 1000) - 1;
	SysTick->VAL = 0;

	// Select the correct clock source and enable the timer
	SysTick->CTRL |= SYSTICK_CLK_INT;
	SysTick->CTRL |= SYSTICK_EN;

	// Delay
	for(int i = 0; i < ms; i++)
	{
		while(!(SysTick->CTRL & SYSTICK_CNT));
		SysTick->CTRL &= ~(SYSTICK_CNT);
	}
}
