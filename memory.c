/******************************************************
*   File: memory.c
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
*              - my_memmove
*              - my_memset
*	       - my_memzero
*              - my_rev
*              
********************************************************/
#include "memory.h"
#include "uni.h"

	
//This function moves data of specified length from source location to destination. The on moving to the destination the data at source is made zero.
int8_t my_memmov(uint8_t * scr, uint8_t * dest,uint32_t length)
{
	int8_t i;
	if((!scr) || (!dest))					// if either pointer arguement is null return zero
	{
		return NULL_PTR;
	}
	if(scr>dest)							// if source pointer is less than dest pointer begin moving from begining
	{
		for(i=0;i<length;i++)
		{
			*(dest+i)=*(scr+i);				// copy contents from source to destination
			*(scr+i)=0;						//set contents of source to 0 post moving
		}
	}
	else 									// if source pointer is greater than dest pointer begin moving from end
	{
		for(i=length-1;i>=0;i--)
		{
			*(dest+i)=*(scr+i);				// copy contents from source to destination
			*(scr+i)=0;						//set contents of source to 0 post moving
		}		
	}
	return SUCCESS;
}

//copies the specified value of data onto the memory location pointed by the source pointer for length l. The data in memory from 
//address of source pointer till specified length is overwritten by value.

int8_t my_memset(uint8_t * scr, uint32_t length,uint8_t value)
{
	int8_t i;
	if(!scr)							// if pointer arguement is null return zero
	{
		return NULL_PTR;
	}
	for(i=0;i<length;i++)
	{
		*(scr+i)=value;					// set the value of mem location to value
	}	
	return SUCCESS;	
}


//copies 0 onto the memory location pointed by the source pointer for given length. The data in memory from address of source 
 //pointer till specified length is overwritten by 0.
int8_t my_memzero(uint8_t *scr, uint32_t length)
{
	int8_t i;
	if(!scr)							// if pointer arguement is null return zero
	{
		return NULL_PTR;
	}
	for(i=0;i<length;i++)
	{
		*(scr+i)=0; 					// set the value of mem location to value
	}
	return SUCCESS;
}

//This function reverses an array of all elements inthe memorylocation starting at address pointed by  
//the source pointer till length specified.

int8_t my_rev(uint8_t * ptr,uint32_t length)
{
	length=length-1; 
	int32_t l;
	if(!ptr)
	{
		return NULL_PTR;
	}
	if(length%2==0)						// For even length, l=length for swapping
	{
		l=length/2;
	}
	else 								// For odd length
	{
		l=(length-1)/2;
	}
	int8_t i;
	int8_t temp;
	for(i=0;i<=l;i++)
	{
		temp=*(ptr+i);					//swapping data on mem to reverse 
		*(ptr+i)=*(ptr+length-i);
		*(ptr+length-i)=temp;
	}
	return SUCCESS;
}
