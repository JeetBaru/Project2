/************************************************************************************************************
*   File: test_memory.c
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
*              	test_memmove_Invalid_Pointer
*    		test_memmove_NoOverlap
*   		test_memove_SRC_in_DST
*    		test_memove_DST_in_SRC
*    		test_memset_Invalid_Pointers
*    		test_memset_Check_set
*    		test_memzero_Invalid_Pointer
*    		test_memzero_Check_set
*    		test_reverse_Invalid_Pointer
*    		test_CheckOddReverse
*    		test_CheckEvenReverse
*    		test_reverse_CheckCharacters
*
**************************************************************************************************************/
#include<math.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "memory.h"
#include "uni.h"

/*******************************************************************************************************************
*Invalid Pointer
*		description: 	
			This function chekcs whether the pointer being passed is valid, to check this a null
			pointer is passed, the chekcing is done by using cmocka unit test framework
		parameters:
		   	The parameters of the function call
			*scr - pointer to the source
			*dst - pointer to the destination
     uint32_t length - 	lenght of data to be moved
*		returns:
			compares the status of the enum for the test condition and returns pass or fail when we 
			give command make test TEST="memory"
******************************************************************************************************************/
void test_memmove_Invalid_Pointer(void **state)
{ 
  	uint8_t set_2[]= {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};
  	uint8_t *ptr;
  	ptr = set_2;
  	ptr=0; 
  	uint8_t *pt = set_2; 
  	enum rt status = my_memmov(ptr, pt+6, 6);			//null pointer is passed
  	assert_int_equal(status, NULL_PTR);
}
/*******************************************************************************************************************
*Nooverlap
*		description: 	
			This function chekcs whether the function being called works properly without overlap
			this checking is done with the help of cmocka unit test framework
		parameters:
		   	The parameters of the function call
			*scr - pointer to the source
			*dst - pointer to the destination
     uint32_t length - 	lenght of data to be moved
*		returns:
			compares the status of the enum for the test condition and returns pass or fail when we 
			give command make test TEST="memory"
*******************************************************************************************************************/
void test_memmove_NoOverlap(void **state)
{
  	uint8_t set_2[]= {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};
  	uint8_t *ptr = set_2;
  	enum rt status = my_memmov(ptr + 25, ptr + 19, 6); 		 // no overlap condition
  	assert_int_equal(status, SUCCESS);
}
/*********************************************************************************************************************
*Overlap(Source in Destination)
*		description: 
			This function checks whether the function being called works properly with the overlap
			(source in destination), this checking is done with the help of cmocka unit
			test framework.
		parameters:
		   	The parameters of the function call
			*scr - pointer to the source
			*dst - pointer to the destination
     uint32_t length - 	lenght of data to be moved
*		returns:
			compares the status of the enum for the test condition and returns pass or fail when we 
			give command make test TEST="memory"
***********************************************************************************************************************/
void test_memove_SRC_in_DST(void **state)
{
  	uint8_t set_2[]= {1,2,3,4,5,6,7,8,9};
  	uint8_t *ptr = set_2;
  	enum rt status = my_memmov(ptr , ptr + 2, 5);	       //source and destination are now overlaping with source in destination
  	assert_int_equal(status, SUCCESS);
}
/*****************************************************************************************************************
*Overlap(Source in Destination)
*		description: 
			This function checks whether the function being called works properly with the overlap
			(destination in source), this checking is done with the help of cmocka unit
			test framework.
		parameters:
		   	The parameters of the function call
			*scr - pointer to the source
			*dst - pointer to the destination
     uint32_t length - 	lenght of data to be moved
*	returns:
			compares the status of the enum for the test condition and returns pass or fail when we 
			give command make test TEST="memory"
******************************************************************************************************************/
void test_memove_DST_in_SRC(void **state)
{
  	uint8_t set_2[]= {1,2,3,4,5,6,7,8,9};
  	uint8_t *ptr = set_2;
  	enum rt status = my_memmov(ptr + 2, ptr , 5);			//destination in source overlaping condition
  	assert_int_equal(status, SUCCESS);
}

//memset
/*********************************************************************
*Invalid pointer
*		description: 
			This function checks whether the pointer passed to the function is valid. To check the 
			condition a null pointer is passed to the function being called. Cmocka unit test
			framework is used for the same.
		parameters:
		   	The parameters of the function call
			*scr - pointer to the source
     uint32_t length - 	length on which a particular value is to be written
     uint8_t value   - 	the value that is to be set for the length given
*		returns:
			compares the status of the enum for the test condition and returns pass or fail when we 
			give command make test TEST="memory"
******************************************************************************************************************/

void test_memset_Invalid_Pointers(void **state)
{
  	uint8_t set_2[]= {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};
  	uint8_t *ptr = set_2;
  	ptr = 0;
  	uint8_t length = 4;
  	enum rt status = my_memset(ptr, length, 0xEE);		//null pointer is passed
  	assert_int_equal(status, NULL_PTR);
}
/*******************************************************************************************************************
*Check_set
*		description: 
			This function checks whether the function writes the value given properly in the given 
			length, cmocka unit test framework has been used to check the functionality.
		parameters:
		   	The parameters of the function call
			*scr - pointer to the source
     uint32_t length - length on which a particular value is to be written
     uint8_t value   - the value that is to be set for the length given
*		returns:
			compares the status of the enum for the test condition and returns pass or fail when we 
			give command make test TEST="memory"
*********************************************************************************************************************/
void test_memset_Check_set(void **state)
{
	uint8_t set_2[]= {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};
  	uint8_t length = 4;
  	uint8_t *ptr = set_2;
  	enum rt status = my_memset(ptr+15, length, 0xEE);	//0xEE is being passed to a length of 4.
  	assert_int_equal(status, SUCCESS);
}	

//memzero
/**********************************************************************************************************************
*Invalid pointer
*		description: 
			This function checks whether the pointer passed to the function is valid. To check the 
			condition a null pointer is passed to the function being called. Cmocka unit test
			framework is used for the same.
		parameters:
		   	The parameters of the function call
			*scr - pointer to the source
     uint32_t length -	length on which a particular value is to be written
     
*		returns:
			compares the status of the enum for the test condition and returns pass or fail when we 
			give command make test TEST="memory"
*************************************************************************************************************************/
void test_memzero_Invalid_Pointer(void **state)
{
  	uint8_t set_2[]= {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};
  	uint8_t length = 32;
  	uint8_t *ptr = set_2;
  	ptr=0;
  	enum rt status= my_memzero(ptr, length);		//null pointer is being passed
  	assert_int_equal(status, NULL_PTR);
}
/***********************************************************************************************************************
*Check_zero
*		description: 	
			This function checks whether the function writes zero, in the given 
			length, cmocka unit test framework has been used to check the functionality.
		parameters:
		   	The parameters of the function call
			*scr - pointer to the source
     uint32_t length - 	length on which a particular value is to be written
     
*		returns:
			compares the status of the enum for the test condition and returns pass or fail when we 
			give command make test TEST="memory"
***************************************************************************************************************************/
void test_memzero_Check_set(void **state)
{
  	uint8_t set_2[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31}; 
  	uint8_t length = 32;
  	uint8_t *ptr = set_2;
  	enum rt status= my_memzero(ptr, length);
  	assert_int_equal(status, SUCCESS);
}
//Reverse
/************************************************************************************************************************
*Invalid pointer
*		description: 
			This function checks whether the pointer passed to the function is valid. To check the 
			condition a null pointer is passed to the function being called. Cmocka unit test
			framework is used for the same.
		parameters:
		   	The parameters of the function call
			ptr - pointer pointing to first element of data array
     uint32_t length - length which is to be reversed
     
*		returns:
			compares the status of the enum for the test condition and returns pass or fail when we 
			give command make test TEST="memory"
***************************************************************************************************************************/
void test_reverse_Invalid_Pointer(void **state)
{
  	uint8_t *ptr;
  	ptr=0;
  	uint8_t length = 10;
  	enum rt status= my_rev(ptr, length);		//null pointer is passed
  	assert_int_equal(status, NULL_PTR);
}
/************************************************************************************************************************
*Check_odd_reverse
*		description: 
			This function checks whether the function being called is able to reverse an odd length 
			of data, to check this cmocka unit test framework is used
		parameters:
		  	The parameters of the function call
			ptr - pointer pointing to first element of data array
     uint32_t length - length which is to be reversed
     
*		returns:
			compares the status of the enum for the test condition and returns pass or fail when we 
			give command make test TEST="memory"
***************************************************************************************************************************/
void test_CheckOddReverse(void **state)
{
  	uint8_t set_2[]= {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};
  	uint8_t length = 11;				//odd length input is given
  	uint8_t *ptr = set_2;
  	enum rt status= my_rev(ptr, length);
  	assert_int_equal(status, SUCCESS);
  
}
/****************************************************************************************************************************
*Check_even_reverse
*		description: 
			This function checks whether the function being called is able to reverse an even length 
			of data, to check this cmocka unit test framework is used
		parameters:
		   	The parameters of the function call
			ptr - pointer pointing to first element of data array
     uint32_t length - length which is to be reversed
     
*		returns:
			compares the status of the enum for the test condition and returns pass or fail when we 
			give command make test TEST="memory"
***************************************************************************************************************************/
void test_CheckEvenReverse(void **state)
{
  	uint8_t set_2[]= {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};
  	uint32_t length = 12;				//even length input is given 
  	uint8_t * ptr = set_2;
  	enum rt status= my_rev(ptr, length);
  	assert_int_equal(status, SUCCESS);
}
/*******************************************************************************************************************************
*Check_characters
*		description: 
			This function checks whether the function being called is able to reverse any given length of 
			array of characters, to check this cmocka unit test framework is used.
		parameters:
		   	The parameters of the function call
			ptr - pointer pointing to first element of data array
     uint32_t length - length which is to be reversed
     
*		returns:
			compares the status of the enum for the test condition and returns pass or fail when we 
			give command make test TEST="memory"
*********************************************************************************************************************************/
void test_reverse_CheckCharacters(void **state)
{	
	uint8_t i, length = 255;
	uint8_t set_2[255];				//created an array of 255 length
	for (i=0; i<length; i++)			//passed character 'a' to each position in the array
	{
		set_2[i] = 'a';
	}		
  	uint8_t *ptr = set_2;
  	enum rt status= my_rev(ptr, length);		//checkes whether the given array could be reversed by the reverse function
  	assert_int_equal(status, SUCCESS);
}
//int main has the cmocka unit tests framwork which checks the whether the condition is failed or passed.
int main(int argc, char **argv)
{
	time_t rawtime;
  	struct tm * timeinfo;
  	time ( &rawtime );
  	timeinfo = localtime ( &rawtime );
  	printf ( "Execution time and date: %s", asctime (timeinfo) );   //invoked time.h to report current execution time and date
  const struct CMUnitTest tests[] = {
    	cmocka_unit_test(test_memmove_Invalid_Pointer),
    	cmocka_unit_test(test_memmove_NoOverlap),
    	cmocka_unit_test(test_memove_SRC_in_DST),
    	cmocka_unit_test(test_memove_DST_in_SRC),
    	cmocka_unit_test(test_memset_Invalid_Pointers),
    	cmocka_unit_test(test_memset_Check_set),
    	cmocka_unit_test(test_memzero_Invalid_Pointer),
    	cmocka_unit_test(test_memzero_Check_set),
    	cmocka_unit_test(test_reverse_Invalid_Pointer),
    	cmocka_unit_test(test_CheckOddReverse),
    	cmocka_unit_test(test_CheckEvenReverse),
    	cmocka_unit_test(test_reverse_CheckCharacters)
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
