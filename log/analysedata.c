/**************************************************************************************
*   File: cirbuff.h
*
*   Copyrights 2016  Sudeep Kulkarniirlekar and Jeet Baru
*   All Rights Reserved
*
*
*   The information contained herein is property of the Authors. 
*   The copying and distribution of the files is prohibited except
*   by express written agreement with the Authors.
*
*
*   Authors: Sudeep Kulkarniirlekar and Jeet Baru
*   Date Edited: 12 March 2017
*
*   Description: Source file for implementing Circular buffer functions
*              - CircBuf_size 
*              - is_buffer_full
*	       - is_buffer_empty
*              - initialize_buffer
*              - destroy_buffer
*              - add_item
*              - remove_item
*	       - cirbuf_peak
*
****************************************************************************************/
#include "analysedata.h"

//this function is used to analyse entered data
void analyse_data(int8_t * c)
{
	LOG_IT(log1,DATA_ANALYSIS_STARTED,1,0);							//Logs begining of data analysis

	int8_t w=0,x=0,y=0,z=0;											//initialize counter to 0
	while(*c != '\0'){
		if(*c=='"' || *c==',' || *c=='.' || *c=='?' || *c=='!' || *c==':' || *c==';')
			(w)++;													//check for punctuation marks
		else if(*c>=0x30 && *c<=0x39)
			(x)++;													//check for numericals
		else if((*c>=0x41 && *c<=0x5A) || (*c>=0x61 && *c<=0x7A))
			(y)++;													//check for letters both upper and lower case
		else
			(z)++;													//count miscellaneous characters
		c++;
	}

	int8_t arr [5];
	int8_t * p = arr;

	LOG_IT(log1,DATA_ALPHA_COUNT,1,my_itoa(p,y,16));				//log the number of alphabets by converting int to ascii

	LOG_IT(log1,DATA_NUMERIC_COUNT,1,my_itoa(p,x,16));				//log the number of numerics by converting int to ascii

	LOG_IT(log1,DATA_PUNCTUATION_COUNT,1,my_itoa(p,w,16));			//log the number of punctuations by converting int to ascii

	LOG_IT(log1,DATA_MISC_COUNT,1,my_itoa(p,z,16));					//log the number of other characters by converting int to ascii

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


