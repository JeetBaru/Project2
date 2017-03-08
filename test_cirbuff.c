#include <math.h>
#include <stdlib.h>

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "cirbuff.h"


void test_Allocate_Free(void **state)
{ circ_buff * ptr;
	ptr = (circ_buff *)malloc(sizeof(circ_buff));
  enum rt status = CircBuf_size(ptr);
  assert_int_equal(status, SUCCESS);
}

void test_Invalid_Pointer(void **state)
{
  circ_buff * ptr;
	ptr = (circ_buff *)malloc(sizeof(circ_buff));
	ptr = 0;
  enum rt status = is_buffer_empty(ptr, 5);
  assert_int_equal(status, INVALID_POINTER);
}




void test_Non_Initialised_Buffer(void **state)
{
  circ_buff * ptr;
	ptr = (circ_buff *)malloc(sizeof(circ_buff));
  enum rt status= initialize_buffer(ptr,10);
  assert_int_equal(status, SUCCESS);
}
void test_Buffer_Full(void **state)
{
  circ_buff * ptr;
	ptr = (circ_buff *)malloc(sizeof(circ_buff));
  enum rt status= is_buffer_full(ptr, 10, 10);
  assert_int_equal(status, FULL);
}

void test_Buffer_empty(void **state)
{
  circ_buff * ptr;
	ptr = (circ_buff *)malloc(sizeof(circ_buff));
  enum rt status= is_buffer_empty(ptr, 0);
  assert_int_equal(status, EMPTY);
}

void test_wrap_add (void **state)
{ 
  circ_buff * ptr;
	ptr = (circ_buff *)malloc(sizeof(circ_buff));
	initialize_buffer(ptr, 10);
  enum rt status= add_item(ptr,5);
  assert_int_equal(status, WRAP_AROUND_SUCCESS);
}

void test_wrap_remove (void **state)
{ 

  circ_buff * ptr;
	ptr = (circ_buff *)malloc(sizeof(circ_buff));
 	initialize_buffer(ptr, 10);
  enum rt status= remove_item(ptr,0);
  assert_int_equal(status, WRAP_AROUND_SUCCESS);

}

void test_overfill (void **state)
{ 
	circ_buff * ptr;
	ptr = (circ_buff *)malloc(sizeof(circ_buff));
	initialize_buffer(ptr, 10);
	ptr->head = ptr->buff+ptr->size;
	//at this condition buffer will be full and any element added should go to overfill condition
	enum rt status = is_buffer_full(ptr,10,10);
  	assert_int_equal(status, FULL);

}


void test_overempty(void **state)
{  
        circ_buff * ptr;
	ptr = (circ_buff *)malloc(sizeof(circ_buff));
	initialize_buffer(ptr, 0);
	ptr->head = ptr->buff;
	//at this point buffer will be empty and any item to be removed at this condition will give
	//overempty condition
	enum rt status = is_buffer_empty(ptr,0);
  	assert_int_equal(status, EMPTY);
}

void test_Add_remove(void **state)
{
	circ_buff * ptr;
	ptr = (circ_buff *)malloc(sizeof(circ_buff));
   	initialize_buffer(ptr,10);
	add_item(ptr,5);
	if (*(ptr->tail) == 5)	{
		enum rt status = initialize_buffer(ptr, 10);
  		assert_int_equal(status, SUCCESS);
	}
	
}

int main()
{
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


