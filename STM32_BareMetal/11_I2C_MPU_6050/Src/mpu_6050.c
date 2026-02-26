//
// MPU 6050 driver for STM32 to measure both accelerometer measurement, temp measurement and gyroscope measurement.
//

// Includes
#include "mpu_6050.h"

// Global variables
volatile uint8_t init_status = FALSE;

// Function declarations (private)

// Functions
//
// Initialize MPU 6050
void mpu_6050_init(void)
{
	// Initialize I2C
	i2c1_init();

	// Read the WHO_AM_I register to get the device ID of the MPU 6050 (needed to verify if the connection was established)
	// This is not the slave address (that we need to hardcode into the program).
	init_status = FALSE;
	char whoami[1];
	mpu_6050_read(MPU_6050_WHOAMI, whoami, 1);

	// Verify whoami (must be 0x68)
	if(whoami == 0x68)
	{
		// Set init status to TRUE
		init_status = TRUE;

		// Set all the registers in the RESET state in the Power Management Register 1.
		// Also enable temp measurement and set CLKSEL bit to 0 (8 MHz internal clock).
		char pwr_mg_val = 0;
		pwr_mg_val |= (1UL << 7);
		mpu_6050_write(MPU_6050_PRW_MGMT_1, pwr_mg_val);

		// Configure accelerometer and gyroscope to measure upto +-4g and 250deg/s respectively
		char accl_config = 0;
		accl_config |= (1UL << 3);
		char gyro_config = 0;
		mpu_6050_write(MPU_6050_ACCL_CONFIG, accl_config);
		mpu_6050_write(MPU_6050_GYRO_CONFIG, gyro_config);

		// We want the gyroscope readings to be sampled at 1KHz
		// The default sampling rate of the gyroscope is 8KHz and varies as sample_rate = gyro_default / (1+Sample_Rate_div)
		// For that we need to set the Sample Rate Divider register to 0x07
		char smpl_rate_div = 0x07;
		mpu_6050_write(MPU_6050_SMPLRT_DIV, smpl_rate_div);
	}
}

// Read accelerometer measurements
// The accl_data_raw array will hold the values of the X, Y and Z accl data respectively
void mpu_6050_accel_read(uint16_t *accl_data_raw, float *accl_data)
{
	if(init_status == TRUE)
	{
		// Since the X, Y and Z acclerometer values are 16 bit we read 8 bits from the low and high registers for each of them,
		// and then accurately set them in the accl_data_raw.
		//
		// Read the data appropriately
		char data[6];
		mpu_6050_read(accl_data_raw_REG_START, data, 6);

		// Store the read data appropriately
		accl_data_raw[0] = (data[0] << 8) | data[1];
		accl_data_raw[1] = (data[2] << 8) | data[3];
		accl_data_raw[2] = (data[4] << 8) | data[5];

		// Store the converted values
		// For conversion we need to divide each raw data by the LSB sensitivity (8192 for range = +-4g)
		accl_data[0] = (float) accl_data_raw[0] / 8192.0f;
		accl_data[1] = (float) accl_data_raw[1] / 8192.0f;
		accl_data[2] = (float) accl_data_raw[2] / 8192.0f;
	}

	else show_error(INIT);
}

// Read temp measurements
void mpu_6050_temp_read(uint16_t temp_data_raw, float temp_data)
{
	if(init_status == TRUE)
	{
		// The temp registers are divided into temp_high and temp_low.
		// Read the data appropriately
		char data[2];
		mpu_6050_read(temp_data_raw_REG_START, data, 2);

		// Store the read raw data appropriately
		temp_data_raw = (data[0] << 8) | data[1];

		// Convert it to interpretable value appropriately
		temp_data = ((float) temp_data_raw/340.00f) + 36.53f;
	}

	else show_error(INIT);
}

// Read gyroscope measurements
// The gyro_data_raw array will hold the values of the X, Y and Z gyro data respectively
void mpu_6050_gyro_read(uint16_t *gyro_data_raw, float *gyro_data)
{
	if(init_status == TRUE)
	{
		// Since the X, Y and Z gyro values are 16 bit we read 8 bits from the low and high registers for each of them
		// and then accurately set them in the gyro_data_raw.
		//
		// Read the data appropriately
		char data[6];
		mpu_6050_read(gyro_data_raw_REG_START, data, 6);

		// Store the read data appropriately
		gyro_data_raw[0] = (data[0] << 8) | data[1];
		gyro_data_raw[1] = (data[2] << 8) | data[3];
		gyro_data_raw[2] = (data[4] << 8) | data[5];

		// Divide the raw data by the LSB sensitivity to get the actual value
		// The LSB senstivity for gyro range = +- 250deg/secs = 131.00
		gyro_data[0] = (float) gyro_data_raw[0] / 250.00f;
		gyro_data[1] = (float) gyro_data_raw[1] / 250.00f;
		gyro_data[2] = (float) gyro_data_raw[2] / 250.00f;
	}

	else show_error(INIT);
}

// Read a register(s) of the MPU 6050
// The read data from each register is stored sequentially in data.
// The num_regs specifies how many regs to read starting from the mem_addr
void mpu_6050_read(char mem_addr, char *data, int num_regs)
{
	if(init_status == TRUE)
	{
		// Read num_regs consecutive bytes from MPU 6050
		i2c1_read_bytes(MPU_6050_ADDR, mem_addr, num_regs, data);
	}

	else throw_error(INIT);
}

// Write to MPU 6050
void mpu_6050_write(char mem_addr, char value)
{
	if(init_status == TRUE)
	{
		char data[1];
		data[0] = value;
		i2c_write_bytes(MPU_6050_ADDR, mem_addr, 1, data);
	}

	else throw_error(INIT);
}

