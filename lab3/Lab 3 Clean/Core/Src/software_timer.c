/*
 * software_timer.c
 *
 *  Created on: Nov 3, 2022
 *      Author: Admin
 */

#include "software_timer.h"
#define TICK	10

int timer1_flag = 0;
int timer2_flag = 0;
int timer3_flag = 0;

int timer1_counter = 0;
int timer2_counter = 0;
int timer3_counter = 0;


void setTimer1(int duration){
	timer1_counter = duration / TICK;
	timer1_flag = 0;
}
void setTimer2(int duration){
	timer2_counter = duration / TICK;
	timer2_flag = 0;
}
void setTimer3(int duration){
	timer3_counter = duration / TICK;
	timer3_flag = 0;
}

void timerRun(){
	if(timer1_counter > 0){
		timer1_counter--;
		if(timer1_counter <= 0) timer1_flag = 1;
	}
	if(timer2_counter > 0){
		timer2_counter--;
		if(timer2_counter <= 0) timer2_flag = 1;
	}
	if(timer3_counter > 0){
		timer3_counter--;
		if(timer3_counter <= 0) timer3_flag = 1;
	}
}
