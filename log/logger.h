/*
 * logger.h
 *
 *  Created on: Mar 3, 2017
 *      Author: Jeet
 */

#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <stdint.h>
#ifndef VERBOSE
	# include "MKL25Z4.h"
	# include "uart.h"
#endif
# include "cirbuff.h"
# include "analysedata.h"

typedef struct log_t{
	int8_t logid;
	int8_t length;
	int8_t * payload;
}log;

log * log1;

typedef enum log_status_t{
	LOGGER_INITIALIZED, GPIO_INITIALIZED, SYSTEM_INITIALIZED, SYSTEM_HALTED, INFO, WARNING,
	ERROR, DAT_RECIEVED, DATA_ANALYSIS_STARTED, DATA_ALPHA_COUNT, DATA_NUMERIC_COUNT, DATA_PUNCTUATION_COUNT,
	DATA_MISC_COUNT, DATA_ANALYSIS_COMPLETED
}status;

void log_data(uint8_t * ptr,uint32_t length);
void log_string(int8_t * ptr);
void log_integer(int32_t data);
void create_log_item(log * logptr, status log_id, int32_t length, int8_t * ptr);
void destroy_log_item(log * log1);
void log_item(log * logptr);
void log_flush(circ_buff * circ_pre);


#define LOG_IT(logptr, log_id, length, ptr); {\
	create_log_item(logptr, log_id, length, ptr);\
	log_item(logptr);\
	}

#define LOG_RAW_STRING(string) log_string(string)
#define LOG_RAW_INTEGER(data) log_integer(data)
#define LOG_RAW_DATA(pointer) log_data(pointer,length)

#endif /* SOURCES_LOGGER_H_ */
