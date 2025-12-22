/*
 * seven_segment.h
 *
 *  Created on: Dec 10, 2025
 *      Author: raunak-kar
 */

#ifndef SEVEN_SEGMENT_H_
#define SEVEN_SEGMENT_H_

// Includes
#include "stm32f4xx.h"
#include "misc.h"
#include <stdlib.h>
#include <characters.h>
#include <string.h>


// Defines
#define NUM_OF_DISP_CHARS	17

// Function declarations
// Seven Segment display functions
void seven_segment_init();
void write_to_seven_segment(char *string);


#endif /* SEVEN_SEGMENT_H_ */
