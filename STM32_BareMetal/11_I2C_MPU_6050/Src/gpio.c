//
// Driver program for controlling all the required GPIOs
//

// Includes
#include "gpio.h"

// Function declarations (private)

// Functions
//
// I2C GPIO initialization.
// Pins PB8 is being used as I2C1_SCL and PB9 as I2C1_SDA
void gpio_i2c1_init(void)
{
	// Enable clock access to GPIOB
	RCC->AHB1ENR |= GPIOB_CLK_EN;

	// Set PB8 and PB9 to alternate function mode
	GPIOB->MODER |= (1UL << 17 | 1UL << 19);
	GPIOB->MODER &= ~(1UL << 16 | 1UL << 18);

	// Set the output type to open drain
	GPIOB->OTYPER  |= (1UL << 8 | 1UL << 9);

	// Enable pull up for these pins
	GPIOB->PUPDR |= (1UL << 16 | 1UL << 18);
	GPIOB->PUPDR &= ~(1UL << 17 | 1UL << 19);

	// Set the alternate function registers to AFR4
	GPIOB->AFR[1] |= (1UL << 2 | 1UL << 6);
	GPIOB->AFR[1] &= ~(1UL << 0 | 1UL << 1 | 1UL << 3 | 1UL << 4 | 1UL << 5 | 1UL << 7);
}
