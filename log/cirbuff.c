
/**************************************************************************************
*   File: cirbuff.h
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
*   Authors: Sudeep Kulkarniirlekar and Jeet Baru
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
****************************************************************************************/

# include "cirbuff.h"

//allocates size to the buffer
int8_t CircBuf_size(circ_buff * cb1)
{
    cb1= malloc(sizeof(circ_buff));							//allocates memory in heap
    return SUCCESS;
}

//checks if buffer is full
int8_t is_buffer_full(circ_buff * cb1)
{
	if (!cb1)												//null pointer check
		return INVALID_POINTER;
	if(cb1->count == cb1->size)								//if number of elements in buffer = size, buffer full
		return FULL;
	else
		return NO;
}


//checks if buffer empty
int8_t is_buffer_empty(circ_buff * cb1)
{
	if (!cb1)
		return INVALID_POINTER;								//null pointer check
	if(cb1->count == 0)										//if number of elements = 0, buffer empty
		return EMPTY;
	else
		return NO;
}

//initializes elements of the structure
int8_t initialize_buffer(circ_buff * cb1, uint32_t size)
{
	if (!cb1)
		return INVALID_POINTER;								//null pointer check
	cb1->buff = (int8_t *)calloc(size,(sizeof(int8_t)));	//initialize memory in heap
	cb1->head = cb1->buff;									//initially head and tail point to 0th poistion
	cb1->tail = cb1->buff;
	cb1->size = size;										//size initialized to parameter passed
	cb1->count = 0;											//count = 0  initially
	return SUCCESS;
}

//used to disown the heap memory allocaed to the buffer
int8_t destroy_buffer(circ_buff * cb1)
{
	if (!cb1)												//null pointer check
		return INVALID_POINTER;
	free(cb1->buff);
	return SUCCESS;
}

//adds item to circular buffer
int8_t add_item(circ_buff * cb1, uint8_t data)
{
	if (!cb1)
		return INVALID_POINTER;								//null pointer check
	if(cb1){
		if(cb1->head==cb1->buff+cb1->size-1){				//if last position reached
			*(cb1->head)=data;								//put data in last position
			cb1->head=cb1->buff;							//reset the head to starting address
			cb1->count++;
			return WRAP_AROUND_SUCCESS;
		}
		else{
			*(cb1->head)=data;								//else enter data in next position
			cb1->head++;
			cb1->count++;
			return SUCCESS;
		}
	}
}

//remove item from circular buffer
int8_t remove_item(circ_buff * cb1)
{
	if (!cb1)
		return INVALID_POINTER;								//null pointer check
	if(cb1){
		if(cb1->tail==cb1->buff+cb1->size-1){				//if last position reached
			cb1->tail=cb1->buff;							//reset pointer to buff
			cb1->count--;
			return *(cb1->buff+cb1->size-1);				//return last position data
		}
		else{
			cb1->tail++;
			cb1->count--;
			return *(cb1->tail-1);							//else increament tail and return data
		}
	}
}

//dereference the required position and return
int8_t cirbuf_peak(circ_buff*cb1, uint8_t index)
{
    uint8_t data;
    data =  *(cb1->buff+index);								//checks the data by dereferencing the pointer at the index
    return data;
}
