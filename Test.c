/**************************************************************************************
*   File: Test.c
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
*              	test_Allocate_Free
*    		test_Invalid_Pointer
*   		test_Non_Initialised_Buffer
*   		test_Buffer_Full
*    		test_Buffer_empty
*    		test_wrap_add
*    		test_wrap_remove
*    		test_overfill
*    		test_overempty
*    		test_Add_remove
*
****************************************************************************************/
#include<math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "data.h"
#include "memory.h"
#include "cirbuff.h"
#include "uni.h"

/****************************************************************************************************************
*Invalid pointer
*	description:
			This function checks whether the pointer being passed is valid, by invoking big_to_little32
			and passing a null pointer, the unit test is being done with the help of cmocka 
			unit test framework.
*	parameters:
			The function call big_to_little32 has the function parameter ptr and length of 
			the data which is being passed
*	returns:
			compares the status of the enum for the test condition and returns pass or fail when we 
			give command make test TEST="data"
****************************************************************************************************************/
void test_big_to_little_Invalid_Pointer(void **state)
{ 
  	uint32_t *ptr;
 	ptr=0; 						             //null pointer is passed 
  	uint32_t length=10 ;
  	enum rt status = big_to_little32(ptr, length);
  	assert_int_equal(status, NULL_PTR);
}
/****************************************************************************************************************
*valid_condtion
*	description:
			This function checks whether the function works properly by passing the data which is defined 
			in the data.h file with a preprocessed macro and passing the length. The cmocka unit test
			framework is being used to check the validity of the function.
*	parameters:
			The function call big_to_little32 has the function parameter ptr and length of 
			the data which is being passed
*	returns:
			compares the status of the enum for the test condition and returns pass or fail when we 
			give command make test TEST="data"
****************************************************************************************************************/
void test_big_to_little_Valid_condition(void **state)
{
  	uint32_t data[] = MAX;  
  	uint32_t length = 32;
  	uint32_t *ptr;
  	ptr = data;
  	enum rt status = big_to_little32(ptr, length);
  	assert_int_equal(status, SUCCESS);
}

/****************************************************************************************************************
*valid_condtion
*	description:
			This function checks whether the pointer being passed is valid, by invoking little_to_big32
			and passing a null pointer, the unit test is being done by cmocka unit test frame work
*	parameters:
			The function call big_to_little32 has the function parameter ptr and length of the data which is being passed
*	returns:
			compares the status of the enum for the test condition and returns pass or fail when we 
			give command make test TEST="data"
****************************************************************************************************************/

void test_little_to_big_Invalid_Pointer(void **state)
{
  	uint32_t *ptr;
  	ptr=0;
  	uint32_t length =10;
  	enum rt status = little_to_big32(ptr, length);			//null pointer is passed
  	assert_int_equal(status, NULL_PTR);
}
/****************************************************************************************************************
*valid_condtion
*	description:
			This function checks whether the function works properly by passing the data which is defined 
			in the data.h file with a preprocessed macro and passing the length. The cmocka unit test
			framework is being used to check the validity of the function.
*	parameters:
			The function call little_to_big32 has the function parameter ptr and length of 
			the data which is being passed

*	returns:
			compares the status of the enum for the test condition and returns pass or fail when we 
			give command make test TEST="data"
****************************************************************************************************************/
void test_little_to_big_Valid_condition(void **state)
{
  	uint32_t data[] = MAX;
  	uint32_t *ptr;
  	ptr=data;
  	uint32_t length = 32;
  	enum rt status= little_to_big32(ptr, length);
  	assert_int_equal(status, SUCCESS);
}


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

/*********************************************************************************************************
*allocate-free
*	description:
			This function checks whether the memory has been allocated to the circular buffer
		    	by using cmocka test framework. Where the ptr of the structure type is defined and
		    	CircBuf_size is called which is defined in cirbuff.h
*	parameters:
			The function call CircBuf_size has the function parameter ptr which is the sturcture 
		   	pointer 	
*	returns:
			compares the status of the enum for the test condition and returns pass or fail when we 
			give command make test TEST="cirbuff"
*********************************************************************************************************/
void test_Allocate_Free(void **state)
{ 
	circ_buff * ptr;
	ptr = (circ_buff *)malloc(sizeof(circ_buff));     //size allocated to the structure pointer
  	enum rt status = CircBuf_size(ptr);
  	assert_int_equal(status, SUCCESS);
}
/*********************************************************************************************************
*Invalid_pointer
*	description:
			This function checks whether the passed (ptr which is a structure pointer type)
			is valid or not by using cmocka unit test framework.
*	parameters:
			The function call is_buffer_empty has the function parameter count and ptr which is a 
			structure pointer
*	returns:
			compares the status of the enum for the test condition and returns pass or fail when we 
			give command make test TEST="cirbuff"
*********************************************************************************************************/
void test_Invalid_Pointer(void **state)
{
 	circ_buff * ptr;
	ptr = (circ_buff *)malloc(sizeof(circ_buff));
	ptr = 0;					  //null pointer is passed for Invalid pointer condition
  	enum rt status = is_buffer_empty(ptr, 5);
  	assert_int_equal(status, INVALID_POINTER);
}

/*********************************************************************************************************
*Non_initialise buffer
*	description: 
			This function checks whether the buffer is initialized by calling initialize_buffer
			in the function definition, and with the help of cmocka unit test framework
*	parameters:
			The function call initialize_buffer has the function parameter size and ptr which is a 
			structure pointer
		
*	returns:
			compares the status of the enum for the test condition and returns pass or fail when we 
			give command make test TEST="cirbuff"
*********************************************************************************************************/
void test_Non_Initialised_Buffer(void **state)
{
  	circ_buff * ptr;
	ptr = (circ_buff *)malloc(sizeof(circ_buff));
  	enum rt status= initialize_buffer(ptr,10);	//initialised_buffer is called to check if it is initialised or not
 	assert_int_equal(status, SUCCESS);
}
/*********************************************************************************************************
*test_Buffer_Full
*	description: 
			This function checks whether the buffer is full by calling is_buffer_full
			in the function definition, and with the help of cmocka unit test framework
*	parameters:
			The function call is_buffer_full has the function parameter size, count and ptr which is a 
			structure pointer
		
*	returns:
			compares the status of the enum for the test condition and returns pass or fail when we 
			give command make test TEST="cirbuff"
*********************************************************************************************************/
void test_Buffer_Full(void **state)
{
  	circ_buff * ptr;
	ptr = (circ_buff *)malloc(sizeof(circ_buff));
  	enum rt status= is_buffer_full(ptr, 10, 10);
  	assert_int_equal(status, FULL);
}
/*********************************************************************************************************
*test_Buffer_empty
*	description: 
			This function checks whether the buffer is empty by calling is_buffer_empty in the 
			function definition and with the help of cmocka unit test framework
*	parameters:
			The function call is_buffer_empty has the function parameter count and ptr which is a 
			structure pointer
		
*	returns:
			compares the status of the enum for the test condition and returns pass or fail when we 
			give command make test TEST="cirbuff"
*********************************************************************************************************/
void test_Buffer_empty(void **state)
{
  	circ_buff * ptr;
	ptr = (circ_buff *)malloc(sizeof(circ_buff));
  	enum rt status= is_buffer_empty(ptr, 0);
  	assert_int_equal(status, EMPTY);
}
/*********************************************************************************************************
*wrap_add
*	description: 
			This function checks whether the buffer gives wrap around success by calling add_item in the
			function definition and with the help of cmocka unit test framework. Here the function inti
			-alize is called before calling the add_item
*	parameters:
			The function call add_item has the function parameter data to be added in the circular
			buffer and ptr which is a structure pointer
		
*	returns:
			compares the status of the enum for the test condition and returns pass or fail when we 
			give command make test TEST="cirbuff"
*********************************************************************************************************/
void test_wrap_add (void **state)
{ 
  	circ_buff * ptr;
	ptr = (circ_buff *)malloc(sizeof(circ_buff));
	initialize_buffer(ptr, 10);				
  	enum rt status= add_item(ptr,5);
  	assert_int_equal(status, WRAP_AROUND_SUCCESS);
}
/*********************************************************************************************************
*wrap_remove
*	description: 	
			This function checks whetherthe buffer gives wrap arount success by calling remove_item
			in the function definition, and with the help of cmocka unit test framework. Here the function 
			initialize_buffer is called before calling remove_item
*	parameters:
			The function call remove_item has the function count and ptr which is a 
			structure pointer
		
*	returns:
			compares the status of the enum for the test condition and returns pass or fail when we 
			give command make test TEST="cirbuff"
*********************************************************************************************************/
void test_wrap_remove (void **state)
{ 

  	circ_buff * ptr;
  	ptr = (circ_buff *)malloc(sizeof(circ_buff));
  	initialize_buffer(ptr, 10);
  	enum rt status= remove_item(ptr,0);
  	assert_int_equal(status, WRAP_AROUND_SUCCESS);

}
/*********************************************************************************************************
*overfill
*	description: 
			This function checks whether the circular buffer we are looking at is getting overfilled. 
		     	The initialize_buffer is first called and then is_buffer_full is called for checking the 
		     	test condition.
*	parameters:
			The function call is_buffer_full has the function parameter size, count and ptr which is a 
			structure pointer
		
*	returns:
			compares the status of the enum for the test condition and returns pass or fail when we 
			give command make test TEST="cirbuff"
*********************************************************************************************************/
void test_overfill (void **state)
{ 
	circ_buff * ptr;
	ptr = (circ_buff *)malloc(sizeof(circ_buff));
	initialize_buffer(ptr, 10);
	ptr->head = ptr->buff+ptr->size;			//head is pointed to last position in the circular buffer
	//at this condition buffer will be full and any element added should go to overfill condition
	enum rt status = is_buffer_full(ptr,10,10);
  	assert_int_equal(status, FULL);
}
/*********************************************************************************************************
*overempty
*	description: 
			This function checks whether the circular buffer we are looking at is being overemptied. 
		     	The initialize_buffer is first called and then is_buffer_empty is called for checking the 
		     	test condition.
	parameters:
		   	The function call is_buffer_empty has the function parameter count and ptr which is the 
		   	structure pointer
*	returns:
			compares the status of the enum for the test condition and returns pass or fail when we 
			give command make test TEST="cirbuff"
*********************************************************************************************************/
void test_overempty(void **state)
{  
        circ_buff * ptr;
	ptr = (circ_buff *)malloc(sizeof(circ_buff));
	initialize_buffer(ptr, 0);
	//the head has to be at the buff position for the buffer empty condition
	ptr->head = ptr->buff;                                                   
	//at this point buffer will be empty and any item to be removed at this condition will give
	//overempty condition
	enum rt status = is_buffer_empty(ptr,0);
  	assert_int_equal(status, EMPTY);
}
/*********************************************************************************************************
*overempty
*	description: 
			This function checks whether when we add an item in the buffer and then remove item from the buffer
		     	when the buffer is full returns the same value
	parameters:
		   	ptr - which is the structure pointer
		   	size - size of the circular buffer for the function call
*	returns:
			compares the status of the enum for the test condition and returns pass or fail when we 
			give command make test TEST="cirbuff"
*********************************************************************************************************/
void test_Add_remove(void **state)
{
	circ_buff * ptr;
	ptr = (circ_buff *)malloc(sizeof(circ_buff));
   	initialize_buffer(ptr,10);
	//5 is being added to the buffer 
	add_item(ptr,5);
	//an item is removed from the circular buffer and checking whether the item added and 
	//removed is same.
	if (*(ptr->tail) == 5)	{			
		enum rt status = initialize_buffer(ptr, 10);
  		assert_int_equal(status, SUCCESS);
	}
	
}
//
int main(int argc, char **argv)
{
	time_t rawtime;
  	struct tm * timeinfo;

  	time ( &rawtime );
  	timeinfo = localtime ( &rawtime );
  	printf ( "Execution time and date: %s", asctime (timeinfo) );  //invoked time.h to report current execution time and date
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
    	cmocka_unit_test(test_reverse_CheckCharacters),
    	cmocka_unit_test(test_Allocate_Free),
    	cmocka_unit_test(test_Invalid_Pointer),
    	cmocka_unit_test(test_Non_Initialised_Buffer),
    	cmocka_unit_test(test_Buffer_Full),
    	cmocka_unit_test(test_Buffer_empty),
    	cmocka_unit_test(test_wrap_add),
    	cmocka_unit_test(test_wrap_remove),
    	cmocka_unit_test(test_overfill),
    	cmocka_unit_test(test_overempty),
    	cmocka_unit_test(test_Add_remove),
    	cmocka_unit_test(test_big_to_little_Invalid_Pointer),
    	cmocka_unit_test(test_big_to_little_Valid_condition),
    	cmocka_unit_test(test_little_to_big_Invalid_Pointer),
    	cmocka_unit_test(test_little_to_big_Valid_condition)
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}


