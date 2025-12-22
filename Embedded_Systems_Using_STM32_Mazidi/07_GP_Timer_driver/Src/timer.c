// Driver program for the general purpose timers
// Incomplete - input capture, period and freq measurement, pulse counter -- remaining

// Includes
#include "timer.h"

// Function declarations (private)

// Function definitions
// Delay functionality using timers
void timer2_delay_ms(int ms, int sys_freq)
{
	// Enable clock access to the timer (if not already provided)
	if(!(RCC->APB1ENR & (TIMER2_CLK_EN))) RCC->APB1ENR |= TIMER2_CLK_EN;

	// The timer prescaler register is used to set the prescaler for the input clock source to the timer
	// Whatever the APB1 frequency is, the timer prescaler divides it by the value in the timer prescaler register
	// Assuming that both AHB1 and APB1 prescalers are 1 (no precaling i.e. APB1 freq = SYS_FREQ),
	// we can set the timer freq to 1MHz by setting the timer prescaler to sys_freq/1000000
	TIM2->PSC = (sys_freq / 1000000);

	// The Timer Auto Reload register (ARR) is the equivalent of the SysTick Load Value register
	// Since by default timers are up counters, so the timer starts counting from 0 to the value in the ARR
	// Since the timer runs at 1MHz, so to get a delay of 1ms, we set the ARR value to 999 (since 1000/1000000 = 0.001 secs or 1 ms)
	TIM2->ARR = 999;

	// The Timer Count Value register (CNT) is the equivalent of the SysTick Current Value register
	// To read the current value of the timer, we read the Count Value register
	TIM2->CNT = 0;					// Reset the timer counter

	// Enable the timer, leaving the update disable flag to 0 (i.e. enable update interrupt)
	TIM2->CR1 |= (1UL << 0);

	// Not a very efficient method of usage of CPU for delay. The cpu keeps polling the UIF flag until it is set, temporarily disabling the usage of the CPU -
	// in this time frame
	for(int i = 0 ;i < ms; i++)
	{
		// Wait until the UIF bit is set in the status register (update interrupt bit is set) indicating that one timer cycle has completed
		while(!(TIM2->SR & (1UL << 0)));
		TIM2->SR &= ~(1UL << 0);	// Clear the Update interrupt flag
	}
}

// Blink LED using timer 2 channel 1 using output compare functionality
void blink_led_using_tim2_ch1(int ms_delay, int sys_freq)
{
	// Here we do not poll for the timer's UIF bit to be set, as it is resourceful and the CPU cannot perform any operation -
	// while it waits for the UIF bit to be set (since it keeps on waiting until the bit is set).
	// Timer channels are pins or GPIOS connected to the timer, such that a signal is sent to that GPIO based on the output compare or input capture values.
	// Whenever the timer count becomes the same as the value in the Capture/Compare register, an interrupt is sent to the channel connected
	// to the timer (the channel for which the capture compare mode has been set-up).

	// Here we set the PA5 as the timer channel 1 of timer 2
	// To do so, we set PA5 to alternate function mode 1
	if(!(RCC->AHB1ENR & (GPIOA_CLK_EN))) RCC->AHB1ENR |= GPIOA_CLK_EN;
	if(!(RCC->APB1ENR & (TIMER2_CLK_EN))) RCC->APB1ENR |= TIMER2_CLK_EN;
	GPIOA->MODER &= ~(1UL << 10);
	GPIOA->MODER |= (1UL << 11);
	GPIOA->AFR[0] |= (1UL << 20);
	GPIOA->AFR[0] &= ~(1UL << 21 | 1UL << 22 | 1UL << 23);

	// Set the pre-scaler such that the timer has a frequency of 1MHz
	TIM2->PSC = (sys_freq / 1000000) - 1;

	// Set the auto-reload register to get a count every ms_delay ms
	TIM2->ARR  = (ms_delay * 1000) - 1;

	// Set the channel 1 of timer2 as output in capture/compare mode register 1
	// We also set the timer to toggle the output connected to channel 1 when the value in the CNT register = CCR1 (capture/compare register 1)
	// See page 558 of RM0390 (Ref manual)
	TIM2->CCMR1 &= ~(1UL << 0 | 1UL << 1);
	TIM2->CCMR1 |= (1UL << 4 | 1UL << 5);
	TIM2->CCMR1 &= ~(1UL << 6);

	// Set the Capture/compare 1 register with the value we want to compare the value in CNT register with, to initiate an output trigger
	// to the selected channel (channel 1 in our case) output pin (PA5)
	// Every timer had 4 channels, and so have 4 individual CCER registers (1,2,3,4), we use CCR1 (since we are using channel 1)
	// We set this to 0, whenever the timer counter (CNT) reaches from ARR value to 0, it will send the output signal to the channel output pin (PA5)
	TIM2->CCR1  = 0;

	// Enable the capture/compare mode using the capture/compare enable register 1 (since we are using channel 1)
	TIM2->CCER |= (1UL << 0);

	// Clear Timer counter register and enable the timer
	TIM2->CNT = 0;
	TIM2->CR1 |= (1UL << 0);
}
