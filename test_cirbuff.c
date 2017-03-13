/**************************************************************************************
*   File: test_cirbuff.c
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
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "cirbuff.h"
#include "uni.h"

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
	ptr = (circ_buff *)malloc(sizeof(circ_buff));     	//size allocated to the structure pointer
  	enum rt status = CircBuf_size(ptr);			//checks whether the buffer is initialised
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
	ptr = 0;					  	//null pointer is passed for Invalid pointer condition
  	enum rt status = is_buffer_empty(ptr);			//checks whether the buffer is empty	
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
  	enum rt status= initialize_buffer(ptr,10);		//initialised_buffer is called to check if it is initialised or not
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
	initialize_buffer(ptr,4);				//initialzed the buffer with size 4
	for (uint8_t i=0; i<4; i++)
	{
		add_item(ptr,i);				//4 items added so that the buffer will be full
	}
  	enum rt status= is_buffer_full(ptr);			//checks whether the buffer is full
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
	initialize_buffer(ptr,10);				//buffer initialized so count=0 and hence the buffer will be empty
  	enum rt status= is_buffer_empty(ptr);			//checks whether the buffer is empty
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
	initialize_buffer(ptr, 4);		
	for (uint8_t i=0; i<3; i++){				//3 items are added in the circular buffer of size 4
		add_item(ptr, i);
	}
		
  	enum rt status= add_item(ptr,5);			//4th item is added hence the unit test will give WRAP_AROUND_SUCCESS
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
  	initialize_buffer(ptr, 4);
	for (uint8_t i=0 ; i<3 ; i++){				//3 items are added and then the added items are removed 
		add_item(ptr, i);
		remove_item(ptr);
	}
	add_item(ptr, 4);					//4th item is added to the 4 size buffer
  	enum rt status= remove_item(ptr);			//removing 4th item will give WRAP_AROUND_SUCCESS
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
	initialize_buffer(ptr, 4);				//created a circular buffer of size 4
	for (uint8_t i=0; i<4; i++)
		add_item(ptr,i);				//4 items added and when tried adding more overfill
	//head is pointed to last position in the circular buffer
	//at this condition buffer will be full and any element added should go to overfill condition
	enum rt status = is_buffer_full(ptr);
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
	initialize_buffer(ptr, 4);					//intialized buffer with 4 length  
	//the head has to be at the buff position for the buffer empty condition
	ptr->head = ptr->buff;                                                   
	//at this point buffer will be empty and any item to be removed at this condition will give
	//overempty condition
	enum rt status = is_buffer_empty(ptr);				//removing more will be overempty
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
//int main has the cmocka unit tests framwork which checks the whether the condition is failed or passed.
int main()
{	
	time_t rawtime;
  	struct tm * timeinfo;
  	time ( &rawtime );
  	timeinfo = localtime ( &rawtime );
	printf("Test Environment : cmocka\n");
  	printf ( "Execution time and date: %s", asctime (timeinfo) ); //invoked time.h to report current execution time and date

  const struct CMUnitTest tests[] = {
    	cmocka_unit_test(test_Allocate_Free),
   	cmocka_unit_test(test_Invalid_Pointer),
    	cmocka_unit_test(test_Non_Initialised_Buffer),
    	cmocka_unit_test(test_Buffer_Full),
    	cmocka_unit_test(test_Buffer_empty),
    	cmocka_unit_test(test_wrap_add),
    	cmocka_unit_test(test_wrap_remove),
    	cmocka_unit_test(test_overfill),
    	cmocka_unit_test(test_overempty),
    	cmocka_unit_test(test_Add_remove)
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}


