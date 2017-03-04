# include "MKL25Z4.h"
# include "uart.h"

void log_data(int8_t * ptr,int32_t length)
{
	sendnbytes( ptr , length);
}

void log_string(int8_t * ptr)
{
	int32_t length=0;
	while(*ptr != '\0')
	{
		length++;
		ptr++;
	}
	sendnbytes( ptr-length, length);
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
		while(d!=0)						//counts number of digits required
		{
			count++;
			d=d/base;
		}
		if(data>=0)						//Stores '+' in 1st position for positive number
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

void log_integer(int32_t data)
{
	int8_t dest [20];
	int8_t * ptr = dest;
	ptr = my_itoa(ptr, data, 16);
	log_string(ptr);
}
