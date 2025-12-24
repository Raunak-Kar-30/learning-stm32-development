#ifndef TIMER_H_
#define TIMER_H_

// Includes
#include "stm32f4xx.h"
#include "usart.h"

// Defines
#define TIM2_CLK_EN				(1UL << 0)
#define TIM2_CH2_PRELOAD_EN		(1UL << 11)
#define TIM2_CH2_OC_EN			(1UL << 4)
#define TIM2_COUNTER_EN			(1UL << 0)

// Function declarations
void timer2_setup_adc(int sys_freq);

#endif /* TIMER_H_ */
