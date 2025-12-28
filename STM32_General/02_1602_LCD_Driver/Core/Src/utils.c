// Utitity file containing all the utility functions that could be used.

// Includes
#include "utils.h"

// Defines (Private)

// Function declarations (Private)

// Functions

// Initialize SysTick Timers.
void systick_init(int sys_freq, int load_val)
{
	// Disable SysTick if already enabled
	SysTick->CTRL &= ~(SYSTICK_EN);

	// Select clock source, disable Tick Interrupt in Control and Status Value Register
	SysTick->CTRL |= SYSTICK_SYS_CLK_SRC;
	SysTick->CTRL &= ~(SYSTICK_TICKINT_EN);

	// Set the reload value in the reload value register
	SysTick->LOAD = load_val - 1;

	// Set the Current Value Register to 0
	SysTick->VAL = 0;

	// Enable SysTick
	SysTick->CTRL |= SYSTICK_EN;
}

// SysTick delay function
void delay_ms(uint64_t sys_freq, int ms)
{
	// Disable SysTick if already enabled
	SysTick->CTRL &= ~(SYSTICK_EN);

	// Select clock source, disable Tick Interrupt in Control and Status Value Register
	SysTick->CTRL |= SYSTICK_SYS_CLK_SRC;
	SysTick->CTRL &= ~(SYSTICK_TICKINT_EN);

	// Set the reload value in the reload value register
	SysTick->LOAD = (sys_freq / 1000) - 1;

	// Set the Current Value Register to 0
	SysTick->VAL = 0;

	// Enable SysTick
	SysTick->CTRL |= SYSTICK_EN;

	// Wait for the desired number of milli-seconds
	for(int i = 0; i < ms; i++)
	{
		while(!(SysTick->CTRL & SYSTICK_CNT_FLAG_SET));
	}
}

// SysTick delay in micro-seconds
void delay_us(uint64_t sys_freq, int us)
{
	// Disable SysTick if already enabled
	SysTick->CTRL &= ~(SYSTICK_EN);

	// Select clock source, disable Tick Interrupt in Control and Status Value Register
	SysTick->CTRL |= SYSTICK_SYS_CLK_SRC;
	SysTick->CTRL &= ~(SYSTICK_TICKINT_EN);

	// Set the reload value in the reload value register
	SysTick->LOAD = (sys_freq / 1000000) - 1;

	// Set the Current Value Register to 0
	SysTick->VAL = 0;

	// Enable SysTick
	SysTick->CTRL |= SYSTICK_EN;

	// Wait for the desired number of milli-seconds
	for(int i = 0; i < us; i++)
	{
		while(!(SysTick->CTRL & SYSTICK_CNT_FLAG_SET));
	}
}

// Initialize USER LED
void usr_led_init(void)
{
	RCC->AHB1ENR |= (1UL << 0);

	GPIOA->MODER |= (1UL << 10);
	GPIOA->MODER &= ~(1UL << 11);
}
