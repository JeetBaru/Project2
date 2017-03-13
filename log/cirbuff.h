/*
 * cirbuff.h
 *
 *  Created on: Mar 11, 2017
 *      Author: Jeet
 */

#ifndef _CIRBUFF_H_
#define _CIRBUFF_H_

# include <stdint.h>
# include <stdlib.h>

typedef struct circ_buff_t{
	uint8_t * buff;
	uint8_t * head;
	uint8_t * tail;
	uint32_t count;
	uint32_t size;
}circ_buff;

circ_buff * circ_ptr;
circ_buff * circ_pre;

typedef enum {
	FULL,EMPTY,NO,INVALID_POINTER,SUCCESS,WRAP_AROUND_SUCCESS
}rt;

int8_t is_buffer_full(circ_buff * cb1);
int8_t is_buffer_empty(circ_buff * cb1);
int8_t initialize_buffer(circ_buff * cb1, uint32_t size);
int8_t destroy_buffer(circ_buff * cb1);
int8_t add_item(circ_buff * cb1, uint8_t data);
int8_t remove_item(circ_buff * cb1);
int8_t cirbuf_peak(circ_buff*cb1, uint8_t index);


#endif /* CIRBUFF_H_ */
