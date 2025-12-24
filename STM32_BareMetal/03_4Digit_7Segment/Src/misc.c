// Source file containing all the miscellaneous functions

void delay_ms(int ms)
{
	for(int i = ms; i > 0; i--)
	{
		for(int j = 0; j < 1300; j++);
	}
}
