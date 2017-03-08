#include<math.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "memory.h"


//memmove
void test_memmove_Invalid_Pointer(void **state)
{ // null pointer
  uint8_t set_2[]= MAX1;
  uint8_t *ptr;
  ptr = set_2;
  ptr=0; 
  uint8_t *pt = set_2; 
  enum retData status = my_memmov(ptr, pt+6, 6);
  assert_int_equal(status, NULL_PTR);
}

void test_memmove_NoOverlap(void **state)
{
  uint8_t set_2[]= MAX1;
  //uint8_t length = 32;
  uint8_t *ptr = set_2;
  enum retData status = my_memmov(ptr + 25, ptr + 19, 6);
  assert_int_equal(status, SUCCESS);
}

void test_memove_SRC_in_DST(void **state)
{
  uint8_t set_2[]= {1,2,3,4,5,6,7,8,9};
  //uint8_t length = 32;
  uint8_t *ptr = set_2;
  enum retData status = my_memmov(ptr , ptr + 2, 5);
  assert_int_equal(status, SUCCESS);
}
void test_memove_DST_in_SRC(void **state)
{
  uint8_t set_2[]= {1,2,3,4,5,6,7,8,9};
  //uint8_t length = 32;
  uint8_t *ptr = set_2;
  enum retData status = my_memmov(ptr + 2, ptr , 5);
  assert_int_equal(status, SUCCESS);
}
//memset

void test_memset_Invalid_Pointers(void **state)
{
  uint8_t set_2[]= MAX1;
  //uint8_t length = 32;
  uint8_t *ptr = set_2;
  ptr = 0;
  uint8_t length = 4;
  enum retData status = my_memset(ptr, length, 0xEE);
  assert_int_equal(status, NULL_PTR);
}

void test_memset_Check_set(void **state)
{
  uint8_t set_2[]= MAX1;
  uint8_t length = 4;
  uint8_t *ptr = set_2;
  enum retData status = my_memset(ptr+15, length, 0xEE);
  assert_int_equal(status, SUCCESS);
}

//memzero
void test_memzero_Invalid_Pointer(void **state)
{
  uint8_t set_2[]= MAX;
  uint8_t length = 32;
  uint8_t *ptr = set_2;
  ptr=0;
  enum retData status= my_memzero(ptr, length);
  assert_int_equal(status, NULL_PTR);
}

void test_memzero_Check_set(void **state)
{
  uint8_t set_2[]= MAX; 
  uint8_t length = 32;
  uint8_t *ptr = set_2;
  enum retData status= my_memzero(ptr, length);
  assert_int_equal(status, SUCCESS);
}
//Reverse
void test_reverse_Invalid_Pointer(void **state)
{
  uint8_t *ptr;
  ptr=0;
  uint8_t length = 10;
  enum retData status= my_rev(ptr, length);
  assert_int_equal(status, NULL_PTR);
}
void test_CheckOddReverse(void **state)
{
  uint8_t set_2[]= MAX1;
  uint8_t length = 11;
  uint8_t *ptr = set_2;
  enum retData status= my_rev(ptr, length);
  assert_int_equal(status, SUCCESS);
  
}
void test_CheckEvenReverse(void **state)
{
  uint8_t set_2[]= MAX1;
  uint32_t length = 12;
  uint8_t * ptr = set_2;
  enum retData status= my_rev(ptr, length);
  assert_int_equal(status, SUCCESS);
}

void test_reverse_CheckCharacters(void **state)
{
  uint8_t set_2[]= "abcd";
  uint8_t length = 4;
  uint8_t *ptr = set_2;
  enum retData status= my_rev(ptr, length);
  assert_int_equal(status, SUCCESS);
}

int main(int argc, char **argv)
{
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
