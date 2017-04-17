/*
 * profiler.c
 *
 *  Created on: Apr 13, 2017
 *      Author: Jeet
 */

#include "MKL25Z4.h"
#include <stdint.h>
#include "profiler.h"

void start_timer()
{

	SIM_SCGC6 |= 0x2000000;					// Enable TPM1 Clock gate
	SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1);		// Select MCGIRFLL clock 21 Mhz

	TPM1_SC = 0;							// Disable Timer
	TPM1_MOD = 0xFFFF;

	overflow = 0;

	//TPM1_SC |= 0x4;					// Prescaler divide by 16
	//TPM1_SC &= ~0x3;

	TPM1_SC &= ~(0x07);

	TPM1_SC |= 0x80;				// Clear TOF flag by writing 1 to it
	TPM1_SC |= TPM_SC_TOIE_MASK; 	// Enable Timer Overflow Interrupt
	NVIC->ISER[0] |= 0x00040000;

	TPM1_SC |= 0x8;					// Selecting clock mode

	//__enable_irq();					// Enable global Interrupt

}

void TPM1_IRQHandler()
{
	__disable_irq();
	overflow++;
	TPM1_SC |= 0x80;				// Clear TOF flag by writing 1 to it
	__enable_irq();
}

uint16_t read_count()
{
	return TPM1_CNT;
}

{

	SIM_SCGC6 |= 0x2000000;					// Enable TPM1 Clock gate
	SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1);		// Select MCGIRFLL clock 21 Mhz

	TPM1_SC = 0;							// Disable Timer
	TPM1_MOD = 0xFFFF;

	overflow = 0;

	//TPM1_SC |= 0x4;					// Prescaler divide by 16
	//TPM1_SC &= ~0x3;

	TPM1_SC &= ~(0x07);

	TPM1_SC |= 0x80;				// Clear TOF flag by writing 1 to it
	TPM1_SC |= TPM_SC_TOIE_MASK; 	// Enable Timer Overflow Interrupt
	NVIC->ISER[0] |= 0x00040000;

	TPM1_SC |= 0x8;					// Selecting clock mode

	//__enable_irq();					// Enable global Interrupt

}

void TPM1_IRQHandler()
{
	__disable_irq();
	overflow++;
	TPM1_SC |= 0x80;				// Clear TOF flag by writing 1 to it
	__enable_irq();
}

uint16_t read_count()
{
	return TPM1_CNT;
}
