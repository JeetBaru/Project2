#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef _CIRBUFF_H
#define _CIRBUFF_H

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
