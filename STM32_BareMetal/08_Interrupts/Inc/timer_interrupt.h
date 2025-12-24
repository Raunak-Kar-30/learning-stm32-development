#ifndef TIMER_INTERRUPT_H_
#define TIMER_INTERRUPT_H_

// Includes
#include "stm32f4xx.h"

// Defines
#define TIM2_CLK_EN	(1UL << 0)

// Function declarations
void blink_led_timer_interrupt(void);

#endif /* TIMER_INTERRUPT_H_ */
