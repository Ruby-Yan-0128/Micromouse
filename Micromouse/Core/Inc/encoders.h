/*
 * encoders.h
 *
 * Wheel encoder mapping on this board:
 *   Left  encoder -> TIM1 (PA8 = TIM1_CH1, PA9 = TIM1_CH2)
 *   Right encoder -> TIM3 (PB4 = TIM3_CH1, PB5 = TIM3_CH2)
 */

#ifndef INC_ENCODERS_H_
#define INC_ENCODERS_H_

#include "main.h"

int16_t getRightEncoderCounts();
int16_t getLeftEncoderCounts();
void resetEncoders();

#endif /* INC_ENCODERS_H_ */
