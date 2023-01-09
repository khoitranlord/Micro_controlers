/*
 * button2.c
 *
 *  Created on: Nov 3, 2022
 *      Author: Admin
 */

#include "button2.h"


static int KeyReg0 = NORMAL_STATE;
static int KeyReg1 = NORMAL_STATE;
static int KeyReg2 = NORMAL_STATE;

static int KeyReg3 = NORMAL_STATE; //previous

static int TimerForKeyPress = 200;

int setRed = redCounter;
int setYellow = yellowCounter;
int setGreen = greenCounter;
int tempRed = redCounter;
int tempYellow = yellowCounter;
int tempGreen = greenCounter;

void KeyInputHandler2(){
	if(KeyReg1Counter == 1){
		tempRed+=1000;
		if(tempRed > 99000){
			tempRed = 0;
		}
	}
	else if(KeyReg1Counter == 2){
		tempYellow+=1000;
		if(tempYellow > 99000){
			tempYellow = 0;
		}
	}
	else if(KeyReg1Counter == 3){
		tempGreen+=1000;
		if(tempGreen > 99000){
			tempGreen = 0;
		}
	}
}
void LongKeyInputHandler2(){
	KeyInputHandler2();
}

void getKeyInput2(){
	KeyReg0 = KeyReg1;
	KeyReg1 = KeyReg2;
	KeyReg2 = HAL_GPIO_ReadPin(Button2_GPIO_Port, Button2_Pin);
	if((KeyReg0 == KeyReg1) && (KeyReg1 == KeyReg2)){
		if(KeyReg3 != KeyReg2){
			KeyReg3 = KeyReg2;
			if(KeyReg2 == PRESSED_STATE){
				KeyInputHandler2();
				TimerForKeyPress = 200;
			}
		}
		else {
			TimerForKeyPress--;
			if(TimerForKeyPress == 0){
				if(KeyReg2 == PRESSED_STATE){
					LongKeyInputHandler2();
				}
				TimerForKeyPress = 200;
			}
		}
	}
}
