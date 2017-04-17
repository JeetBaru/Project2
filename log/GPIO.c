/*
 * GPIO.c
 *
 *  Created on: Apr 13, 2017
 *      Author: Sudeep
 */
#include "GPIO.h"




void Gpio_Init()
{
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
	PORTC_PCR4 |= PORT_PCR_MUX(1); 			//Select Alternate function 1 (or gpio pin) for SPI0_PCS0 (or SPI SS)
	PORTC_PCR5 |= PORT_PCR_MUX(2);			//Select Alternate function 2 for SPI0_SCK
	PORTC_PCR6 |= PORT_PCR_MUX(2); 			//Select Alternate function 2 for SPI0_MOSI
	PORTC_PCR7 |= PORT_PCR_MUX(2); 			//Select Alternate function 2 for SPI0_MISO
	PORTC_PCR3 |= PORT_PCR_MUX(1);			//For CE pin

}
void setting_high()
{
	//enabling port C
		SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
		//Select Alternate function 1 (or gpio pin) for pin 3
		PORTC_PCR3 |= PORT_PCR_MUX(1);
		//setting direction as output
		PTC->PDDR |= 0x08;
		//making the CE pin high (active high)
		PTC->PSOR = 0x08;
}

void setting_low()
{
	//enabling port C
		SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
		//Select Alternate function 1 (or gpio pin) for pin 3
		PORTC_PCR3 |= PORT_PCR_MUX(1);
		//setting direction as output
		PTC->PDDR |= 0x08;
		//making the CE pin low (active high)
		PTC->PCOR = 0x08;

}
