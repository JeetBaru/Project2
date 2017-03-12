#include <math.h>
#include <stdlib.h>

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "Cbuf.h"

//big to little
void test_Allocate_Free(void **state)
{ // null pointer
	
  enum buffer_status status = allocate_memory(circ_buff);
  assert_int_equal(status, SUCCESS);
}

void test_Invalid_Pointer(void **state)
{
  int8_t data = 4;
  CircBuf1 = 0;
  enum buffer_status status =buffer_status put_item_tobuffer(circ_buff, data);
  assert_int_equal(status, NULL_POINTER);
}

//little to big


void test_Non_Initialised_Buffer(void **state)
{
  
  enum buffer_status status= CircBuf_Initialise(circ_buff);
  assert_int_equal(status, SUCCESS);
}
void test_Buffer_Full(void **state)
{
  //uint8_t cnt = 13, len = 12;
  enum buffer_status status=buffer_status buff_full(circ_buff);
  assert_int_equal(status, buffer_full);
}

void test_Buffer_empty(void **state)
{
  //uint8_t element = 6;
  //uint8_t cnt = 0;
  enum buffer_status status=buffer_status buff_empty(circ_buff)
  assert_int_equal(status,buffer_empty);
}

void test_wrap_add (void **state)
{ 
  int8_t data = 6;
  //uint8_t length = 6;
  enum buffer_status status= buffer_status put_item_tobuffer(circ_buff, data)
  assert_int_equal(status, success_item_add_wraparound_override);
}

void test_wrap_remove (void **state)
{ 
  uint8_t cnt = 2;
  enum buffer_status status= read_delete_item_frombuffer(circ_buff);
  assert_int_equal(status, SUCCESS);
}
/*void test_ADD_Remove (void **state)
{
  
  enum retData status= CircBuf_full(CircBuf1, cnt, len);
  assert_int_equal(status, AddRem);
}*/
void test_overfill (void **state)
{ 
   uint8_t element = 3, cnt = 3;
  //uint8_t length = 4;
  if (element <= 2 )
{  	enum buffer_status status = CircBuf_overfill(element, cnt);
  	assert_int_equal(status, SUCCESS);
}
  else 
{
	enum buffer_status status = CircBuf_overfill(element, cnt);
  	assert_int_equal(status, FAIL);

}

}

void test_overempty(void **state)
{  
   uint8_t element = 3, cnt = 4;
   if (element <= 2 )
{  	enum retData status = CircBuf_overempty(element, cnt);
  	assert_int_equal(status, SUCCESS);
}
  else 
{
	enum retData status = CircBuf_overempty(element, cnt);
  	assert_int_equal(status, FAIL);

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
    //cmocka_unit_test(test_ADD_Remove),
    cmocka_unit_test(test_overfill),
    cmocka_unit_test(test_overempty)
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}


