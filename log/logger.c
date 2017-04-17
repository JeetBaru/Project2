
//logger.c

# include "logger.h"
//logs data provided starting address and length
void log_data(uint8_t * ptr,uint32_t length)
{
	while(length > 0 )
	{
		if(circ_ptr->size > length)							//for length less than size of buffer
		{
		    while(length>0)
		    {
		    	add_item(circ_ptr, *ptr);					//item added to transmit buffer
				ptr++;
				length--;
			}
		}
		else
		{
			while(is_buffer_full(circ_ptr)!=FULL)			//for length greater than size of buffer
			{
				add_item(circ_ptr, *ptr);					//only 'size' number of elements added to transmit buffer
				ptr++;
			}
			length = length - circ_ptr->size;

		}
		#ifdef VERBOSE
			while(is_buffer_empty(circ_ptr)!=EMPTY)			//for BBB and Host machine use printf
			{
				printf("%c",remove_item(circ_ptr));
			}
		#else												//for FRDM enable interrupts
			UART0_C2 |= 0x80;
			__enable_irq();
		#endif
	}
}

//logs strings when length not available
void log_string(int8_t * ptr)
{
	int32_t length=0;
	while(*ptr != '\0')										//calculate length by searching for null character
	{
		length++;
		ptr++;
	}
	ptr=ptr-length;
	log_data(ptr,length);									//pass execution to log_data
}

//logs integer values
void log_integer(int32_t data)
{
	int8_t dest [20];
	int8_t * ptr = dest;
	ptr = my_itoa(ptr, data, 16);							//integer converted to ascii value
	log_string(ptr);										//returned string is passed to log_string
}

//initialize log structures with values
void create_log_item(log * logptr, status log_id, int32_t length, int8_t * ptr)
{
	logptr->logid = log_id;
	logptr->timestamp = TIMESTAMP();
	logptr->length = length;
	logptr->payload = ptr;									//initialize payload with start pointer
}

//log items depending on log structure initialization
void log_item(log * logptr)
{
	LOG_RAW_STRING("LOG ID ");								//prints log id
	LOG_RAW_INTEGER(logptr->logid);							//prints log id value
	LOG_RAW_STRING(" / TIMESTAMP ");
	LOG_RAW_INTEGER(logptr->timestamp);
	if(logptr->payload != 0)								//if payload is not zero
	{
		LOG_RAW_STRING(" / PAYLOAD ");
		LOG_RAW_STRING(logptr->payload);					//print payload
	}
	LOG_RAW_STRING("----");
}

//free allocated memory
void destroy_log_item(log * log1)
{
	free(log1);
}

//flush out data from passed pointer
void log_flush(circ_buff * circ_pre)
{
	while(is_buffer_empty(circ_pre)!=EMPTY){
		uint8_t D = remove_item(circ_pre);					//till buffer is not empty
		#ifndef VERBOSE
			add_item(circ_ptr, D);							//use interrupts for FRDM
			UART0_C2 |= 0x80;
			__enable_irq();
		#else
			printf("%c",D);									//print character for BBB and host
		#endif
	}
}



