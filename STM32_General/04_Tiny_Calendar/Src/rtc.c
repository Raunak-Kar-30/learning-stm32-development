/*
 * Source file for configuring and interacting with the Real Time Clock module.
 * This code has been with reference to
 * 		: Israel Gbati Bare-Metal Embedded C book - Chapter : The Real-Time Clock (RTC)
 *
 * This is currently incomplete and must be modified before using further.
 */

// Includes
#include "rtc.h"

// Function declarations (private)

// Functions
// Initialize the RTC. Returns -1 if failed.
int rtc_init(void)
{
	// Check if LSE is on
	if(!(lse_on))
	{
		printf("LSE is not enabled. Enable LSE and then initialize the RTC \r\n");
		return -1;
	}

	// Set the RTC to init mode

	return 0;
}

// Set the asynchronous and synchronous prescaler values
static void rtc_set_asynch_prescaler(uint32_t AsynchPrescaler)
{
	// The MODIFY_REG along with the RTC_PRER_REDIV_A and RTC_PRER_PREDIV_A_Pos macrosa are defined in stm32f4xx.h
	// This basically configures the asynchronous prescaler by updating the appropriate bits in the PRER register.
	//
	// RTC->PRER is the register for setting pre-scaler values (both synchronous and asynchronous)
	// RTC_PRER_PREDIV_A masks the asynchronous prescaler bits
	// RTC_PRER_PREDIV_A_Pos is the position where the AsynchPrescaler is to be written, so we bitshift it to that positon (16 -> 22).
	MODIFY_REG(RTC->PRER, RTC_PRER_PREDIV_A, AsynchPrescaler << RTC_PRER_PREDIV_A_Pos);
}

static void rtc_set_synch_prescaler(uint32_t SynchPrescaler)
{
	// Here SynchPrescaler need not be bit shifted since bits start from 0 -> 14, and can be written directly
	MODIFY_REG(RTC->PRER, RTC_PRER_PREDIV_S, SynchPrescaler);
}

// Configure the date of RTC
static void rtc_date_config(uint32_t week_day, uint32_t day, uint32_t month, uint32_t year)
{
	register uint32_t temp = 0UL;

	// Continue from here ....
}

// RTC Init sequence
static uint8_t rtc_init_seq(void)
{
	// Enable Init mode
	_rtc_enable_init_mode();

	// Wait till we are in init mode
	while(_rtc_init_status() != 1);

	return 1;
}

// RTC exit init sequence
static uint8_t rtc_exit_init_seq(void)
{
	// Stop init mode
	_rtc_disable_init_mode();

	// Wait for registers to synchronize by going to the rtc_reg_sync_wait() function via return.
	return (rtc_reg_sync_wait());
}

// RTC function to wait until all registers are synchronized
static uint8_t rtc_reg_sync_wait(void)
{
	// Clear the Register Sync Status flag from ISR
	RTC->ISR &= ~(RTC_REG_SYCN_FLAG);

	// Wait for registers to synchronize
	while(_rtc_regs_sync_status() != 1);

	return 1;
}

// Enable RTC init
void _rtc_enable_init_mode(void)
{
	RTC->ISR |= RTC_INIT_MODE_EN;
}

// Disable RTC init
void _rtc_disable_init_mode(void)
{
	RTC->ISR &= ~(RTC_INIT_MODE_EN);
}

// Check if RTC is in init mode
uint8_t _rtc_init_status(void)
{
	// If INITF bit is set in the Initialization and Status Register, then RTC is in init mode and calendar registers can be updated
	// else not
	return (RTC->ISR & RTC_INIT_FLAG);
}

// Check if RTC registers have synchronized
uint8_t _rtc_regs_sync_status(void)
{
	// Check if calendar shadow registers are synchronized
	return (RTC->ISR & RTC_REG_SYCN_FLAG);
}

