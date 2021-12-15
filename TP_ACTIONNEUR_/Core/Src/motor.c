/*
 * motor.c
 *
 *  Created on: 15 déc. 2021
 *      Author: jerem
 */

#include <motor.h>

uint8_t motorStatus = 0;

uint8_t MOTOR_init(){
	uint8_t ret = 0;

	HAL_GPIO_WritePin(start_GPIO_Port, start_Pin, GPIO_PIN_RESET);

	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);

	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_3);
	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);

	// Réglage des 4 PWM en complémentaire décalée
	TIM1->CCR2 = (uint32_t)(0.6*TIM1->ARR);
	TIM1->CCR3 = (uint32_t)(TIM1->ARR - TIM1->CCR2);

	return ret;
}

uint8_t MOTOR_start(){
	uint8_t ret = 0;
	printf("Power ON\r\n");
	HAL_GPIO_WritePin(start_GPIO_Port, start_Pin, GPIO_PIN_SET);
	motorStatus = 1;
	return ret;
}

uint8_t MOTOR_stop(){
	uint8_t ret = 0;
	printf("Power OFF\r\n");
	HAL_GPIO_WritePin(start_GPIO_Port, start_Pin, GPIO_PIN_RESET);
	motorStatus = 0;
	return ret;
}

uint8_t MOTOR_setSpeed(int motorSpeed){
	uint8_t ret = 0;

	if(motorSpeed <= TIM1->ARR){
		TIM1->CCR2 = (uint32_t)motorSpeed;
		TIM1->CCR3 = (uint32_t)(TIM1->ARR - TIM1->CCR2);
	}else{
		ret = MOTOR_ERROR_SPEED;
		printf("ERROR - La vitesse doit être comprise entre 0 et %ld\r\n",TIM1->ARR);
	}
	return ret;
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	if(GPIO_Pin == MOTOR_BUTTON_Pin){
		if(motorStatus == 0){
			MOTOR_start();
		}else if(motorStatus == 1){
			MOTOR_stop();
		}
	}
}

