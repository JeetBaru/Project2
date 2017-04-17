
#include "MKL25Z4.h"
#include <stdint.h>
#include "logger.h"

void rtc_init(void)
{
    SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;      //Enable Port C clock
    MCG_C1 |= MCG_C1_IRCLKEN_MASK;      //Enable internal reference clock
	MCG_C2 &= ~(MCG_C2_IRCS_MASK);      //Internal Reference Clock Slow
	PORTC_PCR1 |= (PORT_PCR_MUX(0x1));              //PTC1 as RTC_CLKIN
    SIM_SOPT1 |= 0x00080000;                    //RTC_CLKIN selected for OSC32KCLK
    SIM_SOPT2 |= 0x00000080;                    //MCGIRCLK selected for clock out
    PORTC_PCR3 |= (PORT_PCR_MUX(0x5));              //PTC3 as CLKOUT

    SIM_SCGC6 |= SIM_SCGC6_RTC_MASK;        //Enable the clock to RTC

    RTC_CR  |= RTC_CR_SWR_MASK;

    RTC_CR  &= ~RTC_CR_SWR_MASK;            //Disable and reset RTC

    if (RTC_SR & RTC_SR_TIF_MASK){          //Check if time invalid
		RTC_TSR = 0x00000000;               //Clears the Time invalid flag
	}
    
    RTC_TSR = 0x58F2EFB2;                           //Reset the seconds register

    RTC_IER |=0x10;

    RTC_SR |= RTC_SR_TCE_MASK;                      //Enable RTC

    NVIC_EnableIRQ(RTC_Seconds_IRQn);
    __enable_irq();
}

uint32_t get_time()
{
	return RTC_TSR;
}

extern void RTC_Seconds_IRQHandler()
{
	__disable_irq();
	LOG_IT(log1,HEARTBEAT,1,"HEARTBEAT");
	__enable_irq();
}
