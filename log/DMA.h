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

typedef enum dma_status_t{
	DMA_NULL_POINTER, DMA_SUCCESS
}status;

status dma_memmove(int8_t * source, int8_t * dest, int16_t length);
status dma_memzero( int8_t * d, int16_t l);
void dma_move(int8_t * s, int8_t * d, int16_t l);

#endif /* SOURCES_DMA_H_ */
