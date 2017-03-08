/*
 * logger.h
 *
 *  Created on: Mar 3, 2017
 *      Author: Jeet
 */

#ifndef SOURCES_LOGGER_H_
#define SOURCES_LOGGER_H_

typedef struct log_t{
	int8_t logid;
	int8_t length;
	int8_t * payload;
}log;

log * log1;

typedef enum log_status_t{
	LOGGER_INITIALIZED=1, GPIO_INITIALIZED, SYSTEM_INITIALIZED, SYSTEM_HALTED, INFO, WARNING,
	ERROR, DATA_RECIEVED, DATA_ANALYSIS_STARTED, DATA_ALPHA_COUNT, DATA_NUMERIC_COUNT, DATA_PUNCTUATION_COUNT,
	DATA_MISC_COUNT, DATA_ANALYSIS_COMPLETED
}status;

void log_data();
void log_string();
int8_t * my_itoa(int8_t * str, int32_t data, int32_t base);
void log_integer();
void create_log_item(log * logptr, status log_id, int32_t length, int8_t * ptr);
void log_item(log * logptr);
void analyse_data(int8_t * c);

#endif /* SOURCES_LOGGER_H_ */
