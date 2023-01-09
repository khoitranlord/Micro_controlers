/*
 * global.h
 *
 *  Created on: Nov 3, 2022
 *      Author: Admin
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
#include "software_timer.h"
#include "button1.h"
#include "button2.h"
#include "button3.h"
#include "fsm_run.h"

extern int status1;
extern int status2;
extern int status3; //timer

#define redCounter		10000
#define yellowCounter	2000
#define greenCounter	8000

#define INIT		0
#define RED			1
#define YELLOW		2
#define GREEN		3
#define MAN_RED		11
#define MAN_YELLOW 	12
#define MAN_GREEN 	13

#define WAIT		19
#define AUTOMATIC	20
#define MANUAL		21

#endif /* INC_GLOBAL_H_ */
