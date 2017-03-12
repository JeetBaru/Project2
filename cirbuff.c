/******************************************************
*   File: cirbuff.c
*
*   Copyrights 2016  Sudeep Kulkarniirlekar and Jeet Baru
*   All Rights Reserved
*
*
*   The information contained herein is property of the Authors. 
*   The copying and distribution of the files is prohibited except
*   by express written agreement with the Authors.
*
*
*   Authors: Sudeep Kulkarniirlekar and Jeet BAru
*   Date Edited: 12 March 2017
*
*   Description: Source file for implementing Circular buffer functions
*              - CircBuf_size 
*              - is_buffer_full
*	       - is_buffer_empty
*              - initialize_buffer
*              - destroy_buffer
*              - add_item
*              - remove_item
*	       - cirbuf_peak
*
********************************************************/

#include "cirbuff.h"
#include "uni.h"

//allocates size to the buffer 
int8_t CircBuf_size(circ_buff*cb1)
{   if (!cb1)
		return INVALID_POINTER;
    cb1= malloc(sizeof(circ_buff));
    return SUCCESS;

}
//checks whether the buffer is full
int8_t is_buffer_full(circ_buff * cb1)
{	//overfill
	if (!cb1)
		return INVALID_POINTER;
	if(cb1->count == cb1->size)						//if count is equal to size then buffer is full
		return FULL;
	else
		return NO;
}
//checks whether the buffer is empty
int8_t is_buffer_empty(circ_buff * cb1)
{	
	//overempty
	if (!cb1)
		return INVALID_POINTER;						//if null pointer passed returns invalid pointer
	if(cb1->count == 0)							//if count is zero then buffer is empty
		return EMPTY;
	else
		return NO;
}
//initializes the buffer by bringing buff, head, tail at same position
int8_t initialize_buffer(circ_buff * cb1, uint8_t size)
{       if (!cb1)
		return INVALID_POINTER;
	cb1->buff = (int8_t *)calloc(size,(sizeof(int8_t)));			//allocated the size to buff
	cb1->head = cb1->buff;
	cb1->tail = cb1->buff;							//brought head, tail to buff position at initial condition
	cb1->size = size;
	cb1->count = 0;								//count is set to zero			
	return SUCCESS;
}		
//destroyes the buffer
void destroy_buffer(circ_buff * cb1)
{
	free(cb1->buff);
}
//adds an item to the head position
int8_t add_item(circ_buff * cb1, int8_t data)
{
	if (!cb1)
		return INVALID_POINTER;
	if(cb1){					     			//checking the wrap around condition by setting head to buff position 																			
		if(cb1->buff+cb1->size-1<=cb1->head){										
			cb1->head=cb1->buff;	
			*(cb1->head)=data;
			cb1->count++;
			return WRAP_AROUND_SUCCESS;
		}	
		else{
			*(cb1->head)=data;	
			cb1->head++;	
			cb1->count++;
			return SUCCESS;			//added the data at head's position by dereferencing
		}
	}
	
	//return SUCCESS;
   	
}
//removes item from the buffer by incrementing tail
uint8_t remove_item(circ_buff * cb1)
{
	if (!cb1)
		return INVALID_POINTER;
	if(cb1){
		if(cb1->tail==cb1->buff+cb1->size-1){ 				//wrap around condition tail is moved to buff position
			cb1->tail=cb1->buff;
			cb1->count--;
			return WRAP_AROUND_SUCCESS;
		}
		else{
			cb1->tail++;	
			cb1->count--;
			return SUCCESS;					//tail is incremented 
		}
		
	}
										//wrap_around_success
	
}
//gives the value at the required index position in circular buffer
uint8_t cirbuf_peak(circ_buff*cb1, uint8_t index)
{	
	if (!cb1)
		return INVALID_POINTER;
    	uint8_t data;
     	data =  *(cb1->buff+index);						//checks the data by dereferencing the pointer at the index
     	return data;
}
