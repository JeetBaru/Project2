
//logger.c
#ifndef VERBOSE
	# include "uart.h"
#endif
# include "cirbuff.h"
# include "logger.h"
# include "analysedata.h"

void log_data(uint8_t * ptr,uint32_t length)
{
	while(length > 0 )
	{
		if(circ_ptr->size > length)
		{
		    while(length>0)
		    {
		    	add_item(circ_ptr, *ptr);
				ptr++;
				length--;
			}
		}
		else
		{
			while(is_buffer_full(circ_ptr)!=FULL)
			{
				add_item(circ_ptr, *ptr);
				ptr++;
			}
			length = length - circ_ptr->size;

		}
		#ifdef VERBOSE
			while(is_buffer_empty(circ_ptr)!=EMPTY)
			{
				printf("%c",remove_item(circ_ptr));
			}
		#else
			UART0_C2 |= 0x80;
			__enable_irq();
		#endif
	}
}

void log_string(int8_t * ptr)
{
	int32_t length=0;
	while(*ptr != '\0')
	{
		length++;
		ptr++;
	}
	ptr=ptr-length;
	log_data(ptr,length);
}

void create_log_item(log * logptr, status log_id, int32_t length, int8_t * ptr)
{
	logptr->logid = log_id;
	logptr->length = length;
	logptr->payload = ptr;
}

void log_item(log * logptr)
{
	LOG_RAW_STRING("LOG ID ");
	LOG_RAW_INTEGER(logptr->logid);
	if(logptr->payload != 0)
	{
		LOG_RAW_STRING(" / PAYLOAD ");
		LOG_RAW_STRING(logptr->payload);
	}
	LOG_RAW_STRING("-----");
}

void destroy_log_item(log * log1)
{
	free(log1);
}

void log_integer(int32_t data)
{
	int8_t dest [20];
	int8_t * ptr = dest;
	ptr = my_itoa(ptr, data, 16);
	log_string(ptr);
}

void log_flush(circ_buff * circ_pre)
{
	while(is_buffer_empty(circ_pre)!=EMPTY){
		uint8_t D = remove_item(circ_pre);
		#ifndef VERBOSE
			add_item(circ_ptr, D);
			UART0_C2 |= 0x80;
			__enable_irq();
		#else
			printf("%c",D);
		#endif
	}
}
