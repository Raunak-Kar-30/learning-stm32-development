// Main function for using and testing the systick timer
// Also involves the first usage of the High speed external clock as the system clock source

/*
 * Usage :
 * --------
 * We are currently using the 8MHz crystal from the ST-LINK instead of the 16MHz board crystal
 * To use the board crystal, see page 25 of User Manual of Nucleo board (UM1724)
 *
 * The systick timer can be controlled via the Systick Control and Status Register
 *
 * The Systick Reload Value Register holds the value that the systick timer will re-start counting from,
 * 	once it has counted down to zero, and the COUNTFLAG is set in the Control and Status Register
 *
 * The Systick Current Value Register holds the current value of the systick timer, this is the register we will be reading from
 * 	to get the current timer reading (maybe to initiate some event or count the time elapsed for an event)*/


// Includes
#include "stm32f4xx.h"

// Defines
#define GPIOA_CLK_EN	(1UL << 0)

// Function declarations
void systick_delay_ms(int ms);

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
	RCC->CFGR &= ~(1UL << 4 | 1UL << 5 | 1UL << 6 | 1UL << 7);


	if((RCC->CFGR & (1UL << 2)) && ((RCC->CFGR & (1UL << 3)) == 0))
	{
		// Provide clock access to GPIOA
		RCC->AHB1ENR |= GPIOA_CLK_EN;

		// Set the LED pin (PA5) to output mode
		GPIOA->MODER |= (1UL << 10);
		GPIOA->MODER &= ~(1UL << 11);

		// Configure the Systick timer
		// The Systick is a 24 bit timer. To get a frequency of 1 Hz, we set the load bit to 7999999 (0x7A11FF) to get a frequency of 8000000/8000000 = 1Hz
		// Set the clock source to system clock and enable the systick timer
		// We also the the clock source to system clock and enable the SysTick timer
		SysTick->LOAD  = 0x7A11FF;
		SysTick->CTRL = 0x5;

		int reg_read;

		// Super loop
		while(1)
		{
			// Method 1 of turning the LED on and off (crafty method, intelligent and useful in some cases)
			// -------------------------------------------------------------------------------------------
			// When the Systick timer is reset, the 23rd bit is 1 until all the remaining bits (0->22) go down to 0, this step takes 2^23 clock cycles
			// which is reached in roughly half the time (since it is half the frequency of 2^24 clock cycles). It then stays 0 until the remaining bits all go down to 0
			// This again taked 2^23 clock cycles. We AND the 23rd bit with the 5th bit of the LED so by bit shifting it to the 5th bit (or by 23-5 bits)
			// Thus turning the led on and off each second (i.e. the led stays on for 0.5 secs and off for 0.5 secs)
			//GPIOA->ODR = (SysTick->VAL >> (23-5)) & (1UL << 5);

			// Method 2 of turning the LED on and OFF (simpler and more precise)
			// -------------------------------------------------------------------
			// This check if the SysTick timer has completed one count and turns on the LED. This leads to the LED being turned on for 1 second and off for 1 second
			/*
			while(!(SysTick->CTRL & (1UL << 16)));
			GPIOA->ODR |= (1UL << 5);
			reg_read = SysTick->CTRL;	// Read the control register to clear the flag

			while(!(SysTick->CTRL & (1UL << 16)));
			GPIOA->ODR &= ~(1UL << 5);
			reg_read = SysTick->CTRL;	// Read the control register to clear the flag*/

			// Method 3 of turning the LED on and off using the custom systick delay function
			GPIOA->ODR |= (1UL << 5);
			systick_delay_ms(0.5);
			GPIOA->ODR &= ~ (1UL << 5);
			systick_delay_ms(1);
		}
	}

	return 0;
}

// Simple program to delay in milli-seconds using the systick timer
void systick_delay_ms(int ms)
{
	// Disable the timer if enabled
	if(SysTick->CTRL & (1UL << 0)) SysTick->CTRL &= ~(1UL << 0);

	// We set the Systick load value to 7999, so the systick timer counts from 7999 to 0 (8000 clock cycles).
	// Thus we get a timer of 8000/8000000 = 0.001 secs
	SysTick->LOAD = 0x1F3F;
	SysTick->CTRL |= (1UL << 0);		// Enable the timer

	int read_reg;
	for(int i = 0; i < ms; i++)
	{
		while(!(SysTick->CTRL & (1UL << 16)));
		SysTick->CTRL &= ~(1UL << 16);
	}
}
