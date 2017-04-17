/*
 * RTC.h
 *
 *  Created on: Apr 15, 2017
 *      Author: Jeet
 */

#ifndef SOURCES_RTC_H_
#define SOURCES_RTC_H_
/*****************************************************************************************************
*rtc_init
*	description: This function is used to configure the RTC module
*	parameters:
		This function has no parameters
*   return : This function does not return anything
*****************************************************************************************************/
void rtc_init(void);
/*****************************************************************************************************
*GPIO_Init
*	description:This function is used to lock the current value of RTC_TSR
*	parameters:
		This function has no parameters
*   return : Returns the value of RTC_TSR
*****************************************************************************************************/
uint32_t get_time();

#endif /* SOURCES_RTC_H_ */
