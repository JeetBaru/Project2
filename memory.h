#ifndef __MEMORY_H__
#define __MEMORY_H__

typedef enum retData {
	NULL_PTR,
	SUCCESS
	}Redt_t;

#include<stdint.h>
#define MAX1 {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31}

int8_t my_memmov(uint8_t * scr, uint8_t * dest,uint32_t length);
int8_t my_memset(uint8_t * scr, uint32_t length,uint8_t value);
int8_t my_memzero(uint8_t *scr, uint32_t length);
int8_t my_rev(uint8_t * ptr,uint32_t length);

#endif
