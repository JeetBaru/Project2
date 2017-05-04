/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdint.h>
#include "profiler.h"
#include "logger.h"
#include <string.h>
#include "memory.h"
#include "PWM.h"
#include "command.h"


#ifdef VERBOSE
	#include <time.h>
	#include <stdio.h>
	struct timeval t1, t2;
#else
	#include "MKL25Z4.h"
	#include "uart.h"
	#include "DMA.h"
	#include "RTC.h"
	#include "spi.h"
	#include "nrf.h"
	#include "GPIO.h"
#endif


void initialize()
{
	circ_ptr = (circ_buff *)malloc(sizeof(circ_buff));		//initializes transmit buffer
	initialize_buffer(circ_ptr, 5000);
	circ_pre = (circ_buff *)malloc(sizeof(circ_buff));		//initializes receive buffer
	initialize_buffer(circ_pre,16);
	log1 = (log *)malloc(sizeof(log));						//allocates memory for logger
	#ifndef VERBOSE
		uartinit();											//initialize UART only if not FRDM
	#endif

	LOG_IT(log1,LOGGER_INITIALIZED,1,0);					//log current initializations

	LOG_IT(log1,SYSTEM_INITIALIZED,1,0);
}

int main(void)
{
	uint16_t i;

#ifndef VERBOSE
	rtc_init();												//initialize RTC
#endif

	initialize();											//initialize UART and Logger
	PWM_init();												//initializes timer for PWM
	LED_init();												//initialize LEDs

	uint16_t (*cmd_fp [])(int) = {get_command, validate, decode_command};

	while(1)
	{
		(*cmd_fp[0])(0);									//call get command via function pointer
		sendnbytes("CommandRecieved",15);
		i = (*cmd_fp[1])(0);								//call validate command via function pointer
		if(i==1)
			(*cmd_fp[2])(0);								//call decode command vis function pointer
		free(cmd_msg[0].data);
	}

    return 0;

}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
