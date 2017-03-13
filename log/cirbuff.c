# include "cirbuff.h"

//allocates size to the buffer
int8_t CircBuf_size(circ_buff*cb1)
{
    cb1= malloc(sizeof(circ_buff));
    return SUCCESS;

}

int8_t is_buffer_full(circ_buff * cb1)
{
	if (!cb1)
		return INVALID_POINTER;
	if(cb1->count == cb1->size)
		return FULL;
	else
		return NO;
}

int8_t is_buffer_empty(circ_buff * cb1)
{
	if (!cb1)
		return INVALID_POINTER;
	if(cb1->count == 0)
		return EMPTY;
	else
		return NO;
}

int8_t initialize_buffer(circ_buff * cb1, uint32_t size)
{
	if (!cb1)
		return INVALID_POINTER;
	cb1->buff = (int8_t *)calloc(size,(sizeof(int8_t)));
	cb1->head = cb1->buff;
	cb1->tail = cb1->buff;
	cb1->size = size;
	cb1->count = 0;
	return SUCCESS;
}

int8_t destroy_buffer(circ_buff * cb1)
{
	if (!cb1)
		return INVALID_POINTER;
	free(cb1->buff);
	cb1->buff == '\0';
	return SUCCESS;
}

int8_t add_item(circ_buff * cb1, uint8_t data)
{
	if (!cb1)
		return INVALID_POINTER;
	if(cb1){
		if(cb1->head==cb1->buff+cb1->size-1){
			*(cb1->head)=data;
			cb1->head=cb1->buff;
			cb1->count++;
			return WRAP_AROUND_SUCCESS;
		}
		else{
			*(cb1->head)=data;
			cb1->head++;
			cb1->count++;
			return SUCCESS;
		}
	}
}

int8_t remove_item(circ_buff * cb1)
{
	if (!cb1)
		return INVALID_POINTER;
	if(cb1){
		if(cb1->tail==cb1->buff+cb1->size-1){
			cb1->tail=cb1->buff;
			cb1->count--;
			return *(cb1->buff+cb1->size-1);
		}
		else{
			cb1->tail++;
			cb1->count--;
			return *(cb1->tail-1);
		}
	}
}

int8_t cirbuf_peak(circ_buff*cb1, uint8_t index)
{
    uint8_t data;
    data =  *(cb1->buff+index);						//checks the data by dereferencing the pointer at the index
    return data;
}
