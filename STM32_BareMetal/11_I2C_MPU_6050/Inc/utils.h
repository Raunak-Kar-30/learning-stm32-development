#ifndef INC_UTILS_H_
#define INC_UTILS_H_

// Includes
#include "main.h"

// Defines
// System
#ifndef SYS_FREQ
#define SYS_FREQ		16000000
#endif
// SysTick Timer
#define SYSTICK_CLK_INT	(1UL << 2)
#define SYSTICK_EN		(1UL << 0)
#define SYSTICK_CNT		(1UL << 16)

// Function declarations
void delay_ms(int ms);
void delay_us(int us);

#endif /* INC_UTILS_H_ */
