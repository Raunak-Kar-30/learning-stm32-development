#ifndef INC_GPIO_H_
#define INC_GPIO_H_

// Includes
#include "main.h"

// Defines
#define GPIOB_CLK_EN	(1UL << 1)

// Function declarations (public).
void gpio_lcd_1602_init(void);
void gpio_i2c1_init(void);

#endif /* INC_GPIO_H_ */
