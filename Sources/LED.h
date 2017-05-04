/*
 * LED.h
 *
 *  Created on: Apr 26, 2017
 *      Author: Jeet
 */

#ifndef SOURCES_LED_H_
#define SOURCES_LED_H_

#include "MKL25Z4.h"
#include "profiler.h"

//      COLOR       Value          R G B
#define OFF         0           // 0 0 0
#define BLUE        1           // 0 0 1
#define GREEN       2           // 0 1 0
#define CYAN        3           // 0 1 1
#define RED         4           // 1 0 0
#define PINK        5           // 1 0 1
#define ORANGE      6           // 1 1 0
#define WHITE       7           // 1 1 1

#define PWM_OVERFLOW_VALUE          65535u
#define RED_LED                     TPM2_C0V
#define GREEN_LED                   TPM2_C1V
#define BLUE_LED                    TPM0_C1V


/****************************************************************************************************
*led_init
*	description:This function initializes LED GPIO pins

*	parameters:
		None

*	returns:
			None
*****************************************************************************************************/
void LED_init(void);


/****************************************************************************************************
*LED_SET_COLOR
*	description:This function sets a color by writing to specific timer registers
*				and writing 0 onto the rest

*	parameters:
		uint8_t COLOUR - it recieves a value between 0-7 and sets certain timer registers
		according to the requested color

*	returns:
			None
*****************************************************************************************************/
void LED_SET_COLOR(uint8_t COLOUR);

/****************************************************************************************************
*LED_SET_BRIGHTNESS
*	description:This function sets the brightness of the requested LED to a certain value
*				passed as an arguement.

*	parameters:
		int LED - LED which must be set
		int brightness - value of brightness to which the LED is set

*	returns:
			None
*****************************************************************************************************/
void LED_SET_BRIGHTNESS(uint8_t LED, uint32_t BRIGHTNESS);

/****************************************************************************************************
*LED_ON_IT
*	description:This function turns an LED on by writing the last value of LED brightness

*	parameters:
		LED - The LED which is to be turned ON

*	returns:
			None
*****************************************************************************************************/
void LED_ON_IT(uint8_t LED);

/****************************************************************************************************
*LED_ON_IT
*	description:This function turns an LED on by writing the last value of LED brightness

*	parameters:
		LED - The LED which is to be turned OFF

*	returns:
			None
*****************************************************************************************************/
void LED_OFF_IT(uint8_t LED);

#endif /* SOURCES_LED_H_ */
