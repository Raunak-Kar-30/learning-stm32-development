// ==========================================================================================
//
// Main program containing various use-cases and exampled of the 16X2 LCD using the 1602 LCD driver
//
// Author : Raunak Kar
//
// ==========================================================================================

// Includes
#include "main.h"

// Function declarations

// Main function
int main(void)
{
	// Initialize the LCD and USR_LED
	usr_led_init();
	lcd_1602_init();

	// While
	while(1)
	{
		lcd_1602_send_data('h');
		lcd_1602_send_data('e');
		lcd_1602_send_data('l');
		lcd_1602_send_data('l');
		lcd_1602_send_data('o');

		// Test if the timer works correctly by blinking an LED
		GPIOA->ODR ^= (1UL << 5);
		delay_us(SYS_FREQ, 1000000);
	}
}

