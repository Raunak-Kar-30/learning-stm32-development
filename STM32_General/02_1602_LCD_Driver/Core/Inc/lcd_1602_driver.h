// ==========================================================================================
//
// Driver file header containing the required declarations and definitions for using the 1602 LCD (without I2C module).
//
// The driver file has been written purely using CMSIS.
// HAL has not been used, since simple GPIO operations and register read/write operations would be too long and exhausting.
//
// Pin mappings : 	PB7 - D7
//					PB6 - D6
//					PB5 - D5
//					PB4 - D4
//					PB3 - EN
//					PB2 - R/W (can also be connected to ground)
//					PB1 - RS
//
// References : HD44780U Hitachi Data-sheet, Arduino LiquidCrystal source code (available on github)
//
// Author : Raunak Kar
//
// ==========================================================================================

#ifndef INC_LCD_1602_DRIVER_H_
#define INC_LCD_1602_DRIVER_H_

// Includes
#include <stdint.h>
#include "stm32f4xx.h"
#include "utils.h"

// Defines
//
// System Frequency
#ifndef SYS_FREQ
#define SYS_FREQ				16000000
#endif

// Pin states
#define LOW						0
#define HIGH					1

// The required bits to be turned on and off can be referenced from HD44780U Hitachi Data-sheet
// LCD control bits
#define LCD_EN_BIT				(1UL << 3)
#define LCD_RW_BIT				(1UL << 2)
#define LCD_RS_BIT				(1UL << 1)

// LCD commands - sets the kind of control we want. Control and setup must be done via the various Control flags(HD44780U - page 24)
#define LCD_CLEAR_DISPLAY		0x01
#define LCD_RETURN_HOME			0x02
#define LCD_ENTRY_MODE_SET		0x04
#define LCD_DISP_CONTROL		0x08
#define LCD_CURSOR_SHIFT		0x10
#define LCD_FUNCTION_SET		0x20
#define LCD_SET_CG_RAM_ADDRESS	0x40
#define LCD_SET_DD_RAM_ADDRESS	0x80

// Flags for setting the required/specified control bits of various commands
// We set the bit flags according to their postion in the 8 bit Command Register (to see the positions refer HD44780U page 24, 28 and 29)
//
// Flags for display entry mode - (HD44780U Page 26)
#define LCD_RIGHT_ENTRY			0x00
#define LCD_LEFT_ENTRY			0x02
#define LCD_ENTRY_SHIFT_INC		0x01
#define LCD_ENTRY_SHIFT_DEC		0x00

// Flags for display on/off control
#define LCD_DISPLAY_ON			0x04
#define LCD_DISPLAY_OFF			0x00
#define LCD_CURSOR_ON			0x02
#define LCD_CURSOR_OFF			0x00
#define LCD_BLINK_ON			0x01
#define LCD_BLINK_OFF			0x00

// Flags for display cursor shift
#define LCD_SHIFT_CURSOR		0x00
#define LCD_SHIFT_DISPLAY		0x08
#define LCD_SHIFT_LEFT			0x00
#define LCD_SHIFT_RIGHT			0x04

// Flags for function control
#define LCD_8_BIT_MODE			0x10
#define LCD_4_BIT_MODE			0x00
#define LCD_2_LINE_MODE			0x08
#define LCD_1_LINE_MODE			0x00
#define LCD_5x10_FONT			0x04
#define LCD_5x8_FONT			0x00

// Global variables
// Used to store the configurations of the LCD
uint8_t display_function_flags;
uint8_t display_control_flags;
uint8_t display_mode_flags;

uint8_t num_of_lines;
uint8_t row_offset;

uint8_t initialized;

// Function declarations
void lcd_1602_init(void);
void lcd_1602_send_command(char command);
void lcd_1602_send_data(char data);


#endif /* INC_LCD_1602_DRIVER_H_ */
