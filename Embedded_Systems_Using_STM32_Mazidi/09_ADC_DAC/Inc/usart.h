#ifndef USART_H_
#define USART_H_

// Includes
#include "stm32f4xx.h"
#include <stdio.h>
#include <string.h>

// Defines
#define USART2_CLK_EN		(1UL << 17)
#define GPIOA_CLK_EN		(1UL << 0)
#define USART2_OVER8_EN		(1UL << 15)
#define USART2_TX_EN		(1UL << 3)
#define USART2_EN			(1UL << 13)
#define USART2_TXE			(1UL << 7)

// Function declarations
void usart2_init(void);
void usart2_write(char *data);

#endif /* USART_H_ */
