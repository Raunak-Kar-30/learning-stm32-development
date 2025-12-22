#ifndef UTILS_H_
#define UTILS_H_

// Includes
#include "stm32f4xx.h"

// Defines

// Function declarations (public)
void enable_usr_led(void);
void blink_usr_led(int times);
void systick_delay_ms(int ms);

#endif /* UTILS_H_ */
