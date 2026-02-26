/*
 * gpio.h
 *
 *  Created on: 13-Feb-2026
 *      Author: raunak_kar
 */

#ifndef GPIO_H_
#define GPIO_H_

// Includes
#include "main.h"

// Defines
#define GPIOA_CLK_EN	(1UL << 0)

// Function declarations
void usr_led_gpio_init(void);
void usart2_gpio_init(void);

#endif /* GPIO_H_ */
