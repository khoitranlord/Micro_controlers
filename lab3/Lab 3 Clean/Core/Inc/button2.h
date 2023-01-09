/*
 * button2.h
 *
 *  Created on: Nov 12, 2022
 *      Author: Admin
 */

#ifndef INC_BUTTON2_H_
#define INC_BUTTON2_H_

#include "global.h"
#define NORMAL_STATE 	GPIO_PIN_SET //-> 0 Nhan
#define PRESSED_STATE 	GPIO_PIN_RESET // -> Nhan

extern int setRed;
extern int setYellow;
extern int setGreen;
extern int tempRed;
extern int tempYellow;
extern int tempGreen;
//function prototype
void KeyInputHandler2();
void LongKeyInputHandler2();
void getKeyInput2();
#endif /* INC_BUTTON2_H_ */
