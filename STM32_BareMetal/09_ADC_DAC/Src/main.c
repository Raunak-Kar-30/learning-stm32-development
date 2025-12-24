// Program to learn and test ADC and DAC concepts and interfacing

// Includes
#include <stdio.h>
#include <stdlib.h>
#include "stm32f4xx.h"
#include "usart.h"
#include "timer.h"
#include "adc_conversion.h"

// Defines

// Function declarations
char *int_to_string(int data);

// Main function
int main(void)
{
	// Initialize USART2 module for writing the ADC converted value to USART2 TX.
	usart2_init();

	// Initialize ADC to start conversion
	adc1_temp_conv_init();

	// Start converion - in continuous conversion mode on channel 18
	adc1_start_conversion();

	// Clear the terminal and print something to the USART Terminal
	usart2_write("\e[1;1H\e[2J");
	usart2_write("Temp conversion using on-board ADC using STM32");

	// Keep reading data from the temp-sensor, and print the data to USART2
	while(1)
	{
		// Read the data from the ADC1 Data Register
		int data = adc1_read();

		// Convert the ADC output to Voltage read by the sensor (the reverse of what was done by ADC), because the Temp is calculated based on the voltage read.
		//
		// Now ref-voltage is 3.3V and resolution is 12 bit, and since we are using 12 bit resolution, so step_size = 3.3/4095 V
		// Now number of steps (which the variable 'data' represents) = (v_sensor / step_size), so => v_sensor = (data * step_size) = (data / 4095 * 3.3)
		// Formula : v_sensor = (step_size * number_of_steps) = (step_size * data) = (data / 4095 * 3.3)
		int v_sensor = data / 4095 * 3.3;

		// Convert the data read (which is expressed in terms of voltage) to readable temperature data.
		// For that we use the formula referred to in page 377 of (ref manual) RM0390.
		//
		// Formula according to RM0390 is => [Temp(deg Cel) = {(V_sensor - V_25) / Avg_slope} + 25].
		//
		// To get the values of V_25 and Avg_slope - refer datasheet DS10693 page 144.
		// According to data-sheet DS10693 : v_25 = 0.76 V and avg_slope = 2.5 mv/C = 0.0025 V/deg_C
		int temperature = ((v_sensor - 0.76) / 0.0025) + 25;

		// Print the raw data value and temp value to the terminal via USART.
		usart2_write("\n\rTemp : ");
		usart2_write(int_to_string(temperature));
		usart2_write("\n\rRaw Value : ");
		usart2_write(int_to_string(v_sensor));
		usart2_write("\n\r");
	}

	return 0;
}

// Convert the integer value to string, to print them via USART
char *int_to_string(int value)
{
	// Allocating some memory the size of an integer plus some extra (32 + 6 = 40), to store the integer data as character array.
	char *data = (char *)calloc(40, sizeof(char));

	// Calculate the length of the integer number (number of digits)
	int temp = value;
	int len = 0;
	while(temp > 0)
	{
		temp = temp / 10;
		len = len + 1;
	}

	for(int i = len-1; i >= 0; i--)
	{
		int rem = value % 10;
		value = value / 10;

		data[i] = rem + 48;
	}

	data[len] = '\0';

	return data;
}
