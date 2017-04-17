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
/*****************************************************************************************************
*buffer full
*	description:This function checks whether the buffer is full by comparing the count and 
		    length 
*	parameters:
		  circ_buff*cb1 -This function parameter is the pointer of the structure type
				circ_buff which is essentially the object of circ_buff_t		
*	returns:
		Returns an enum which dictates the status of whether it is Successful or not
*****************************************************************************************************/
__attribute__((always_inline)) static inline int8_t is_buffer_full(circ_buff * cb1)
{
	if(cb1->count == cb1->size)
		return FULL;
	else 
		return NO;
}
/*****************************************************************************************************
*empty
*	description:This function checks wheter the buffer is empty by checking if the 
			count is zero
*	parameters:
		circ_buff*cb1 -This function parameter is the pointer of the structure type
				circ_buff which is essentially the object of circ_buff_t
		
*	returns:
			Returns a pointer to the starting location of the reversed
			series of bytes
*****************************************************************************************************/
__attribute__((always_inline)) static inline int8_t is_buffer_empty(circ_buff * cb1)
{
	if(cb1->count == 0) 
		return EMPTY;
	else
		return NO;
}
/*****************************************************************************************************
*initialise
*	description:This function initialises the circular buffer by allocating the 
		    size for a pointer buff, and then brings head, tail and buff to 	
		    same position
*	parameters:
		circ_buff*cb1 -This function parameter is the pointer of the structure type
				circ_buff which is essentially the object of circ_buff_t
		  uint8_t size - This variable is the fixed length of the circular buffer.
*	returns:
			Returns an enum saying the buffer has been initialised, also it 
			sets the size of the circular buffer 
*****************************************************************************************************/
int8_t initialize_buffer(circ_buff * cb1, uint32_t size);
/*****************************************************************************************************
*destroy
*	description:This function will destroy the memory that has been allcated
			on the heap by using "free"
*	parameters:
		circ_buff*cb1 -This function parameter is the pointer of the structure type
				circ_buff which is essentially the object of circ_buff_t
*	returns:
		It is a void function and does not return anything
*****************************************************************************************************/
int8_t destroy_buffer(circ_buff * cb1);
/*****************************************************************************************************
*add_item
*	description:This function adds an item in the buffer and increments the head position by 	
			1, this function also takes care of wrap around condition.
*	parameters:
		circ_buff*cb1 -This function parameter is the pointer of the structure type
				circ_buff which is essentially the object of circ_buff_t
		int8_t data - This variable is the data to be added at the head position 
				in the circular buffer
*	returns:
		This function returns an enum WRAP_AROUND_SUCCESS when head's position is ahead
		of the size, or SUCCESS for general condtion
********************************************************************************************************/
int8_t add_item(circ_buff * cb1, uint8_t data);
/*****************************************************************************************************
*remove item
*	description:This function removes item from the circular buffer, here we read the data
			that is present at the tail and increment the tail, this function also 
			takes care of wrap around condition on its own
*	parameters:
		circ_buff*cb1 -This function parameter is the pointer of the structure type
				circ_buff which is essentially the object of circ_buff_t
*	returns:
			Returns either an enum if there is WRAP_AROUND_CONDITION is there
			or returns data that is being removed  
*****************************************************************************************************/
int8_t remove_item(circ_buff * cb1);
/*****************************************************************************************************
*data at particular position
*	description:This function gives the value at the index in the circular buffer by dereferencing
			the pointer at index in the circular buffer
*	parameters:
		circ_buff*cb1 -This function parameter is the pointer of the structure type
				circ_buff which is essentially the object of circ_buff_t
		  uint8_t index - This variable's value should be less than or equal to size
				to get the value at that position in circular buffer
*	returns:
			Returns data at the index passed in the circular buffer
*****************************************************************************************************/
int8_t cirbuf_peak(circ_buff*cb1, uint8_t index);


#endif /* CIRBUFF_H_ */
