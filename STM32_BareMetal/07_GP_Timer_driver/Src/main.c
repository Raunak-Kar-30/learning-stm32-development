// Main program to showcase the functionality of general purpose timers
// Incomplete - input capture, period and freq measurement, pulse counter -- remaining

// Includes
#include "stm32f4xx.h"
#include "timer.h"

// Defines
#define SYS_FREQ		8000000
#define GPIOA_CLK_EN	(1UL << 0)
#define LED_PIN			(1UL << 5)

// Main function
int main(void)
{
	// Enable the HSE clock (8MHz ST-LINK XTAL) and set it as the system clk
	RCC->CR |= (1UL << 16);				// Enable external clock
	while(!(RCC->CR & (1UL << 17)));	// Wait until the external clock is stable and the HSERDY flag is set
	RCC->CFGR |= (1UL << 0);			// Switch the system clock to HSE instead of HSI
	RCC->CFGR &= ~(1UL << 1);			// Disable the high speed internal clock
	RCC->CFGR &= ~(1UL << 7);			// Set the AHB prescaler to 1
	RCC->CFGR &= ~(1UL << 12);			// Set the APB1 prescaler to 1

	// If HSE is set execute the remaining program
	if((RCC->CFGR & (1UL << 2)) && ((RCC->CFGR & (1UL << 3)) == 0))
	{
		/*
		// Delay without the output compare functionality (polling UIF bit and much more in-efficient)
		// Initialize GPIOA for USR_LED
		RCC->AHB1ENR |= GPIOA_CLK_EN;
		GPIOA->MODER |= (1UL << 10);
		GPIOA->MODER &= ~(1UL << 11);

		while(1)
		{
			GPIOA->ODR |= LED_PIN;
			timer2_delay_ms(1000, SYS_FREQ);
			GPIOA->ODR &= ~(LED_PIN);
			timer2_delay_ms(1000, SYS_FREQ);
		}*/

		// Blink the LED using the Timer Output compare functionality, which makes it more cpu resourceful than the UIF polling method
		blink_led_using_tim2_ch1(1000, SYS_FREQ);
	}
}

