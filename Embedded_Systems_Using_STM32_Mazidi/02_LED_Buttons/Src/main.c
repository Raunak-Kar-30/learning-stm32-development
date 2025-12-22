// Simple program to blink the USR LED of the STM32 uC
// We are using an external LED (connected to PA6) and external push button (connected to PA5)

// Includes
#include <stm32f4xx.h>

// Defines
#define GPIOA_CLK_EN	(1UL << 0)
#define LED_PIN_HIGH	(1UL << 6)
#define BTN_PIN_HIGH	(1UL << 5)

// Function declarations
void delay_ms(int ms);

// Main functions
int main(void)
{
	// Enable clock access to the pin PA5
	RCC->AHB1ENR |= GPIOA_CLK_EN;

	// Set the pin PA6 to output mode and set it to push-pull
	GPIOA->MODER |= (1UL << 12);
	GPIOA->MODER &= ~(1UL << 13);
	GPIOA->OTYPER &= ~(1UL << 6);

	// Set PA5 to input mode and set the pin 5 to push pull mode
	// Since we connect the push-button to the ground, so the internal pull-up resistor is enabled (see Mazidi - Page 51)
	GPIOA->MODER &= ~(1UL << 10);
	GPIOA->MODER &= ~(1UL << 11);
	GPIOA->PUPDR |= (1UL << 10);
	GPIOA->PUPDR &= ~(1UL << 11);

	// Super loop
	while(1)
	{
		// Push buttons are active low - i.e. in active state (pushed state) it sends a low signal otherwise a high signal
		// So when PA6 recieves high signal (btn not pressed), PA5 is set to low and vice-versa
		if(GPIOA->IDR & (BTN_PIN_HIGH)) GPIOA->ODR &= ~(LED_PIN_HIGH);
		else GPIOA->ODR |= (LED_PIN_HIGH);
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
