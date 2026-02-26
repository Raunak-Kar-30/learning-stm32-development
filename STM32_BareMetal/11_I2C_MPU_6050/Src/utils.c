// Utility file

// Includes
#include "utils.h"

// Function declarations (private)

// Functions
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
