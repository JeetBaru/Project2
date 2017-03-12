#include <math.h>
#include <stdlib.h>

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "circbuf.h"

//big to little
void test_Allocate_Free(void **state)
{ // null pointer
	
  enum retData status = CircBuf_size();
  assert_int_equal(status, SUCCESS);
}

void test_Invalid_Pointer(void **state)
{
  CircBuf * ptr;
	ptr = (CircBuf *)malloc(sizeof(CircBuf));
	ptr = 0;
  enum retData status = CircBuf_remove(ptr,0);
  assert_int_equal(status, NULL_POINTER);
}

//little to big


void test_Non_Initialised_Buffer(void **state)
{
  CircBuf * ptr;
	ptr = (CircBuf *)malloc(sizeof(CircBuf));
  enum retData status= CircBuf_Initialise(ptr,10);
  assert_int_equal(status, SUCCESS);
}
void test_Buffer_Full(void **state)
{
  CircBuf * ptr;
	ptr = (CircBuf *)malloc(sizeof(CircBuf));
  enum retData status= CircBuf_full(ptr, 12, 10);
  assert_int_equal(status, FULL);
}

void test_Buffer_empty(void **state)
{
  CircBuf * ptr;
	ptr = (CircBuf *)malloc(sizeof(CircBuf));
  enum retData status= CircBuf_empty(ptr, 0);
  assert_int_equal(status, EMPTY);
}

void test_wrap_add (void **state)
{ 
  CircBuf * ptr;
	ptr = (CircBuf *)malloc(sizeof(CircBuf));
	CircBuf_Initialise(ptr,10);
  enum retData status= CircBuf_add(ptr, 10, 0,8);
  assert_int_equal(status, WRAP_AROUND_SUCCESS);
}

void test_wrap_remove (void **state)
{ 

  CircBuf * ptr;
	ptr = (CircBuf *)malloc(sizeof(CircBuf));
  	//CircBuf_Initialise(ptr,10);
  enum retData status= CircBuf_remove(ptr, 4);
  assert_int_equal(status, WRAP_AROUND_SUCCESS);
}
/*void test_ADD_Remove (void **state)
{
  
  enum retData status= CircBuf_full(CircBuf1, cnt, len);
  assert_int_equal(status, AddRem);
}*/
void test_overfill (void **state)
{ 
	CircBuf * ptr;
	ptr = (CircBuf *)malloc(sizeof(CircBuf));
	enum retData status = CircBuf_overfill(ptr,2,2, 1);
  	assert_int_equal(status, SUCCESS);

}

void test_overempty(void **state)
{  
        CircBuf * ptr;
	ptr = (CircBuf *)malloc(sizeof(CircBuf));
	enum retData status = CircBuf_overempty(ptr,2,1);
  	assert_int_equal(status, SUCCESS);
}

void test_Add_remove(void **state)
{
	CircBuf * ptr;
	ptr = (CircBuf *)malloc(sizeof(CircBuf));
   	CircBuf_Initialise(ptr,10);
	enum retData status = CircBuf_Add_remove();
  	assert_int_equal(status, Add_Rem);

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
    //cmocka_unit_test(test_ADD_Remove),
    cmocka_unit_test(test_overfill),
    cmocka_unit_test(test_overempty),
    cmocka_unit_test(test_Add_remove)
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}


