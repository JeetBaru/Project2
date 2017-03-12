#ifndef __DATA_H__
#define __DATA_H__
#include <stdint.h>
#include <stdio.h>
#define CircBuf_siz 8
typedef enum retData{
                WRAP_AROUND_SUCCESS,
                FULL,
		No_Length,
                EMPTY,
                FAIL,
                NULL_POINTER,
                Buffer_allocation_failure,
                SUCCESS,
                AddRem,
		Add_Rem
}Redt_t;
typedef struct {
    uint8_t *  buffer;
    uint8_t *head;
    uint8_t *tail;
    uint8_t length;
    uint8_t count;
    uint8_t index;

}CircBuf;
//CircBuf *CircBuf1;
//int8_t *C_buffer;



//enum retData status = malloc(sizeof(retData));
uint8_t CircBuf_size();
int8_t CircBuf_Initialise(CircBuf*CircBuf1,uint8_t length);
int8_t CircBuf_add(CircBuf*CircBuf1, uint8_t element, uint8_t cnt, uint8_t length );
uint8_t CircBuf_remove(CircBuf*CircBuf1, uint8_t cnt);
int8_t CircBuf_add1(CircBuf*CircBuf1, uint8_t element, uint8_t cnt, uint8_t length);
uint8_t CircBuf_remove1(CircBuf*CircBuf1, uint8_t cnt);
uint8_t CircBuf_empty(CircBuf*CircBuf1, uint8_t cnt);
uint8_t CircBuf_full(CircBuf*CircBuf1,uint8_t cnt, uint8_t len);
uint8_t CircBuf_peak(CircBuf*CircBuf1, uint8_t index);
int8_t CircBuf_overfill(CircBuf*CircBuf1, uint8_t element, uint8_t cnt, uint8_t length);
uint8_t CircBuf_overempty(CircBuf*CircBuf1, uint8_t cnt, uint8_t length);
int8_t CircBuf_destroy(CircBuf *CircBuf1);
int8_t CircBuf_Add_remove();

#endif
