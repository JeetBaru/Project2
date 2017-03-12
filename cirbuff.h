/*
 * cirbuff.h
 *
 *  Created on: Mar 11, 2017
 *      Author: Jeet
 */

#ifndef CIRBUFF_H_
#define CIRBUFF_H_

#ifndef SOURCES_CIRBUFF_H_
#define SOURCES_CIRBUFF_H_

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
	FULL,EMPTY,NO
}rt;

int8_t is_buffer_full(circ_buff * cb1);
int8_t is_buffer_empty(circ_buff * cb1);
void initialize_buffer(circ_buff * cb1, uint32_t size);
void destroy_buffer(circ_buff * cb1);
void add_item(circ_buff * cb1, uint8_t data);
uint8_t remove_item(circ_buff * cb1);

#endif


#endif /* CIRBUFF_H_ */
