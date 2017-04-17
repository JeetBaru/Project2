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
#include "analysedata.h"
#define SIZE 100
#ifdef VERBOSE
	#include <sys/time.h>
	#include <stdio.h>
	struct timespec t1, t2;
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
#ifndef VERBOSE
	rtc_init();
#endif

	initialize();

	int i = 0;

    int8_t source_array[5000];
    for(i=0;i<5000;i++)
    	source_array[i]=i;
    int8_t destination_array[5000];
    for(i=0;i<5000;i++)
        source_array[i]=0;

    int8_t arr [5];
    int8_t * p = arr;

    int8_t * ptr = source_array;

    LOG_IT(log1,INFO,1,"-----MEMMOVE PROFILING-----")

#ifndef VERBOSE
    start_timer();
    start_time = START_TIMER();
    dma_memmove_32(source_array ,destination_array ,SIZE);
    diff=DIFFERENCE();
    LOG_IT(log1,CLOCK_CYCLES,1,my_itoa(p,diff,10));

    start_timer();
	start_time = START_TIMER();
	dma_memmove_16(source_array ,destination_array ,SIZE);
	diff=DIFFERENCE();
	LOG_IT(log1,CLOCK_CYCLES,1,my_itoa(p,diff,10));

	start_timer();
	start_time = START_TIMER();
	dma_memmove_8(source_array ,destination_array ,SIZE);
	diff=DIFFERENCE();
	LOG_IT(log1,CLOCK_CYCLES,1,my_itoa(p,diff,10));
#endif

#ifndef VERBOSE
	start_timer();
#endif
	start_time = START_TIMER();
	my_memmov(source_array ,destination_array ,SIZE);
	stop_time = STOP_TIMER();
	diff=DIFFERENCE();
	LOG_IT(log1,CLOCK_CYCLES,1,my_itoa(p,diff,10));


#ifndef VERBOSE
	start_timer();
#endif
	start_time = START_TIMER();
	memmove(destination_array ,source_array ,SIZE);
	stop_time = STOP_TIMER();
	diff=DIFFERENCE();
	LOG_IT(log1,CLOCK_CYCLES,1,my_itoa(p,diff,10));

	LOG_IT(log1,INFO,1,"-----MEMZERO PROFILING-----")

#ifndef VERBOSE
	start_timer();
	start_time = START_TIMER();
	dma_memzero_32(source_array, SIZE);
	diff=DIFFERENCE();
	LOG_IT(log1,CLOCK_CYCLES,1,my_itoa(p,diff,10));

	start_timer();
	start_time = START_TIMER();
	dma_memzero_16(source_array, SIZE);
	diff=DIFFERENCE();
	LOG_IT(log1,CLOCK_CYCLES,1,my_itoa(p,diff,10));

	start_timer();
	start_time = START_TIMER();
	dma_memzero_8(source_array, SIZE);
	diff=DIFFERENCE();
	LOG_IT(log1,CLOCK_CYCLES,1,my_itoa(p,diff,10));
#endif

#ifndef VERBOSE
	start_timer();
#endif
	start_time = START_TIMER();
	my_memzero(source_array, SIZE);
	stop_time = STOP_TIMER();
	diff=DIFFERENCE();
	LOG_IT(log1,CLOCK_CYCLES,1,my_itoa(p,diff,10));

#ifndef VERBOSE
	start_timer();
#endif
	start_time = START_TIMER();
	memset(source_array, 0, SIZE);
	stop_time = STOP_TIMER();
	diff=DIFFERENCE();
	LOG_IT(log1,CLOCK_CYCLES,1,my_itoa(p,diff,10));

    /*
    start_timer();

    start_time = START_TIMER();
    dma_memzero(destination_array,9);

    LOG_IT(log1,CLOCK_CYCLES,1,my_itoa(p,(stop_time - start_time),10));
	*/

	LOG_IT(log1,INFO,1,"Here");





	#ifndef VERBOSE

		uint8_t c,read_config,read_status, read_rf_ch;
		uint8_t TX_ADDR[5] = {0x17, 0x37, 0x27, 0x37, 0x97};
		uint8_t * ptr1 = TX_ADDR;

		uint8_t status=0 , read_rf_setup, val1, val2, val3, val4, val5;
		uint8_t fifo_status;

		SPI_init();

		read_status=nrf_read_status();
		LOG_IT(log1,INFO,1,my_itoa(p,read_status,16));

		uint8_t arr1[15];
		uint8_t* ptr2 = arr1;

		// calling the tx configure function
		nrf_write_config(0x02);
		read_config=nrf_read_config();
		LOG_IT(log1,INFO,1,my_itoa(p,read_config,16));

		//calling the rf setup function*/
		nrf_write_rf_setup(0x05);

		read_rf_setup = nrf_read_rf_setup();
		LOG_IT(log1,INFO,1,my_itoa(p,read_rf_setup,16));


		fifo_status = nrf_read_register(NORDIC_FIFO_STATUS);
		LOG_IT(log1,INFO,1,my_itoa(p,fifo_status,16));

		nrf_write_rf_ch(0x03);
		read_rf_ch = nrf_read_rf_ch();
		LOG_IT(log1,INFO,1,my_itoa(p,read_rf_ch,16));

		//setting tx address
		nrf_write_TX_ADDR(ptr1);
		//NORDIC_CS_ENABLE();
		nrf_read_TX_ADDR(ptr2);

		val1=*ptr2;
		ptr2++;
		val2=*ptr2;
		ptr2++;
		val3=*ptr2;
		ptr2++;
		val4=*ptr2;
		ptr2++;
		val5=*ptr2;

		LOG_IT(log1,INFO,1,my_itoa(p,val1,16));
		LOG_IT(log1,INFO,1,my_itoa(p,val2,16));
		LOG_IT(log1,INFO,1,my_itoa(p,val3,16));
		LOG_IT(log1,INFO,1,my_itoa(p,val4,16));
		LOG_IT(log1,INFO,1,my_itoa(p,val5,16));

	#endif

#ifndef VERBOSE
	while(1){
		__enable_irq();
	}
#endif

    return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
