/* Copyright (c) 2015, Freescale Semiconductor, Inc.
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
#ifndef VERBOSE
	#include "MKL25Z4.h"
#endif
#include "uart.h"
#include "logger.h"
#include "cirbuff.h"
#include "analysedata.h"
#include <stdint.h>

void initialize(){

	circ_ptr = (circ_buff *)malloc(sizeof(circ_buff));
	initialize_buffer(circ_ptr,500);
	circ_pre = (circ_buff *)malloc(sizeof(circ_buff));
	initialize_buffer(circ_pre,16);
	log1 = (log *)malloc(sizeof(log));
	uartinit();

	LOG_IT(log1,LOGGER_INITIALIZED,1,0);

	LOG_IT(log1,SYSTEM_INITIALIZED,1,0);
}

int main(void)
{
	/*
	uartinittx();
	int8_t d[] ="12345678";
	int8_t * ptr = d;
	sendnbytes(ptr, 8);
	uartinitrx();
	uint8_t data = recievebyte();
	//int8_t  = 0x11;
	uartinittx();
	sendbyte(data);
	*/

	//uint8_t data [] = "123456789";
	//uint32_t length = 9;
	//uint8_t * ptr = data;

	//create_log_item(log1,LOGGER_INITIALIZED,1,0);
	//log_item(log1);

	initialize();
	//log_data(ptr, length);
	//log_string(ptr);
	//log_integer(0x33);
	//UART0_C2 |= 0x20;
	//create_log_item(log1,INFO,1,ptr);
	//log_item(log1);

	//log1 = (log *)malloc(sizeof(log));
	//int8_t c [20];
	//int8_t * pt;
	//pt=c;
	LOG_IT(log1,INFO,1,"ENTER ONLY 16 CHARACTERS");

	recieve_n_bytes();

	LOG_IT(log1,WARNING,1,"RECIEVE BUFFER FULL");

	*((circ_pre->tail)+16)='\0';

	LOG_IT(log1,INFO,1,"RECIEVED DATA :- ");

	LOG_IT(log1,DATA_RECIEVED,1,circ_pre->buff);

	LOG_IT(log1,INFO,1,"DATA ANALYSIS STARTED :- ")

	analyse_data(circ_pre->tail);

	LOG_IT(log1,INFO,1,"DATA ANALYSIS COMPLETED :- ");

	LOG_IT(log1,INFO,1,"FLUSHING RECIEVE BUFFER :- ");

	log_flush(circ_pre);
	/*
	create_log_item(log1,DATA_ANALYSIS_STARTED,1,0);
	log_item(log1);

	int8_t array [8]={0,'\0',0,'\0',0,'\0',0,'\0'};

	analyse_data(circ_pre->buff,&array);

	create_log_item(log1,DATA_ALPHA_COUNT,1,&array[4]);
	log_item(log1);

	create_log_item(log1,DATA_NUMERIC_COUNT,1,&array[2]);
	log_item(log1);

	create_log_item(log1,DATA_PUNCTUATION_COUNT,1,&array[0]);
	log_item(log1);

	create_log_item(log1,DATA_MISC_COUNT,1,&array[6]);
	log_item(log1);
	*/
	/*
	while(1){
	if(UART0_D && (is_buffer_full(circ_pre)==NO)){
		add_item(circ_pre, UART0_D) ;
		__enable_irq();
		}
	}
	*/
	/*
	int32_t i;
	for(i=0;i<10000;i++);
	while(is_buffer_full(circ_pre)){
		int8_t c=recievebyte();
		add_item(circ_pre,c);
		sendbyte(c);
	}
	/*
	while(is_buffer_full(circ_pre)!=FULL)
	{
		add_item(circ_pre,UART0_D);
	}
	*/
	//uint32_t i;
	//for(i=1;1<10000;i++);
	//sendbyte(0x99);


	//log_recieve();

	//uint8_t d = recievebyte();
	//sendbyte(d);

	return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
