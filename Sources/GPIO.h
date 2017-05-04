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


void Gpio_Init();
void setting_high();
void setting_low();

#endif /* SOURCES_GPIO_H_ */
