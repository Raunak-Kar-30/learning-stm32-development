/**
 ******************************************************************************
 * @file : main.c
 * @author : Raunak Kar
 * @brief : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2026 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 *
 * Simple program to blink an LED multiple times a second and generate an interrupt every time the on-board button is pressed.
 * This is just a practice program and is no way related to course material of Valvano
 *
 ******************************************************************************

 */

// Includes
#include <stm32f4xx.h>

// Defines

#define GPIOA_CLK_EN (1UL << 0)
#define GPIOC_CLK_EN (1UL << 2)
#define SYSCFG_CLK_EN (1UL << 14)
#define LED_PIN_EN (1UL << 5)
#define SYS_FREQ 16000000
#define CLK_SRC_INT (1UL << 2)
#define SYSTICK_EN (1UL << 0)
#define SYSTICK_CNT (1UL << 16)
#define EXTI_LINE_13 (1UL << 13)
// Function declarations (private)
void delay_ms(int ms);
void usr_btn_init_IT(void);
void EXTI13_Callback(void);

// Main
int main(void)
{
	// Clock source - internal 16 MHz oscillator
	// Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOA_CLK_EN;

	// Set GPIO A, Pin 5 to output mode
	GPIOA->MODER |= (1UL << 10);
	GPIOA->MODER &= ~(1UL << 11);

	// Intialize the button with interrupts.
	usr_btn_init_IT();
	GPIOA->BSRR |= (1UL << 5);
	while (1)
	{
		// Toggle the output of the LED via the BSRR register
		if (GPIOA->ODR & (1UL << 5)) GPIOA->BSRR |= (1UL << (5 + 16));
		else GPIOA->BSRR |= (1UL << 5);
		delay_ms(5000);
	}
}

// Initialize button to generate button every time it is pressed.
void usr_btn_init_IT(void)
{
	// Disable all interrupts globally
	__disable_irq();

	// Provide clock access to the button port and SYSCFG (system configuration)
	RCC->AHB1ENR |= GPIOC_CLK_EN;
	RCC->APB2ENR |= SYSCFG_CLK_EN;

	// Set PC 13 to GPIO input
	GPIOC->MODER &= ~(1UL << 26);
	GPIOC->MODER &= ~(1UL << 27);

	// Set the PA 13 to pull-up mode
	GPIOC->PUPDR |= (1UL << 26);
	GPIOC->PUPDR &= ~(1UL << 27);

	// Enable EXTI13 for GPIOC in SYSCFG_EXTICR4 register
	SYSCFG->EXTICR[3] &= 0xFF0F; // Reset bits 4-7 to clear EXTI13 line keeping all other bits same
	SYSCFG->EXTICR[3] = (1UL << 5);

	// Unmask EXTI 13
	EXTI->IMR |= (1UL << 13);

	// Since our button is set to pull-up mode, so PC13 line stays high by default and is pulled low when button is pressed
	// To detect button press and turn on LED, we must hence detect falling edge and not rising edge.
	EXTI->FTSR |= (1UL << 13);

	// Enable interrupt request handling for EXTI 13 in NVIC
	NVIC_EnableIRQ(EXTI15_10_IRQn);

	// Enable all IRQs globally
	__enable_irq();
}

// Interrupt service routine for EXTI13
// This service routine will not execute any code other than detecting the EXTI line (15 - 13) and calling the callback
// function accordingly
void EXTI15_10_IRQHandler(void)
{
// Check if pending register is set for EXTI13, meaning that the interrupt has not been handled yet
// If pending bit for EXTI 13 is set in pending register (PR), clear the pending bit and execute the callback function
	if (EXTI->PR & EXTI_LINE_13)
		EXTI->PR |= (EXTI_LINE_13);

	// Callback function
	EXTI13_Callback();
}

// EXTI callback function
void EXTI13_Callback(void)
{
	// If LED on, turn the LED off and vice versa
	if (GPIOA->ODR & (1UL << 5))
		GPIOA->BSRR |= (1UL << (5 + 16));
	else
		GPIOA->BSRR |= (1UL << 5);
}

// Systick delay
void delay_ms(int ms)
{
	// We want a 1 ms delay. Dividing the system frequency by 1000 gives us that
	SysTick->LOAD = (SYS_FREQ / 1000) - 1;

	// Clear the Systick current value register
	SysTick->VAL = 0;

	// Select the Systick clock source as the internal clock source for systick
	SysTick->CTRL |= CLK_SRC_INT;

	// Enable the systick timer
	SysTick->CTRL |= SYSTICK_EN;

	// Milli-second delay
	for (int i = 0; i < ms; i++)
	{
		// Wait until count flag is set
		while (!(SysTick->CTRL & SYSTICK_CNT));
		SysTick->CTRL &= ~(SYSTICK_CNT);
	}
}

