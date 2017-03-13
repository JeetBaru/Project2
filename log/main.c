
/**************************************************************************************
*   File: cirbuff.h
*
*   Copyrights 2016  Sudeep Kulkarniirlekar and Jeet Baru
*   All Rights Reserved
*
*
*   The information contained herein is property of the Authors. 
*   The copying and distribution of the files is prohibited except
*   by express written agreement with the Authors.
*
*
*   Authors: Sudeep Kulkarniirlekar and Jeet Baru
*   Date Edited: 12 March 2017
*
*   Description: Source file for implementing Circular buffer functions
*              - CircBuf_size 
*              - is_buffer_full
*	       	   - is_buffer_empty
*              - initialize_buffer
*              - destroy_buffer
*              - add_item
*              - remove_item
*	     	   - cirbuf_peak
*
****************************************************************************************/

#ifdef NOLOG
	#error "Logging Dissselected"
#endif

#ifndef VERBOSE
	#include "MKL25Z4.h"
	#include "uart.h"
#endif
#include "logger.h"
#include "cirbuff.h"
#include "analysedata.h"

#define PRINTDATA "jebasuku1234,.#@"						//Macro for input data while executing
															//on BBB and Host

//Used to initialize required structures and memory blocks
void initialize()
{
	circ_ptr = (circ_buff *)malloc(sizeof(circ_buff));		//initializes transmit buffer
	initialize_buffer(circ_ptr, 500);
	circ_pre = (circ_buff *)malloc(sizeof(circ_buff));		//initializes receive buffer
	initialize_buffer(circ_pre,16);
	log1 = (log *)malloc(sizeof(log));						//allocates memory for logger
	#ifndef VERBOSE
		uartinit();											//initialize UART only if not FRDM
	#endif

	LOG_IT(log1,LOGGER_INITIALIZED,1,0);					//log current initializations

	LOG_IT(log1,SYSTEM_INITIALIZED,1,0);
}


//main function to execute the whole project!!!
int main(void)
{
	initialize();											//make all initializations

	#ifndef VERBOSE
		LOG_IT(log1,INFO,1,"ENTER ONLY 16 CHARACTERS");		//input for FRDM
		recieve_n_bytes();
	#else
	{
		int8_t i=0;
		int8_t data[] = PRINTDATA;
		while(is_buffer_full(circ_pre)!=FULL)				//Uses MACRO data to fill transmit buffer
		{
			add_item(circ_pre,data[i]);						//add item to transmit buffer
			i++;
		}
	}
	#endif

	LOG_IT(log1,WARNING,1,"RECIEVE BUFFER FULL");			//Display warning

	*((circ_pre->tail)+16)='\0';

	LOG_IT(log1,INFO,1,"RECIEVED DATA :- ");				//Logs inputed data

	LOG_IT(log1,DAT_RECIEVED,1,circ_pre->buff);

	LOG_IT(log1,INFO,1,"DATA ANALYSIS STARTED :- ")

	analyse_data(circ_pre->tail);							//function for analysis of entered data called

	LOG_IT(log1,INFO,1,"DATA ANALYSIS COMPLETED :- ");

	LOG_IT(log1,INFO,1,"FLUSHING RECIEVE BUFFER :- ");

	log_flush(circ_pre);									//empties the recieve buffer through the transmit buffer

	return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
