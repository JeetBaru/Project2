/*
 * Circular_Buffer.c
 *
 *  Created on: 30-Oct-2016
 *      Author: Sayan
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "Cbuf.h"
int8_t* C_buffer;
//check if buffer is full
buffer_status buff_full(circular_buff_t *circ_buff)
{
    if (circ_buff->num_items == circ_buff->length)
    {
        return buffer_full;
    }
    else
    {
        return buffer_not_full;
    }

}
int8_t CircBuf_Initialise(circular_buff_t *circ_buff)
{   
    circ_buff->buff =(int8_t*)malloc(sizeof(C_buffer));
	//return SUCCESS;
    circ_buff->head = circ_buff-> buff;
    circ_buff ->tail = circ_buff -> buff;
    //circ_buff-> length = CircBuf_siz;
    //CircBuf1-> count= 0;
    return SUCCESS;
   //else 
	//return FAIL;
}
//allocate memory to buffer
int8_t* allocate_memory(circular_buff_t *circ_buff)
{
	circ_buff->buff= malloc(sizeof(circular_buff_t));
    return SUCCESS;
}

//free the memory allocated to buffer
void free_buff(circular_buff_t *circ_buff)
{
	free(circ_buff);
}

//check if buffer is empty
buffer_status buff_empty(circular_buff_t *circ_buff)
{
    if(circ_buff->num_items==0)
    {
        return buffer_empty;
    }
    else
    {
        return buffer_not_empty;
    }
}

//add item to buffer
 buffer_status put_item_tobuffer(circular_buff_t *circ_buff, int8_t data)
{

    if(!circ_buff)
	return NULL_POINTER;

    buffer_status _bufferstatus;
    _bufferstatus=buff_full(circ_buff);
    if(_bufferstatus==buffer_not_full)
    {
        if(circ_buff->head==(circ_buff->buff)+(circ_buff->length)-1)
        {
          circ_buff->head=circ_buff->buff;
          circ_buff->head++;
        *(circ_buff->head)=data;
        if(!(circ_buff->num_items!=MAX_LEN))
        (circ_buff->num_items)++;
        return success_item_add_wraparound_override;
        }
        else
        {
            circ_buff->head++;
            *(circ_buff->head)=data;
            (circ_buff->num_items)++;
            return success_item_add;
        }
    }
    else if(_bufferstatus==buffer_full)
    {
      return buffer_full;
    }

}

//read data from the buffer and remove the content saved in the buffer
 int8_t read_delete_item_frombuffer(circular_buff_t *circ_buff)
{
    buffer_status _bufferstatus;
	int8_t data;
    _bufferstatus=buff_empty(circ_buff);
    if(_bufferstatus==buffer_not_empty)
    {

        if(circ_buff->tail==((circ_buff->buff)+(circ_buff->length))-1)
        {

        circ_buff->tail=circ_buff->buff;
        (circ_buff->tail)++;
        data=*(circ_buff->tail);
        *(circ_buff->tail)=0;
        (circ_buff->num_items)--;
        return data;
        }
        else
        {
            (circ_buff->tail)++;
            data=*(circ_buff->tail);
            *(circ_buff->tail)=0;
            (circ_buff->num_items)--;
            return SUCCESS;
        }
    }
    else if(_bufferstatus==buffer_empty)
    {
      return -1;
    }
}
uint8_t CircBuf_overfill(uint8_t element, uint8_t cnt)
{
    if (element <= 2)
    {
        //CircBuf_add(CircBuf1, element, cnt);
        return SUCCESS;
    }
    else
        return FAIL;
}

uint8_t CircBuf_overempty(uint8_t element, uint8_t cnt)
{

    if (element <= 2)
    {
        //CircBuf_remove(CircBuf1, cnt);
        return SUCCESS;
    }
    else
        return FAIL;

}
