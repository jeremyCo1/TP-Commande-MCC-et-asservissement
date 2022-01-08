/*
 * motor.c
 *
 *  Created on: 15 déc. 2021
 *      Author: jerem
 */

#include <motor.h>

uint8_t motorStatus = 0;
uint16_t motorAlpha = 500;

uint8_t MOTOR_init(){
	uint8_t ret = 0;

	HAL_GPIO_WritePin(start_GPIO_Port, start_Pin, GPIO_PIN_RESET);

	// Réglage des 4 PWM en complémentaire décalée
	TIM1->CCR2 = (uint32_t)(0.5*TIM1->ARR);
	TIM1->CCR3 = (uint32_t)(TIM1->ARR - TIM1->CCR2);

	//__HAL_TIM_SET_COUNTER(&htim2,(htim2.Instance->ARR+1)/2);
	HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);

	//__HAL_TIM_SET_COUNTER(&htim2,(uint32_t)((htim2.Instance->ARR)/2)+1);
	__HAL_TIM_SET_COUNTER(&htim2,0);
	//__HAL_TIM_SET_COUNTER(&htim2,28);
	printf("TIM2 : CNT %lu\r\n", TIM2->CNT);

	return ret;
}

uint8_t MOTOR_start(){
	uint8_t ret = 0;
	printf("Power ON\r\n");
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);

	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_3);
	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);
	HAL_GPIO_WritePin(start_GPIO_Port, start_Pin, GPIO_PIN_SET);
	motorStatus = 1;
	return ret;
}

uint8_t MOTOR_stop(){
	uint8_t ret = 0;
	printf("Power OFF\r\n");
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_3);
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);

	HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_3);
	HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_2);

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


