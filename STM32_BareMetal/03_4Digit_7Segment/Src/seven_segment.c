// Driver program for seven segment display

// Includes
#include "seven_segment.h"

// Defines
#define GPIOC_CLK_EN	(1UL << 2)
#define GPIOB_CLK_EN	(1UL << 1)
#define GPIOA_CLK_EN	(1UL << 0)

// Function declarations
void show_error(int code);

// Initialization function
void seven_segment_init()
{
	RCC->AHB1ENR |= 2;
	RCC->AHB1ENR |= 4;
	GPIOC->MODER &= ~0x0000FFFF;
	GPIOC->MODER |= 0x00005555;
	GPIOB->MODER &= ~0x000000FF;
	GPIOB->MODER |= 0x00000055;
	GPIOA->MODER |= (1UL << 10);
	GPIOA->MODER &= ~(1UL << 11);
}

void test_seven_segment()
{
	// Runs a simple test program to check if the display is setup properly
	while(1)
	{
		GPIOC->ODR = 0x0067;
		//GPIOB->BSRR = (1UL << 17 | 1UL << 16);
		//GPIOB->BSRR = (1UL << 1);
		GPIOB->ODR = 0x00;
		GPIOB->ODR |= (1UL << 0);
		delay_ms(1000);

		GPIOC->ODR = 0x0077;
		//GPIOB->BSRR = (1UL << 17);
		//GPIOB->BSRR = (1UL << 1 || 1UL << 0);
		GPIOB->ODR = 0x00;
		GPIOB->ODR |= (1UL << 1);
		delay_ms(1000);
	}
}

// Write something to the seven segment display
void write_to_seven_segment(char *string)
{
	int len = strlen(string);
	if(string[len-1] == '\n')
	{
		string[len-1] = '\0';
		len = len - 1;
	}

	// If the length of the string is more than 4 then send an error message to the seven segment display
	if(len > 4)
	{
		// Send "ERR" to the seven-segment-display
		show_error(3);
		exit(1);
	}

	// char array for holding the binary data to be writen
	char data[4];
	for(int i = 0; i < len; i++)
	{
		// If all characters are valid, get the binary equivalent
		if((string[i] >= 'A' && string[i] <= 'F') || (string[i] >= '0' && string[i] <= '9'))
		{
			for(int j = 0; j < NUM_OF_DISP_CHARS; j++)
			{
				if(string[i] == characters[j])
				{
					data[i] = hex_values[j];
					break;
				}
			}
		}

		// If lower case then convert to upper case, and get the binary equivalent
		else if(string[i] >= 'a' && string[i] <= 'f')
		{
			string[i] = string[i] - 32;
			for(int j = 0; j < NUM_OF_DISP_CHARS; j++)
			{
				if(string[i] == characters[j])
				{
					data[i] = hex_values[j];
					break;
				}
			}
		}

		// Else display nothing
		else
		{
			show_error(4);
			data[i] = 0x00;
		}
	}

	while(1)
	{
		// To turn on each digit, we need to set the respective pin to low (0)
		// This is because for any LED to turn on it's cathode must be at a lower voltage than it's anode.
		// Since 5461AS is a common cathode display, that means that the digit pins are connected to the cathode
		// Now to turn the a digit on, we need to pull the respective cathode low, and so clear the respective digit pin .
		// Now we switch between each of the characters fast to give an illusion of showing multiple characters
		GPIOC->ODR = data[0];
		GPIOB->ODR = 0x0F;
		GPIOB->ODR &= ~(1UL << 0);
		delay_ms(5);

		GPIOC->ODR = data[1];
		GPIOB->ODR = 0x0F;
		GPIOB->ODR &= ~(1UL << 1);
		delay_ms(5);

		GPIOC->ODR = data[2];
		GPIOB->ODR = 0x0F;
		GPIOB->ODR &= ~(1UL << 2);
		delay_ms(5);

		GPIOC->ODR = data[3];
		GPIOB->ODR = 0x0F;
		GPIOB->ODR &= ~(1UL << 3);
		delay_ms(5);
	}
}

// Error LED
void show_error(int code)
{
	for(int i = 0 ; i < 5; i++)
	{
		for(int j = 0; j <= code; j++)
		{
			GPIOA->ODR ^= (1UL << 5);
			delay_ms(500);
		}

		delay_ms(2000);
	}
}
