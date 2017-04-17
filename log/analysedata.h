/**************************************************************************************
*   File: analysedata.h
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

#ifndef _ANALYSEDATA_H_
#define _ANALYSEDATA_H_

#include "logger.h"
#ifndef VERBOSE
	#include "uart.h"
#endif
#include <stdint.h>
/*****************************************************************************************************
*analyse_data
*	description:This function analyses data starting from pointer passed as parameter. It 
				displays number odd characters, numbers, punctuations and misc characters
*	parameters:
		  int8_t * c - It is the starting address to the data string that is to be analysed		
*	returns:
		no returns
*****************************************************************************************************/
void analyse_data(int8_t * c);
/*****************************************************************************************************
*my_itoa
*	description:This function converts a numeric data to its equivalent ascii string
*	parameters:
		  int8_t * str - It is the destination pointer from where the ascii string will be stored
		  int32_t data - data to be converted to ascii
		  int32_t base - base is used to convert the data to the base and string
*	returns:
		Returns the pointer to the starting address of converted ascii string
*****************************************************************************************************/
int8_t * my_itoa(int8_t * str, int32_t data, int32_t base);

#endif /* SOURCES_ANALYSEDATA_H_ */
