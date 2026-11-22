/*
 * irs.h
 */

#ifndef INC_IRS_H_
#define INC_IRS_H_

#include "main.h"

// The number of samples to take (and average) for each reading
#define NUM_SAMPLES 128

// Using this enumeration makes the code more readable
// The IRs are numbered around the front of the Rat from left to right:
// IR_1 = left side, IR_2 = front-left, IR_3 = front-right, IR_4 = right side
typedef enum
{
	IR_1 = 0,
	IR_2 = 1,
	IR_3 = 2,
	IR_4 = 3
}IR;

uint16_t readIR(IR ir);
uint16_t readIR1(void);
uint16_t readIR2(void);
uint16_t readIR3(void);
uint16_t readIR4(void);
uint16_t analogRead(IR ir);

#endif /* INC_IRS_H_ */
