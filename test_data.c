//#include<math.h>
#include <stdlib.h>
#include "data.h"
#include <stdio.h>
#include <stdarg.h>

#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>



//big to little
void test_big_to_little_Invalid_Pointer(void **state);


void test_big_to_little_Valid_condition(void **state);

//little to big

void test_little_to_big_Invalid_Pointer(void **state);


void test_little_to_big_Valid_condition(void **state);


int main()
{
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(test_big_to_little_Invalid_Pointer),
    cmocka_unit_test(test_big_to_little_Valid_condition),
    cmocka_unit_test(test_little_to_big_Invalid_Pointer),
    cmocka_unit_test(test_little_to_big_Valid_condition)
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}

//big to little
void test_big_to_little_Invalid_Pointer(void **state)
{ // null pointer
	
  uint32_t *ptr;
  //ptr = &data;
  ptr=0; 
  uint32_t length=10 ;
  enum retData status = big_to_little32(ptr, length);
  assert_int_equal(status, NULL_PTR);
}

void test_big_to_little_Valid_condition(void **state)
{
  uint32_t data[] = MAX;
  uint32_t length = 32;
  uint32_t *ptr;
  ptr = data;
  enum retData status = big_to_little32(ptr, length);
  assert_int_equal(status, SUCCESS);
}

//little to big

void test_little_to_big_Invalid_Pointer(void **state)
{
  uint32_t *ptr;
  //ptr=&data;
  ptr=0;
  uint32_t length =10;
  enum retData status = little_to_big32(ptr, length);
  assert_int_equal(status, NULL_PTR);
}

void test_little_to_big_Valid_condition(void **state)
{
  uint32_t data[] = MAX;
  uint32_t *ptr;
  ptr=data;
  uint32_t length = 32;
  enum retData status= little_to_big32(ptr, length);
  assert_int_equal(status, SUCCESS);
}
