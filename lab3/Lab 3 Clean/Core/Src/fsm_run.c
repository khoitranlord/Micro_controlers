/*
 * fsm_run.c
 *
 *  Created on: Nov 12, 2022
 *      Author: Admin
 */

#include "fsm_run.h"

#include <math.h>


const uint8_t sevenSegTable[10] = {
		  0x40 //0
		, 0x79 //1
		, 0x24 //2
		, 0x30 //3
		, 0x19 //4
		, 0x12 //5
		, 0x02 //6
		, 0x78 //7
		, 0x00 //8
		, 0x10 /*9*/};
int Seg_Arr1[7]={a_Pin,b_Pin,c_Pin,d_Pin,e_Pin,f_Pin,g_Pin};
void display7SEG1(int num){
	for(int i=0;i<7;i++){
		HAL_GPIO_WritePin(GPIOB, Seg_Arr1[i], ((sevenSegTable[num]>>i)&0x01));
	}
}
int Seg_Arr2[7]={h_Pin,i_Pin,j_Pin,k_Pin,l_Pin,m_Pin,n_Pin};
void display7SEG2(int num){
	for(int i=0;i<7;i++){
		HAL_GPIO_WritePin(GPIOB, Seg_Arr2[i], ((sevenSegTable[num]>>i)&0x01));
	}
}

int counter1 = 50;
int ledIndex = 0;

int timer1,timer2;

int tempCounter;



//STATE MACHINE FOR THE 7 SEG
void update7Seg(int index){
	switch (status3){
	case AUTOMATIC:
		timer1 = (timer1_counter / 100)+1;
		timer2 = (timer2_counter / 100)+1;
		break;
	case MANUAL:
		timer1 = KeyReg1Counter;
		timer2 = tempCounter/1000;
		status1 = WAIT;
		status2 = WAIT;
		if(KeyReg1Counter == 0){
			status1 = INIT;
			status2 = INIT;
			status3 = AUTOMATIC;
		}
		else if(KeyReg1Counter == 1){
			tempCounter = tempRed;
		}
		else if(KeyReg1Counter == 2){
			tempCounter = tempYellow;
		}
		else if(KeyReg1Counter == 3){
			tempCounter = tempGreen;
		}

		break;
	}
	switch (index){
	case 0:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, RESET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, RESET);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, SET);
		if(timer1>=10){
			display7SEG1(timer1 / 10);
		}
		else display7SEG1(0);
		if(timer2>=10){
			display7SEG2(timer2 / 10);
		}
		else display7SEG2(0);
		break;
	case 1:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, RESET);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, SET);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, RESET);
		if(timer1>=10){
			display7SEG1(timer1%10);
		}
		else display7SEG1(timer1);
		if(timer2>=10){
			display7SEG2(timer2%10);
		}
		else display7SEG2(timer2);
		break;
	default:
		break;
	}

}

void seg7Blinking(){
	if(counter1 == 0){
		if(ledIndex >=2){
			ledIndex = 0;
		}
		update7Seg(ledIndex++);
		counter1 = 50 ;
	}
	counter1--;
}
int counter3 = 50;
void fsm_run1(){
	switch (status1){
	case INIT:
		HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, SET);
		HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, SET);
		status1 = RED;
		setTimer1(setRed);
		break;
	case WAIT:
		if(KeyReg1Counter == 1){
			status1 = MAN_RED;
		}
		else if(KeyReg1Counter == 2){
			status1 = MAN_YELLOW;
		}
		else if(KeyReg1Counter == 3){
			status1 = MAN_GREEN;
		}
		break;
	case MAN_RED:
		HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, SET);
		if(counter3 > 0){
			HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, RESET);
		}
		if(counter3 < 0){
			HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, SET);
			if(counter3 == -50){
				counter3 = 50;
			}
		}
		counter3--;
		break;
	case MAN_YELLOW:
		HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, SET);
		HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, SET);
		if(counter3 > 0){
			HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, RESET);
		}
		if(counter3 < 0){
			HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, SET);
			if(counter3 == -50){
				counter3 = 50;
			}
		}
		counter3--;
		break;
	case MAN_GREEN:
		HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, SET);
		if(counter3 > 0){
			HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, RESET);
		}
		if(counter3 < 0){
			HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, SET);
			if(counter3 == -50){
				counter3 = 50;
			}
		}
		counter3--;
		break;
	case RED:
		HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, SET);
		HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, RESET);
		HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, SET);
		if(timer1_flag == 1){
			status1 = GREEN;
			setTimer1(setGreen);
		}
		break;
	case GREEN:
		HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, RESET);
		HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, SET);
		if(timer1_flag == 1){
			status1 = YELLOW;
			setTimer1(setYellow);
		}
		break;
	case YELLOW:
		HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, SET);
		HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, RESET);
		if(timer1_flag == 1){
			status1 = RED;
			setTimer1(setRed);
		}
		break;
	default:
		break;
	}

}
int counter4 = 50;
void fsm_run2(){
	switch (status2){
	case INIT:
		HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, SET);
		HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, SET);
		status2 = GREEN;
		setTimer2(setGreen);
		break;
	case WAIT:
		if(KeyReg1Counter == 1){
			status2 = MAN_RED;
		}
		else if(KeyReg1Counter == 2){
			status2 = MAN_YELLOW;
		}
		else if(KeyReg1Counter == 3){
			status2 = MAN_GREEN;
		}
		break;
	case MAN_RED:
		HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, SET);
		if(counter4 > 0){
			HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, RESET);
		}
		if(counter4 < 0){
			HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, SET);
			if(counter4 == -50){
				counter4 = 50;
			}
		}
		counter4--;
		break;
	case MAN_YELLOW:
		HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, SET);
		HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, SET);
		if(counter4 > 0){
			HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, RESET);
		}
		if(counter4 < 0){
			HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, SET);
			if(counter4 == -50){
				counter4 = 50;
			}
		}
		counter4--;
		break;
	case MAN_GREEN:
		HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, SET);
		if(counter4 > 0){
			HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, RESET);
		}
		if(counter4 < 0){
			HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, SET);
			if(counter4 == -50){
				counter4 = 50;
			}
		}
		counter4--;
		break;
	case GREEN:
		HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, RESET);
		HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, SET);
		if(timer2_flag == 1){
			status2 = YELLOW;
			setTimer2(setYellow);
		}
		break;
	case YELLOW:
		HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, SET);
		HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, RESET);
		if(timer2_flag == 1){
			status2 = RED;
			setTimer2(setRed);
		}
		break;
	case RED:
		HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, SET);
		HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, RESET);
		HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, SET);
		if(timer2_flag == 1){
			status2 = GREEN;
			setTimer2(setGreen);
		}
		break;
	default:
		break;
	}
}


