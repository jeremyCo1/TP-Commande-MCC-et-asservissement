/*
 * motor.h
 *
 *  Created on: 15 déc. 2021
 *      Author: jerem
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include "stdio.h"
#include "tim.h"
#include "gpio.h"

#define MOTOR_ERROR_SPEED 10
#define MOTOR_ENCODER_LEN 1000

extern uint16_t motorAlpha;
extern uint8_t motorStatus;

uint8_t MOTOR_init();

uint8_t MOTOR_start();
uint8_t MOTOR_stop();

uint8_t MOTOR_setSpeed(int motorSpeed);

#endif /* INC_MOTOR_H_ */
