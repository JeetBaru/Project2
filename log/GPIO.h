/*
 * GPIO.h
 *
 *  Created on: Apr 13, 2017
 *      Author: Sudeep
 */

#ifndef SOURCES_GPIO_H_
#define SOURCES_GPIO_H_
#include "MKL25Z4.h"
#include "spi.h"
#include <stdio.h>
#include <stdint.h>
#define NORDIC_CS_ENABLE()  (PTC->PCOR |= 0x10)  //clearing the ss bit to drive it low
#define NORDIC_CS_DISABLE() (PTC->PSOR |= 0x10)  //setting the ss bit to drive it high
#define NORDIC_TRANSMIT_ENABLE() (PTC->PCOR|=0X08) //transmit enable
#define NORDIC_TRANSMIT_DISABLE()	(PTC->PSOC |=0X08) //transmit disable

/*****************************************************************************************************
*GPIO_Init
*	description:function we use in SPI configuration by configuring the GPIO pins
*	parameters:
		This function has no parameters
*   return : This function does not return anything
*****************************************************************************************************/
void Gpio_Init();
/*****************************************************************************************************
*setting_high
*	description:The function is used to setting the direction output and make CE pin high
*	parameters:
		This function has no parameters
*   return : This function does not return anything
*****************************************************************************************************/
void setting_high();
/*****************************************************************************************************
*setting_low
*	description:The function is used to setting the alternat function 1 or GPIO pin for pin3 and
				setting the CE pin low.
*	parameters:
		This function has no parameters
*   return : This function does not return anything
*****************************************************************************************************/
void setting_low();

#endif /* SOURCES_GPIO_H_ */

