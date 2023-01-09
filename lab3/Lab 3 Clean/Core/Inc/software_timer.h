/*
 * software_timer.h
 *
 *  Created on: Nov 3, 2022
 *      Author: Admin
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

extern int timer1_flag;
extern int timer2_flag;
extern int timer3_flag;

extern int timer1_counter;
extern int timer2_counter;

void setTimer1(int duration);
void setTimer2(int duration);
void setTimer3(int duration); //For Blinking
void timerRun();


#endif /* INC_SOFTWARE_TIMER_H_ */
