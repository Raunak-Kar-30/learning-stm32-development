/*
 * main.h
 *
 *  Created on: Dec 10, 2025
 *      Author: raunak-kar
 */

#ifndef USART_H_
#define USART_H_

// Includes
#include "stm32f4xx.h"
#include "misc.h"
#include <string.h>

// Defines
#define GPIOA_CLK_EN	(1UL << 0)
#define USART2_CLK_EN	(1UL << 17)
#define USART2_EN		(1UL << 13)

// Function declarations (global functions)
void usart2_init();
void usart2_write(char *data);
char usart2_read();

#endif /* USART_H_ */
