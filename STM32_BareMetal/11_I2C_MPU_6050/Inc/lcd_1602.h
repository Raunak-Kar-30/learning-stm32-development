#ifndef INC_LCD_1602_H_
#define INC_LCD_1602_H_

// Pins used : 	PB7 - D7
//				PB6 - D6
//				PB5 - D5
//				PB4 - D4
//				PB3 - EN
//				PB2 - RW
//				PB1 - RS
//
// Works Successfully !!!

// Includes
#include "main.h"

// Defines

// Clock accesses
#define GPIOB_CLK_EN	(1UL << 1)
// Pins
#define D7_PIN			(1UL << 7)
#define D6_PIN			(1UL << 6)
#define D5_PIN			(1UL << 5)
#define D4_PIN			(1UL << 4)
#define EN_PIN			(1UL << 3)
#define RW_PIN			(1UL << 2)
#define RS_PIN			(1UL << 1)

// Function declarations
void lcd_1602_pins_init();
void lcd_1602_start();
void lcd_1602_command(char command);
void lcd_1602_write(char message);

#endif /* INC_LCD_1602_H_ */
