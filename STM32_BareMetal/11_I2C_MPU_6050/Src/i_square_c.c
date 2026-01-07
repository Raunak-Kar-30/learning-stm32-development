// Driver program for the I2C module.

// Includes
#include "i_square_c.h"

// Function declarations (private)

// Functions
// Initialize the I2C module.
// The I2C 1 module uses pins PB8 for I2C1_SCL (clock line) and PB9 for I2C1_SDA (data line).
void i2c1_init(void)
{
	// Disable I2C
	I2C1->CR &= ~(I2C1_PERIPH_EN);

	// Initialize pins for I2C1
	gpio_i2c1_init();

	// Enable clock access to I2C module
	RCC->APB1ENR |= I2C1_CLK_EN;

	// Set I2C 1 to reset mode, then clear the reset bit.
	I2C1->CR1 |= I2C1_SW_RESET;
	I2C1->CR1 &= ~(I2C1_SW_RESET);

	// Set the peripheral clock frequency. Write 16 to FREQ bits in Control Register 2
	I2C1->CR2 |= (1UL << 4);
	I2C1->CR2 &= ~(1UL << 0 | 1UL << 1 | 1UL << 2 | 1UL << 3 | 1UL << 5);

	// Set I2C to standard mode
	I2C1->CCR |= ~(I2C1_FAST_MODE);

	// For 100KHz frequency, divide the sys_freq by 1 to get the time in nano-seconds, and multiply it with the appropriate
	// number such that the result is 5000.
	//
	// So if sys_freq is 16000000, then TIME period in nano-seconds = 62.5 ns, and multiplying it with 80 (0x50) gives 5000.
	// So set the value of CCR bits to 0x50 (80).
	I2C1->CCR |= 0x50;

	// Set the rise time.
	// TRISE value is given by (Rise time / Periph Time period) + 1.
	// Since the rise time is 1000 ns (for 100 KHz) and the periph time period = system time period = 62.5 ns, so TRISE = 16 + 1 = 17.
	I2C1->TRISE = 17;

	// Enable the I2C1 module
	I2C1->CR1 |= I2C1_PERIPH_EN;
}

// Read functionality for I2C1
i2c1_read_byte(char slave_addr, char mem_addr, char *data)
{
	// Temp variable to read registers to clear some bits.
	// Needs to be declared as volatile so that the compiler does not remove it for optimization.
	volatile int temp;

	// Wait until bus is not busy
	while(I2C1->SR2 & I2C1_BUS_BUSY);

	// Generate a start condition (Start condition to write the memory address to the slave device)
	I2C1->CR1 |= I2C1_START;

	// Wait until start flag is set in the status register.
	while(!(I2C1->SR1 & I2C1_START_STAT));

	// Transmit slave address (and set to write mode to write the memory address).
	// We are bit shifting by 1 bit, so that a 0 appears as the last bit, which is needed to generate a write condition
	I2C1->DR = slave_addr << 1;

	// Wait until address flag is set
	while(!(I2C1->SR1 & I2C1_ADDR_STAT));

	// Clear the address flag. This is done by reading the Status Register 2
	temp = I2C1->SR2;

	// Now we send the memory address
	I2C1->DR = mem_addr;

	// Wait until transmitter empty
	while(!(I2C1->SR & I2C1_TXE_STAT));

	// Generate a restart condition (now we will re-start the entire process but in read mode)
	I2C1->CR1 |= I2C1_START;

	// Wait until start flag is set
	while(!(I2C1->SR1 & I2C1_START_STAT));

	// Tranmit slave address (and now set to read mode).
	// This must be done after every re(start), since the I2C needs to determine the slave address
	//
	// We are bit shifting by 1 bit and then OR with 1, so that a 1 appears as the last bit (needed for a read condition)
	I2C1->DR = slave_addr << 1 | 1;

	// Wait until the address flag is set.
	while(!(I2C1->SR1 & I2C1_ADDR_STAT));

	// Disable acknowledge
	I2C1->CR1 &= ~(I2C1_ACK_EN);

	// Clear address flag
	temp = I2C1->SR2;

	// Generate a stop condition after data has been recieved
	I2C1->CR1 |= I2C1_STOP;

	// Wait until RXNE bit has been set
	while(!(I2C1->SR2 & I2C1_RXNE_STAT));

	// Now finally read from the Data Register
	*data++ = I2C1->DR;
}

void I2C1_burst_read(char slave_addr, char mem_addr, int n, char *data)
{
	// Temp variable for reading certain registers.
	volatile int temp;

	// Wait until bus is not busy
	while(I2C1->SR2 & I2C1_BUS_BUSY);
}
