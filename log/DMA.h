/*
 * DMA.h
 *
 *  Created on: Apr 14, 2017
 *      Author: Jeet
 */

#ifndef SOURCES_DMA_H_
#define SOURCES_DMA_H_

# include <stdint.h>
# include "MKL25Z4.h"

#define START_CRITICAL() __disable_irq()
#define STOP_CRITICAL() __enable_irq()

typedef enum dma_status_t{
	DMA_NULL_POINTER, DMA_SUCCESS, DMA_NULL_LENGTH
}dma_status;

/*****************************************************************************************************
*dma_memmove
*	description:This function consists of DMA only Logic for memove. It takes care of overlap as well
*	parameters:
		This function takes source pointer, destination pointer and length of data as paramenters
*   return : This function Sucess or Error enum
********************************************************************************************/
dma_status dma_memmove(int8_t * source, int8_t * dest, int16_t length);

/*****************************************************************************************************
*dma_memzero
*	description:This function consists of DMA only Logic for memzero. 

*	parameters:
		This function takes destination pointer and length of data as paramenters
*   return : This function Sucess or Error enum
********************************************************************************************/
dma_status dma_memzero( int8_t * d, int16_t l);

/*****************************************************************************************************
*dma_memmove_32
*	description:This function consists of DMA and processor memmov Logic for memove. It provides for 
* an accelerated transfer speed. It uses 32 bit DMA transfers.
*	parameters:
		This function takes source pointer, destination pointer and length of data as paramenters
*   return : This function Sucess or Error enum
********************************************************************************************/
dma_status dma_memmove_32(int8_t * s, int8_t * d, int16_t l);

/*****************************************************************************************************
*dma_memmove_16
*	description:This function consists of DMA and processor memmov Logic for memove. It provides for 
* an accelerated transfer speed. It uses 16 bit DMA transfers.
*	parameters:
		This function takes source pointer, destination pointer and length of data as paramenters
*   return : This function Sucess or Error enum
********************************************************************************************/
dma_status dma_memmove_16(int8_t * s, int8_t * d, int16_t l);

/*****************************************************************************************************
*dma_memmove_8
*	description:This function consists of DMA and processor memmov Logic for memove. It provides for 
* an accelerated transfer speed. It uses 8 bit DMA transfers.
*	parameters:
		This function takes source pointer, destination pointer and length of data as paramenters
*   return : This function Sucess or Error enum
********************************************************************************************/
dma_status dma_memmove_8(int8_t * s, int8_t * d, int16_t l);

/*****************************************************************************************************
*dma_memzero_32
*	description:This function consists of DMA and processor memzero Logic for memzero. It provides for 
* an accelerated transfer speed. It uses 32 bit DMA transfers.
*	parameters:
		This function takes source pointer, destination pointer and length of data as paramenters
*   return : This function Sucess or Error enum
********************************************************************************************/
dma_status dma_memzero_32(int8_t * d, int16_t l);

/*****************************************************************************************************
*dma_memzero_16
*	description:This function consists of DMA and processor memzero Logic for memzero. It provides for 
* an accelerated transfer speed. It uses 16 bit DMA transfers.
*	parameters:
		This function takes source pointer, destination pointer and length of data as paramenters
*   return : This function Sucess or Error enum
********************************************************************************************/
dma_status dma_memzero_16(int8_t * d, int16_t l);

/*****************************************************************************************************
*dma_memzer_8
*	description:This function consists of DMA and processor memzero Logic for memzero. It provides for 
* an accelerated transfer speed. It uses 8 bit DMA transfers.
*	parameters:
		This function takes source pointer, destination pointer and length of data as paramenters
*   return : This function Sucess or Error enum
********************************************************************************************/
dma_status dma_memzero_8(int8_t * d, int16_t l);


void dma_move(int8_t * s, int8_t * d, int16_t l);

#endif /* SOURCES_DMA_H_ */
