#ifndef USART_H_
#define USART_H_

// Includes
#include "main.h"
#include "gpio.h"

// Defines
#define USART2_CLK_EN	(1UL << 17)
#define USART2_EN		(1UL << 13)
#define USART2_TX_EN	(1UL << 3)
#define USART2_RX_EN	(1UL << 2)
#define USART2_TXE		(1UL << 7)
#define USART2_RXNE		(1UL << 5)

// Function declarations (public)
void usart2_init(void);
char usart2_read(void);

#endif /* USART_H_ */
