/*
 * profiler.h
 *
 *  Created on: Apr 14, 2017
 *      Author: Jeet
 */

#ifndef SOURCES_PROFILER_H_
#define SOURCES_PROFILER_H_

#ifdef VERBOSE
	#include "time.h"
	#define START_TIMER() clock_gettime(CLOCK_REALTIME, &t1)
	#define STOP_TIMER() clock_gettime(CLOCK_REALTIME, &t2)
#define DIFFERENCE() ((t2.tv_sec - t1.tv_sec)*1000000000 + (t2.tv_nsec - t1.tv_nsec))
#else
	#define START_TIMER() read_count()
	#define STOP_TIMER() read_count()
	#define DIFFERENCE() (stop_time + (overflow * (65536)) - start_time)*0.047
#endif

uint32_t start_time;
uint32_t stop_time;
uint32_t diff;
uint32_t overflow;

void start_timer();
uint16_t read_count();

#endif /* SOURCES_PROFILER_H_ */
