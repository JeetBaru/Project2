/**************************************************************************************
*   File: test_data.c
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
*       	test_big_to_little_Invalid_Pointer
    		test_big_to_little_Valid_condition
    		test_little_to_big_Invalid_Pointer
    		test_little_to_big_Valid_condition
*
****************************************************************************************/
#include <stdlib.h>
#include "data.h"
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
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
//int main has the cmocka unit tests framwork which checks the whether the condition is failed or passed.
int main()
{
	time_t rawtime;
  	struct tm * timeinfo;

  	time ( &rawtime );
  	timeinfo = localtime ( &rawtime );
  	printf ( "Execution time and date: %s", asctime (timeinfo) ); //invoked time.h to report current execution time and date
  const struct CMUnitTest tests[] = {
    	cmocka_unit_test(test_big_to_little_Invalid_Pointer),
    	cmocka_unit_test(test_big_to_little_Valid_condition),
    	cmocka_unit_test(test_little_to_big_Invalid_Pointer),
    	cmocka_unit_test(test_little_to_big_Valid_condition)
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
