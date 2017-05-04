/*
 * LED.c
 *
 *  Created on: Apr 25, 2017
 *      Author: Jeet
 */

#include "LED.h"

uint8_t color = 7;                              //Integer to store the color number from 0 to 7
uint32_t brightness_value = 2;                   //Integer to store brightness on a scale of 1 to 10
uint32_t brightness = 0.5*PWM_OVERFLOW_VALUE;    //Integer to store duty cycle for set brightness
uint32_t brightness_r = PWM_OVERFLOW_VALUE;
uint32_t brightness_g = PWM_OVERFLOW_VALUE;
uint32_t brightness_b = PWM_OVERFLOW_VALUE;

void LED_init(void){
    SIM_SCGC5 |= 0x00000400;            // enable clock to Port B
    SIM_SCGC5 |= 0x00001000;            // enable clock to Port D
    PORTB_PCR18 = PORT_PCR_MUX(3);      // set PTB18(red LED) pin as PWM
    PTB->PDDR |= 0x00040000;            // set PTB18 as output pin
    PORTB_PCR19 = PORT_PCR_MUX(3);      // set PTB19(green LED) pin as PWM
    PTB->PDDR |= 0x00080000;            // set PTB19 as output pin
    PORTD_PCR1 = PORT_PCR_MUX(4);       // make PTD1(blue LED) pin as PWM
    PTD->PDDR |= 0x00000002;            // make PTD1 as output pi
}

void LED_SET_COLOR(uint8_t COLOUR){
    color = COLOUR;
    if(color<0)                         //if color goes beyond selection then rotate back
        color = 7;
    else if (color > 7)
        color = 0;
    switch(color){
        case 0:
            RED_LED = 0;                // red LED off
            GREEN_LED = 0;              // green LED off            OFF
            BLUE_LED = 0;               // blue LED off
            break;

        case 1:
            RED_LED = 0;                // red LED off
            GREEN_LED = 0;              // green LED off            BLUE
            BLUE_LED = brightness;      // blue LED on
            break;

        case 2:
            RED_LED = 0;                // red LED off
            GREEN_LED = brightness;     // green LED on             GREEN
            BLUE_LED = 0;               // blue LED off
            break;

        case 3:
            RED_LED = 0;                // red LED off
            GREEN_LED = brightness;     // green LED on             LIGHT BLUE
            BLUE_LED = brightness;      // blue LED on
            break;

        case 4:
            RED_LED = brightness;       // red LED on
            GREEN_LED = 0;              // green LED off            RED
            BLUE_LED = 0;               // blue LED off
            break;

        case 5:
            RED_LED = brightness;       // red LED on
            GREEN_LED = 0;              // green LED off            PINK
            BLUE_LED = brightness;      // blue LED on
            break;

        case 6:
            RED_LED = brightness;       // red LED on
            GREEN_LED = brightness;     // green LED on             ORANGE
            BLUE_LED = 0;               // blue LED off
            break;

        case 7:
            RED_LED = brightness;       // red LED on
            GREEN_LED = brightness;     // green LED on             WHITE
            BLUE_LED = brightness;      // blue LED on
            break;

        default:
            RED_LED = brightness;       // red LED on
            GREEN_LED = brightness;     // green LED on             WHITE
            BLUE_LED = brightness;      // blue LED on
            break;

    }

}


void LED_SET_BRIGHTNESS(uint8_t LED,uint32_t BRIGHTNESS){

	brightness = BRIGHTNESS;

	if(LED == 0)
		RED_LED = BRIGHTNESS;
	else if(LED == 1)
		GREEN_LED = BRIGHTNESS;
	else if(LED == 2)
		BLUE_LED = BRIGHTNESS;
	else
		LED_SET_COLOR(color);

}

void LED_OFF_IT(uint8_t LED)
{
	if(LED == 0)
		RED_LED = 0;
	else if(LED == 1)
		GREEN_LED = 0;
	else if(LED == 2)
		BLUE_LED = 0;
	else
	{
		RED_LED = 0;
		GREEN_LED = 0;
		BLUE_LED = 0;
	}
}

void LED_ON_IT(uint8_t LED)
{
	if(LED == 0)
		RED_LED = PWM_OVERFLOW_VALUE;
	else if(LED == 1)
		GREEN_LED = PWM_OVERFLOW_VALUE;
	else if(LED == 2)
		BLUE_LED = PWM_OVERFLOW_VALUE;
	else
	{
		RED_LED = PWM_OVERFLOW_VALUE;
		GREEN_LED = PWM_OVERFLOW_VALUE;
		BLUE_LED = PWM_OVERFLOW_VALUE;
	}
}


