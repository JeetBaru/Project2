#ifndef __MEMORY_H__
#define __MEMORY_H__

#include<stdint.h>

int8_t my_memmov(uint8_t * scr, uint8_t * dest,uint32_t length);
int8_t my_memset(uint8_t * scr, uint32_t length,uint8_t value);
int8_t my_memzero(uint8_t *scr, uint32_t length);
int8_t my_rev(uint8_t * ptr,uint32_t length);

#endif
