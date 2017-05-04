/*
 * PWM.h
 *
 *  Created on: Apr 26, 2017
 *      Author: Jeet
 */

#ifndef SOURCES_PWM_H_
#define SOURCES_PWM_H_


/****************************************************************************************************
*PWM_init
*	description:This function initializes counter for Red, Blue and Green LEDs

*	parameters:
		none

*	returns:
		None
*****************************************************************************************************/
void PWM_init(void);

/****************************************************************************************************
*PWM_init
*	description:This function initializes counter for Red LED

*	parameters:
		none

*	returns:
		None
*****************************************************************************************************/
void RED_PWM_init(void);

/****************************************************************************************************
*PWM_init
*	description:This function initializes counter for Blue LED

*	parameters:
		none

*	returns:
		None
*****************************************************************************************************/
void BLUE_PWM_init(void);

/****************************************************************************************************
*PWM_init
*	description:This function initializes counter for Green LED

*	parameters:
		none

*	returns:
		None
*****************************************************************************************************/
void GREEN_PWM_init(void);

#endif /* SOURCES_PWM_H_ */
