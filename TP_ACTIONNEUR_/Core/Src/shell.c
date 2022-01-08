/*
 * shell.c
 *
 *  Created on: 15 déc. 2021
 *      Author: jerem
 */

#include <shell.h>
#include <motor.h>

char msg[1];
int it_uart;
char bufMesg[MSG_BUFFER_SIZE];
uint8_t cptr_buf;

char bufMotorSpeed[4];

int32_t speed = 0;
uint32_t buf_ADC_DMA[2];
uint32_t buf_ADC[2];

void SHELL_init(){
	it_uart = 0;
	msg[0] = 0;
	for(int i=0; i<(MSG_BUFFER_SIZE+1);i++){
		bufMesg[i] = 0;
	}
	cptr_buf = 0;

	HAL_UART_Receive_IT(&huart2,(uint8_t*)msg,1);
}

void SHELL(){
	if(it_uart){
		if(msg[0] == '\r'){
			printf("\r\n");
			bufMesg[cptr_buf] = '\0';
			if(strcmp(bufMesg,"help") == 0){
				SHELL_help();
			}else if(strcmp(bufMesg,"pinout") == 0){
				printf("Fonction pinout à faire !\r\n");
			}else if(strcmp(bufMesg,"start") == 0){
				MOTOR_start();
			}else if(strcmp(bufMesg,"stop") == 0){
				MOTOR_stop();
			}else if(strcmp(bufMesg,"cnt") == 0){
				printf("vitesse = %ld tr/min \r\n",speed);
				printf("courant R = %lu mA \r\n",buf_ADC[0]);
				printf("courant Y = %lu mA \r\n",buf_ADC[1]);
			}else if(strcmp(bufMesg,"") == 0){
			}else{
				for(int i=0; i<4; i++){
					bufMotorSpeed[i] = bufMesg[i+6];
				}
				bufMesg[6] = '\0';
				if(strcmp(bufMesg,"speed=") == 0){
					motorAlpha = (uint16_t)atoi(bufMotorSpeed);
					//MOTOR_setSpeed(atoi(bufMotorSpeed));
				}else{
					printf("Command not found\r\n");
				}
			}
			for(int i=0; i<(cptr_buf+1); i++){
				bufMesg[cptr_buf] = 0;
			}
			cptr_buf = 0;
		}else{
			HAL_UART_Transmit(&huart2, (uint8_t*)msg, 1, HAL_MAX_DELAY);
			bufMesg[cptr_buf] = msg[0];
			cptr_buf++;
		}
		it_uart = 0;
	}
}

void SHELL_help(){
	printf(" pinout\r\n start\r\n stop\r\n speed=XXXX\r\n");
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART2){
		HAL_UART_Receive_IT(&huart2,(uint8_t*)msg,1);
		it_uart = 1;
	}
}

