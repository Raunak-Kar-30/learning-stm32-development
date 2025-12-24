// Source file containing all the miscellaneous functions

// Includes
#include "misc.h"

void delay_ms(int ms)
{
	for(int i = ms; i > 0; i--)
	{
		for(int j = 0; j < 1300; j++);
	}
}
/*
// Blink the built in led certain number of times
void raise_error(int code)
{
	if(!(RCC->AHB1ENR & (1UL << 0))) RCC->AHB1ENR |= (1UL << 0);
	if(!(GPIOA->MODER & (1UL << 10))) GPIOA->MODER |= (1UL << 10);
	if(!(GPIOA->MODER & ~(1UL << 11))) GPIOA->MODER &= ~(1UL << 11);

	for(int i = 0; i < 5; i++)
	{
		for(int j = 0; j < code; j++)
		{
			GPIOA->ODR |= (1UL << 5);
			delay_ms(500);
			GPIOA->ODR &= ~(1UL << 5);
			delay_ms(500);
		}

		delay_ms(1000);
	}
}
*/
