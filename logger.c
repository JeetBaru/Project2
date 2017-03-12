
//logger.c

# include "MKL25Z4.h"
# include "uart.h"
# include "cirbuff.h"
# include "logger.h"

//extern circ_buff * circ_ptr;

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
		//sendnbytes( pt , l);
		}
		else
		{
			while(is_buffer_full(circ_ptr)!=FULL)
			{
				add_item(circ_ptr, *ptr);
				ptr++;
			}
		//sendnbytes( pt , circ_ptr->size);
			length = length - circ_ptr->size;

		}
		#ifdef VERBOSE
			while(is_buffer_empty(circ_ptr)!=0)
			{
				printf("%c",remove_item(circ_ptr));
			}
		#else
			UART0_C2 |= 0x80;
			__enable_irq();
		#endif
		/*
		__disable_irq();
		UART0_C2 |= 0x80;
		__enable_irq();
		*/
	}
	/*
	__disable_irq();
	uartinit();
	*/
	//UART0_C2 &= 0x7F;

	//sendnbytes(ptr, length)
}

void UART0_IRQHandler()
{
	//if(UART0_S1 & 0x80 != 0)
	__disable_irq();
	if(UART0_C2 & 0x80)
	//if(UART0_S1 & 0x80)
	{
		UART0_C2 &= 0x7F;
		UART0_D = remove_item(circ_ptr);
		//int32_t i;
		//for(i=0;i<10000;i++);
		if(is_buffer_empty(circ_ptr) != EMPTY)
		{
			UART0_C2 |= 0x80;
			__enable_irq();
		}
	}
	else if (UART0_C2 & 0x20)
	{
		UART0_C2 &= 0xDF;
		//if(is_buffer_full(circ_pre)!=FULL)
		//{
			//sendbyte(UART0_D);
			//UART0_C2 |= 0x80;
			//add_item(circ_pre, UART0_D);
			add_item(circ_pre,UART0_D);
			//UART0_D = remove_item(circ_pre);
			//UART0_C2 |= 0x20;
			//UART0_C2 |= 0x20;
			//__enable_irq();

		/*if(is_buffer_full(circ_pre) == FULL)
		{
			sendnbytes(circ_pre->tail,circ_pre->size);
		}

		__enable_irq();
		*/
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
	LOG_RAW_STRING("----------");
}

int8_t * my_itoa(int8_t * str, int32_t data, int32_t base)
{
	int8_t count=0;						//Count used to count length of new based number
	int32_t rem,d;             			//rem-remainder; d-copy of data
	d=data;
	if(str == '\0')						//Return 0 for null pointer arguement
	{
		return 0;
	}
	if(base<=1 || base>36)				//Works only for any base from 2 to 36
	{
		return 0;
	}
	else
	{
		if(data==0){
			str = "0";
			return str;
		}
		while(d!=0)						//counts number of digits required
		{
			count++;
			d=d/base;
		}
		if(data>0)						//Stores '+' in 1st position for positive number
		{
			*str='+';
		}
		else
		{
			*str='-';					//Stores '-' in 1st position for negative number
			data=-data;
		}
		str=str+count+1;				//Pointer points to last position
		*str='\0';						//Null termination provided
		str--;
		while(count>0)
		{
			rem=data%base;				//Remainder is calculated for given base
			if(rem<10)					//if remainder is <10; then respective digit is to be added
			{
				*str=0x30+rem;
			}
			else 						//if remainder >=10; then respective letter is to be added
			{
				*str=0x41+rem-10;
			}
			data=data/base;				//we divide by base to obtain next digit
			str--;
			count--;
		}
	}
	return str;
}

void analyse_data(int8_t * c)
{
	LOG_IT(log1,DATA_ANALYSIS_STARTED,1,0);

	int8_t w=0,x=0,y=0,z=0;
	while(*c != '\0'){
		if(*c=='"' || *c==',' || *c=='.' || *c=='?' || *c=='!' || *c==':' || *c==';')
			(w)++;
		else if(*c>=0x30 && *c<=0x39)
			(x)++;
		else if((*c>=0x41 && *c<=0x5A) || (*c>=0x61 && *c<=0x7A))
			(y)++;
		else
			(z)++;
		c++;
	}

	int8_t arr [5];
	int8_t * p = arr;

	LOG_IT(log1,DATA_ALPHA_COUNT,1,my_itoa(p,y,16));

	LOG_IT(log1,DATA_NUMERIC_COUNT,1,my_itoa(p,x,16));

	LOG_IT(log1,DATA_PUNCTUATION_COUNT,1,my_itoa(p,w,16));

	LOG_IT(log1,DATA_MISC_COUNT,1,my_itoa(p,z,16));

	LOG_IT(log1,DATA_ANALYSIS_COMPLETED,1,0);
}

void log_integer(int32_t data)
{
	int8_t dest [20];
	int8_t * ptr = dest;
	ptr = my_itoa(ptr, data, 16);
	log_string(ptr);
}

void log_flush(circ_pre)
{
	while(is_buffer_empty(circ_pre)!=EMPTY){
		uint8_t D = remove_item(circ_pre);
		add_item(circ_ptr, D);
		UART0_C2 |= 0x80;
		__enable_irq();
	}
}

void log_printdata(uint8_t * ptr, uint32_t length)
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
		//sendnbytes( pt , l);
		}
		else
		{
			while(is_buffer_full(circ_ptr)!=FULL)
			{
				add_item(circ_ptr, *ptr);
				ptr++;
			}
		//sendnbytes( pt , circ_ptr->size);
			length = length - circ_ptr->size;

		}

		/*
		__disable_irq();
		UART0_C2 |= 0x80;
		__enable_irq();
		*/
	}
		/*
		__disable_irq();
		uartinit();
		*/
		//UART0_C2 &= 0x7F;

		//sendnbytes(ptr, length)
}

void log_print(uint8_t * ptr)
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

void log_printint(int32_t data)
{
	int8_t dest [20];
	int8_t * ptr = dest;
	ptr = my_itoa(ptr, data, 16);
	log_print(ptr);
}
