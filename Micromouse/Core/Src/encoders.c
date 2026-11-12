/*
 * encoders.c
 */

#include "main.h"
#include "stm32f411xe.h"
#include "encoders.h"

/*
 * The encoder timers count in hardware as the wheels turn; the current count
 * lives in TIMx->CNT. Return the RIGHT encoder's count.
 *
 * Hint: the right encoder is on TIM3. Cast CNT to int16_t so that spinning the
 * wheel backwards reads as a negative number.
 */
int16_t getRightEncoderCounts() {
	return -(int16_t) TIM3->CNT;

}

/*
 * Return the LEFT encoder's count. The left encoder is on TIM1.
 */
int16_t getLeftEncoderCounts() {
	return -(int16_t) TIM1->CNT;

}

/*
 * This function has already been implemented for you. Enjoy! :)
 * (Left = TIM1, Right = TIM3 on this board.)
 */
void resetEncoders() {
	TIM1->CNT = (int16_t) 0;
	TIM3->CNT = (int16_t) 0;
}
