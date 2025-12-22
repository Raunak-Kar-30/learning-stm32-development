#ifndef TIMER_H_
#define TIMER_H_

// Includes
#include "stm32f4xx.h"

// Defines
// If GPIOA_CLK_EN is not defined in main or other any file, define it
#ifndef GPIOA_CLK_EN
#define GPIOA_CLK_EN	(1UL << 0)
#endif

#define TIMER2_CLK_EN	(1UL << 0)

// Function declarations (public)
void timer2_delay_ms(int ms, int sys_freq);
void blink_led_using_tim2_ch1(int ms_delay, int sys_freq);

#endif /* TIMER_H_ */
