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

#define START_CRITICAL() __disable_irq()
#define STOP_CRITICAL() __enable_irq()

uint32_t start_time;
uint32_t stop_time;
uint32_t diff;
uint32_t overflow;
/*****************************************************************************************************
*start_timer
*	description:function to configure and implement the timer
*	parameters:
		This function has no parameters
*   return : This function does not return anything
*****************************************************************************************************/
	void start_timer();
/*****************************************************************************************************
*read_count
*	description:function to disable the irq and incrementing the overflow flag and then clearning
				the flag by asserting it
*	parameters:
			This function has no parameters
*   return : This function returns the read count of the current state
*****************************************************************************************************/
	uint16_t read_count();

#endif /* SOURCES_PROFILER_H_ */
