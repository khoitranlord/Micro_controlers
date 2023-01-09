/*
 * led_display.c
 *
 *  Created on: Nov 12, 2022
 *      Author: AdminPC
 */
#include "led_display.h"
#include "main.h"


void led_red_toggle(void){
	HAL_GPIO_TogglePin( LED_RED_GPIO_Port, LED_RED_Pin);
}
void led_yellow_toggle(void){
	HAL_GPIO_TogglePin( LED_YELLOW_GPIO_Port, LED_YELLOW_Pin);
}
void led_green_toggle(void){
	HAL_GPIO_TogglePin( LED_GREEN_GPIO_Port, LED_GREEN_Pin);
}
