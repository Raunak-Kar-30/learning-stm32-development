/*
 * Source file for reading and generating morse code
 */

// Includes
#include "morse.h"

// Private defines
#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

// Globals (private)
uint16_t unit_ms = 0;
char data[2000] = {'\0'};
int init_flag = 0;

// Function declarations (private)
void morse_read(void);

// Functions
// Initialize morse code generator - Takes the time represented by 1 unit
void morse_init(uint16_t ms)
{
	// Initialize USART
	usart2_init();

	// Set the unit time to the given time
	unit_ms = ms;

	init_flag = 1;
}

// Automated script for executing entire morse program (can be used by programmer to test out the program
// or if they are lazy enough to not implement it themselves ;-) )
int morse_run(void)
{
	// Check if morse has been initialized
	if(!init_flag)
	{
		/*
		printf("Morse need to be initialized before morse_run() \n\r");
		printf("Initialize morse using morse_init() before morse_run() \r\n");*/

		strcpy(err_message, "Morse need to be initialized before morse_run() using morse_init() \n\r");
		return -1;
	}

	// Read morse input
	morse_read();

	// Generate the corresponding morse code

	return 0;
}

// Read the input to generate the appropriate morse command
void morse_read(void)
{
	// Clear the screen and print the prompt
	printf("\033[0;0H");
	printf("\033[2J");
	printf("$ >> ");
	fflush(stdout);	// Forces the items in the output stream to be written to stdout

	//fflush(stdout);

	char byte = '\0';
	int i = 0;
	while(1)
	{
		// Read one character from serial com port
		byte = usart2_read();

		if(byte == '\r' || byte == '\n') break;

		if(i < (ARRAY_SIZE(data) - 1))
		{
			data[i++] = byte;
			printf("%c", byte);
			fflush(stdout);
		}
	}

	// End the string
	data[i++] = '\0';

	printf("\r\n%s\r\n", data);
}

// Code generator - generates the code corresponding to the input text
void morse_code_gen(char *data)
{

}

// Outputs the morse code generated to the LED
void morse_output(void)
{

}
