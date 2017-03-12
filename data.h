/******************************************************
*   File: data.h
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
*              - my_itoa
*              - my_atoi
*	       - big_to_little32
*              - little_to_big32
*              - print_memory
*              
********************************************************/
#ifndef DATA_H
#define DATA_H
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#define MAX {0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,\
0xC,0xD,0xE,0xF,0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF}

/*////////////////////////////////////////////////////////////////////////////////////////
//Name	   : my_itoa									//
//Params   : destination pointer,data ,base				    		//
//Function : This function converts the given data into its equivalent  		//	
//			 with the specified base and store the result as a string  	//
//		 	 in the memory location starting from destination pointer	// 
//Returns  : pointer to start of ascii string, or 0 for error				//
///////////////////////////////////////////////////////////////////////////////////////*/
int8_t * my_itoa(int8_t * str, int32_t data, int32_t base);
/*////////////////////////////////////////////////////////////////////////////////////////
//Name	   : my_atoi									//
//Params   : source pointer								//
//Function : This function converts the given ascii string 		 		//	
//			 starting from memory location pointed at by source   		//
//		 	 pointer to integer data value of base 10 provided 		//
//			 all characters are digits.					//
//Returns  : 32 bit data post conversion, or 0 for error				//
////////////////////////////////////////////////////////////////////////////////////////*/
int32_t my_atoi(int8_t * str);
/*////////////////////////////////////////////////////////////////////////////////////////
//Name	   : big_to_little32								//
//Params   : 32 bit pointer data, length						//
//Function : This function converts the given 32 bit data stored in  			//	
//			 big endian form starting from memory location pointed  	//
//		 	 at by data pointer to its little endian form. This 		//
//			 continues for provided length. length is number 		//
//			 of such 32 bit data entries					//
//Returns  : 0 for error, 1 for successful operation					//
////////////////////////////////////////////////////////////////////////////////////////*/
int8_t big_to_little32(uint32_t * data,uint32_t length);
/*////////////////////////////////////////////////////////////////////////////////////////
//Name	   : little_to_big32							        //
//Params   : 32 bit pointer data, length						//
//Function : This function converts the given 32 bit data stored in  			//	
//			 little endian form starting from memory location pointed  	//
//		 	 at by data pointer to its big endian form. This 		//
//			 continues for provided length. length is number 		//
//			 of such 32 bit data entries				        //
//Returns  : 0 for error, 1 for successful operation					//
///////////////////////////////////////////////////////////////////////////////////////*/
int8_t little_to_big32(uint32_t * data,uint32_t length);
/*////////////////////////////////////////////////////////////////////////////////////////
//Name	   : print_memory								//
//Params   : pointer start, length							//
//Function : This function prints contents of memory starting from  			//	
//			 memory location pointed at by start till the specified 	//
//		 	 length. It prints the hex equivalent of the data stored 	//
//Returns  : void return type								//
///////////////////////////////////////////////////////////////////////////////////////*/
void print_memory(uint8_t * start, uint32_t length);

#endif
