/*
 * analysedata.c
 *
 *  Created on: Mar 12, 2017
 *      Author: Jeet
 */
#include "logger.h"
#ifndef VERBOSE
	#include "uart.h"
#endif
#include "analysedata.h"
#include <stdint.h>

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


