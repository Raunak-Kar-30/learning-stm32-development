/*
 * utils.h
 *
 *  Created on: 26-Dec-2025
 *      Author: raunak_kar
 */

#ifndef INC_UTILS_H_
#define INC_UTILS_H_

// Includes
#include "stm32f4xx.h"

// Defines
#define SYSTICK_SYS_CLK_SRC		(1UL << 2)
#define SYSTICK_TICKINT_EN		(1UL << 1)
#define SYSTICK_EN				(1UL << 0)
#define SYSTICK_CNT_FLAG_SET	(1UL << 16)

// Function Declarations
void systick_init(int sys_freq, int load_val);
void delay_ms(uint64_t sys_freq, int ms);
void delay_us(uint64_t sys_freq, int us);
void usr_led_init(void);

#endif /* INC_UTILS_H_ */
