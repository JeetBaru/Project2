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
*	       - is_buffer_empty
*              - initialize_buffer
*              - destroy_buffer
*              - add_item
*              - remove_item
*	       - cirbuf_peak
*
****************************************************************************************/

#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <stdint.h>
#ifndef VERBOSE
	# include "MKL25Z4.h"
	# include "uart.h"
#endif
# include "cirbuff.h"
# include "analysedata.h"


//log item structure
typedef struct log_t{
	int8_t logid;
	int8_t length;
	int8_t * payload;
}log;

//global log1 pointer
log * log1;

//enum to declare logid
typedef enum log_status_t{
	LOGGER_INITIALIZED, GPIO_INITIALIZED, SYSTEM_INITIALIZED, SYSTEM_HALTED, INFO, WARNING,
	ERROR, DAT_RECIEVED, DATA_ANALYSIS_STARTED, DATA_ALPHA_COUNT, DATA_NUMERIC_COUNT, DATA_PUNCTUATION_COUNT,
	DATA_MISC_COUNT, DATA_ANALYSIS_COMPLETED
}status;

/*****************************************************************************************************
*log_data
*	description:This function adds the data to the transmit buffer and either calls
				interrupt or prints depending on device
*	parameters:
		uint8_t * ptr - pointer to the starting adress of the data to be logged
		uint32_t length - length of data
*****************************************************************************************************/
void log_data(uint8_t * ptr,uint32_t length);

/*****************************************************************************************************
*log_string
*	description:This function calculates length of string and calls log_data
*	parameters:
		uint8_t * ptr - pointer to the starting adress of the data to be logged
*****************************************************************************************************/
void log_string(int8_t * ptr);

/*****************************************************************************************************
*log_int
*	description:This function converts integer data to ascii string and call log_string
*	parameters:
		int32_t data - data to be converted and hence logged
*****************************************************************************************************/
void log_integer(int32_t data);

/*****************************************************************************************************
*create log item
*	description:this function intializes the log structure with values for next log
*	parameters:
		log * logptr - pointer to log struct
		status log_id - log id og next log item
		int32_t length - length of data of next log item
		int8_t * ptr - pointer to data of next log item
*****************************************************************************************************/
void create_log_item(log * logptr, status log_id, int32_t length, int8_t * ptr);

/*****************************************************************************************************
*destroy log item
*	description:this function destroys memory allocated in heap
*	parameters:
		log * log1 - pointer to log struct to be destroyed
*****************************************************************************************************/
void destroy_log_item(log * log1);

/*****************************************************************************************************
*log item
*	description:this function calls various functions to log desired data
*	parameters:
		log * logptr - pointer to log struct to be displayed
*****************************************************************************************************/
void log_item(log * logptr);

/*****************************************************************************************************
*log flush
*	description:this function flushes the contents of given buffer via circptr
*	parameters:
		circ_buff *circ_pre - pointer to log struct to be flused
*****************************************************************************************************/
void log_flush(circ_buff * circ_pre);

//macro to combile both log item statements
#define LOG_IT(logptr, log_id, length, ptr); {\
	create_log_item(logptr, log_id, length, ptr);\
	log_item(logptr);\
	}

//wrappers log functions
#define LOG_RAW_STRING(string) log_string(string)
#define LOG_RAW_INTEGER(data) log_integer(data)
#define LOG_RAW_DATA(pointer) log_data(pointer,length)

#endif /* SOURCES_LOGGER_H_ */
