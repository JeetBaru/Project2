#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<memory.h>

#include "circbuf.h"


typedef struct CircBuf{
    uint8_t *buffer;
    uint8_t *head;
    uint8_t *tail;
    uint8_t length;
    uint8_t count;
    uint8_t index;

}C;

CircBuf *CircBuf1;
int8_t *C_buffer;

/*int8_t (CircBuf1* buf)
{
    buf-> buffer = buf-> head = buf-> tail;

}*/
//Buffer add
uint8_t CircBuf_size()
{
    CircBuf1= malloc(sizeof(CircBuf));
   // C_buffer= 
    return SUCCESS;

}
int8_t CircBuf_Initialise(CircBuf*CircBuf1,uint8_t length)
{
    CircBuf1->buffer =(uint8_t*)malloc(length*sizeof(uint8_t));
	//return SUCCESS;
    CircBuf1->head = CircBuf1-> buffer;
    CircBuf1 ->tail = CircBuf1 -> buffer;
    CircBuf1-> length = length;
    CircBuf1-> count= 0;
    return SUCCESS;
   //else 
	//return FAIL;
}
int8_t CircBuf_add(CircBuf*CircBuf1, uint8_t element, uint8_t cnt, uint8_t length)
{
    if (!CircBuf1)
	return NULL_POINTER;
    CircBuf1-> count = cnt;
    
    *(CircBuf1->head)= element;
    CircBuf1->head= CircBuf1->head+1;
    
    if(CircBuf1->head > CircBuf1->buffer+CircBuf1->length)
        CircBuf1->head = CircBuf1->buffer;
    CircBuf1->count++;
    return WRAP_AROUND_SUCCESS;	
}


int8_t CircBuf_overfill(CircBuf*CircBuf1, uint8_t element, uint8_t cnt, uint8_t length)
{
    //printf("Added Element[%d] = %d  ",buf->end, element );
    if(CircBuf1==0)
        return NULL_POINTER;
    CircBuf1->length = length;
    if (CircBuf1->length < cnt)
	return SUCCESS;
    else 
	return FAIL;
}

//buffer remove


uint8_t CircBuf_remove(CircBuf*CircBuf1, uint8_t cnt)
{
    if (!CircBuf1)
	return NULL_POINTER;
    CircBuf1-> count = cnt;
    
    CircBuf1->tail= CircBuf1->tail+1;
    //for (CircBuf1->buffer; CircBuf1->buffer+CircBuf1+length-1 ; CircBuf1->buffer+1)
    if(CircBuf1->tail > CircBuf1->buffer+CircBuf1->length)
        CircBuf1->tail = CircBuf1->buffer;
    CircBuf1->count--;
    return WRAP_AROUND_SUCCESS;
}
uint8_t CircBuf_remove1(CircBuf*CircBuf1, uint8_t cnt)
{
    if (!CircBuf1)
	return NULL_POINTER;
    CircBuf1-> count = cnt;
    uint8_t rem = *(CircBuf1->tail);
    CircBuf1->tail= CircBuf1->tail+1;
    //for (CircBuf1->buffer; CircBuf1->buffer+CircBuf1+length-1 ; CircBuf1->buffer+1)
    if(CircBuf1->tail > CircBuf1->buffer+CircBuf1->length)
        CircBuf1->tail = CircBuf1->buffer;
    CircBuf1->count--;
    return rem;
}

int8_t CircBuf_add1(CircBuf*CircBuf1, uint8_t element, uint8_t cnt, uint8_t length)
{
    if (!CircBuf1)
	return NULL_POINTER;
    CircBuf1-> count = cnt;
    //CircBuf1->length=length;
    *(CircBuf1->head)= element;
    CircBuf1->head= CircBuf1->head+1;
    //*(CircBuf1->head)= element;
    //for (CircBuf1->buffer; CircBuf1->buffer+CircBuf1+length-1 ; CircBuf1->buffer+1)
    if(CircBuf1->head > CircBuf1->buffer+CircBuf1->length)
        CircBuf1->head = CircBuf1->buffer;
    CircBuf1->count++;
    return element;	
}
//check Empty
int8_t CircBuf_Add_remove()
{	
	
	CircBuf * ptr;
	ptr = (CircBuf *)malloc(sizeof(CircBuf));
	//CircBuf1->head = CircBuf1->tail
	CircBuf_Initialise(ptr,8);
	uint8_t add = CircBuf_add1(ptr, 12, 0, 8);
	//CircBuf_Initialise(ptr,8);
	ptr->tail = ptr->head-1;
	uint8_t Rem=CircBuf_remove1(ptr, 0);
	if (add==Rem)
		return Add_Rem;
	else 
		return FAIL;
	
}

uint8_t CircBuf_empty(CircBuf*CircBuf1, uint8_t cnt)
{  
   
   CircBuf1->count = cnt;
   if (CircBuf1->count <= 0)
   	return EMPTY;
   else 
	return FAIL;
}

//check Full

uint8_t CircBuf_full(CircBuf*CircBuf1,uint8_t cnt,uint8_t len)
{   
    CircBuf1->count  = cnt;
    CircBuf1->length = len;
    if (CircBuf1->length <= CircBuf1->count)
        return FULL;
    else 
	return FAIL;
}

//check for the nth element

uint8_t CircBuf_peak(CircBuf*CircBuf1, uint8_t index)
{
    uint8_t data;
//    uint8_t index;
     data =  *(CircBuf1->buffer+CircBuf1->index);
     return data;
        return SUCCESS;
}


uint8_t CircBuf_overempty(CircBuf*CircBuf1, uint8_t cnt, uint8_t length)
{
    CircBuf1->length = length;
    if (CircBuf1->length < cnt )
    {
        //CircBuf_remove(CircBuf1, cnt);
        return SUCCESS;
    }
    else
        return FAIL;

}


int8_t CircBuf_destroy(CircBuf *CircBuf1)
{
    free(CircBuf1->buffer);
    free(CircBuf1);
    return EMPTY;
}

