# include <stdint.h>
# include <stdlib.h>
#include "cirbuff.h"

int8_t CircBuf_size(circ_buff*cb1)
{
    cb1= malloc(sizeof(circ_buff));
    return SUCCESS;

}

int8_t is_buffer_full(circ_buff * cb1, uint8_t count, uint8_t size)
{	//overfill
	
	cb1->count = count;
	cb1->size = size;
	if(cb1->count == cb1->size )
		return FULL;
	else
		return NO;
}

int8_t is_buffer_empty(circ_buff * cb1, uint8_t count)
{	
	//overempty
	if (!cb1)
		return INVALID_POINTER;
	cb1->count = count;
	if(cb1->count == 0)
		return EMPTY;
	else
		return NO;
}

int8_t initialize_buffer(circ_buff * cb1, int8_t size)
{
	cb1->buff = (int8_t *)calloc(size,(sizeof(int8_t)));
	cb1->head = cb1->buff;
	cb1->tail = cb1->buff;
	cb1->size = size;
	cb1->count = 0;
	return SUCCESS;
}

void destroy_buffer(circ_buff * cb1)
{
	free(cb1->buff);
}

int8_t add_item(circ_buff * cb1, int8_t data)
{
	if(cb1){
		if(cb1->head==cb1->buff+cb1->size-1){
			cb1->head=cb1->buff;
			*(cb1->head)=data;
		}
		else{
			cb1->head++;
			*(cb1->head)=data;
		}
	}
	cb1->count++;
   	return WRAP_AROUND_SUCCESS;
}

uint8_t remove_item(circ_buff * cb1, uint8_t size)
{
	
	if(cb1){
		if(cb1->tail==cb1->buff+cb1->size-1){
			cb1->tail=cb1->buff;
		}
		else{
			cb1->tail++;
		}
		cb1->count--;
	}
	return WRAP_AROUND_SUCCESS;
	
}

