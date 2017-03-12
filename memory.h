/******************************************************
*   File: memory.h
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
#ifndef MEMORY_H
#define MEMORY_H

#include<stdio.h>
#include<stdint.h>
#include<time.h>


/*////////////////////////////////////////////////////////////////////////////////////////
//Name	   : my_memmov									//
//Params   : source pointer, destination pointer, length				//
//Function : This function moves data of specified length 				//	
//			 from source location to destination. The on moving 		//
//			 to the destination the data at source is made zero.		//
//Returns  : 0 for error, 1 for successful operation					//
///////////////////////////////////////////////////////////////////////////////////////*/
int8_t my_memmov(uint8_t * scr, uint8_t * dest,uint32_t length);
//////////////////////////////////////////////////////////////////////////////////////////
//Name	   : my_memset									//
//Params   : source pointer, data, length						//
//Function : This function copies the specified value of data onto 			//	
//			 the memory location pointed by the source pointer for 		//
//			 length l. The data in memory from address of source 		//
//			 pointer till specified length is overwritten by value.		// 
//Returns  : 0 for error, 1 for successful operation					//
///////////////////////////////////////////////////////////////////////////////////////*/
int8_t my_memset(uint8_t * scr, uint32_t length,uint8_t value);
/*////////////////////////////////////////////////////////////////////////////////////////
//Name	   : my_memzero									//
//Params   : source pointer, length							//
//Function : This function copies 0 onto the memory location pointed			//	
//			 by the source pointer for given length. The data in memory	//
//			 from address of source pointer till specified length		//
//			 is overwritten by 0.						// 
//Returns  : 0 for error, 1 for successful operation					//
////////////////////////////////////////////////////////////////////////////////////////*/
int8_t my_memzero(uint8_t *scr, uint32_t length);
/*////////////////////////////////////////////////////////////////////////////////////////
//Name	   : my_rev									//
//Params   : source pointer, length							//
//Function : This function reverses an array of all elements in   			//	
//			 the memorylocation starting at address pointed by  		//
//			 the source pointer till length specified.  			// 
//Returns  : 0 for error, 1 for successful operation					//
///////////////////////////////////////////////////////////////////////////////////////*/
int8_t my_rev(uint8_t * ptr,uint32_t length);

#endif
