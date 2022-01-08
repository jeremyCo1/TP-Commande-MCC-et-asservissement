/*
 * shell.h
 *
 *  Created on: 15 déc. 2021
 *      Author: jerem
 */

#ifndef INC_SHELL_H_
#define INC_SHELL_H_


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "usart.h"


#define MSG_BUFFER_SIZE 20

extern int32_t speed;
extern uint32_t buf_ADC[2];
extern uint32_t buf_ADC_DMA[2];

void SHELL_init();
void SHELL();

void SHELL_help();

#endif /* INC_SHELL_H_ */
