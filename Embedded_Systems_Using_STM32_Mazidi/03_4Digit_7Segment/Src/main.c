// Program to interface with the 4 digit 7 segment display

// Includes
#include "stm32f4xx.h"
#include "seven_segment.h"
#include "misc.h"

// Main function
int main(void)
{
	// -- Main program --
	// Initialize the seven segment display pins
	seven_segment_init();

	// Write soemthing to the
	write_to_seven_segment("1234");

	return 0;
}
