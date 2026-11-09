/*
 * motors.h
 */

#ifndef INC_MOTORS_H_
#define INC_MOTORS_H_

#include "main.h"

#define PWM_MAX 0.8 // You probably shouldn't mess with this, but if you do, do not exceed 1
#define MAX_TIMER_COUNTS 19199 // Must equal TIM4's Counter Period / ARR. With Prescaler 0: 96 MHz / (19199+1) = 5 kHz PWM

float limitPWM(float pwm);
void setMotorRPWM(float pwm);
void setMotorLPWM(float pwm);
void resetMotors();

#endif /* INC_MOTORS_H_ */
