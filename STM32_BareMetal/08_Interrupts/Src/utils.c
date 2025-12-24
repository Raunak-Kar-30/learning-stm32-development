// Utility file containing all the utility functions

// Includes
#include "utils.h"

// Function declarations (private functions)

// Enable USR_LED (PA5)
void enable_usr_led(void)
{
	RCC->AHB1ENR |= (1UL << 0);
	GPIOA->MODER |= (1UL << 10);
	GPIOA->MODER &= ~(1UL << 11);
}

// Blink USR_LED n number of times (useful for testing or other functionalities)
void blink_usr_led(int times)
{
	enable_usr_led();

	for(int i = 0; i < times; i++)
	{
		GPIOA->BSRR |= (1UL << 5);
		systick_delay_ms(50);
		GPIOA->BSRR |= (1UL << (5+16));
		systick_delay_ms(50);
	}
}

// Simple program to delay in milli-seconds using the systick timer
void systick_delay_ms(int ms)
{
	// Disable the timer if enabled
	if(SysTick->CTRL & (1UL << 0)) SysTick->CTRL &= ~(1UL << 0);

	// We set the Systick load value to 7999, so the systick timer counts from 7999 to 0 (8000 clock cycles).
	// Thus we get a timer of 16000/16000000 = 0.001 secs
	SysTick->LOAD = 16000 - 1;
	SysTick->CTRL |= (1UL << 0);		// Enable the timer

	for(int i = 0; i < ms; i++)
	{
		while(!(SysTick->CTRL & (1UL << 16)));
		SysTick->CTRL &= ~(1UL << 16);
	}
}
