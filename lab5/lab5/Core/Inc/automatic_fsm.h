/*
 * automatic_fsm.h
 *
 *  Created on: Dec 3, 2022
 *      Author: AdminPC
 */

#ifndef INC_AUTOMATIC_FSM_H_
#define INC_AUTOMATIC_FSM_H_


#include "main.h"
#include "software_timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUFFER_SIZE 30
#define MAX_CMD_SIZE 3

extern uint8_t index_buffer;
extern uint8_t buffer_flag;
extern uint8_t buffer_byte;
extern uint8_t buffer[MAX_BUFFER_SIZE];


#define INIT 0
#define READING 1
#define STOP 2



#define RST 8
#define OK 9



void cmd_parser_fsm();
void uart_communiation_fsm();

#endif /* INC_AUTOMATIC_FSM_H_ */
