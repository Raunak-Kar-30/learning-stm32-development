/*
 * Source file for handling all the gpio configurations
 */

// Includes
#include "gpio.h"

// Function declarations (private)

// Functions
// USR_LED GPIO init
void usr_led_gpio_init(void)
{
	// Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOA_CLK_EN;

	// Set LED to output mode
	GPIOA->MODER |= (1UL << 10);
	GPIOA->MODER &= ~(1UL << 11);
}

// USART GPIO init
void usart2_gpio_init(void)
{
	// Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOA_CLK_EN;

	// Set the pins to alternate mode to AF7 for PA2 (USART2 TX) and PA3 (USART2 RX)
	GPIOA->MODER &= ~(1UL << 4 | 1UL << 6);
	GPIOA->MODER |= (1UL << 5 | 1UL << 7);

	// Reset the AF for desired pins in AFR Low register and set each pins to AF7
	GPIOA->AFR[0] &= 0xFFFF00FF;
	GPIOA->AFR[0] |= 0x00007700;
}
