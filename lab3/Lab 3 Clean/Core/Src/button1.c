/*
 * button1.c
 *
 *  Created on: Nov 3, 2022
 *      Author: Admin
 */

#include "button1.h"

int KeyReg1Counter = 0;

static int KeyReg0 = NORMAL_STATE;
static int KeyReg1 = NORMAL_STATE;
static int KeyReg2 = NORMAL_STATE;

static int KeyReg3 = NORMAL_STATE; //previous

static int TimerForKeyPress = 200;

void KeyInputHandler1(){
	KeyReg1Counter++;
	if(KeyReg1Counter >= 4){

		KeyReg1Counter = 0;
	}
	status3 = MANUAL;
}
void LongKeyInputHandler1(){
	KeyInputHandler1();
}

void getKeyInput1(){
	KeyReg0 = KeyReg1;
	KeyReg1 = KeyReg2;
	KeyReg2 = HAL_GPIO_ReadPin(Button1_GPIO_Port, Button1_Pin);
	if((KeyReg0 == KeyReg1) && (KeyReg1 == KeyReg2)){
		if(KeyReg3 != KeyReg2){
			KeyReg3 = KeyReg2;
			if(KeyReg2 == PRESSED_STATE){
				KeyInputHandler1();
				TimerForKeyPress = 200;
			}
		}
		else {
			TimerForKeyPress--;
			if(TimerForKeyPress == 0){
				if(KeyReg2 == PRESSED_STATE){
					LongKeyInputHandler1();
				}
				TimerForKeyPress = 200;
			}
		}
	}
}
