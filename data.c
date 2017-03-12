/******************************************************
*   File: data.c
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
*   Authors: Sudeep Kulkarniirlekar and Jeet BAru
*   Date Edited: 12 March 2017
*
*   Description: Source file for implementing Circular buffer functions
*              - my_itoa
*              - my_atoi
*	       - big_to_little32
*              - little_to_big32
*              - print_memory
*              
********************************************************/
#include "data.h"
#include "uni.h"


//This function converts the given data into its equivalent with the specified base and store the result as a string  	
//in the memory location starting from destination pointer

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

//This function converts the given ascii string starting from memory location pointed at by source   		
//pointer to integer data value of base 10 provided 		
//all characters are digits.
int32_t my_atoi(int8_t * str)
{
	int32_t data=0; 													//initializing data and sign
	int8_t sign=1;														
	int8_t * ptr;														
	ptr=str;
	int8_t c=0,k=0;
	if(str == '\0') 													//Check for null termination and return zero
	{
		return 0;
	}
	while(*ptr!='\0')
	{
		if((*ptr>=0x30 && *ptr <=0x39) || (*ptr=='-') || (*ptr=='+'))	//checks if all characters are digits and hence valid
		{
			c++;
		}
		k++;
		ptr++;
	}
	if(c!=k)															//if invalid characters return zero
	{
		return 0;
	}
	else
	{
		if(*str=='-')													//if first character is '-' put sign = -1
		{
			sign=-1;
			str++;
		}
		else if(*str=='+')												//if first character is '+' put sign = 1
		{
			sign=1;
			str++;
		}
		else 															//if neither take sign = 1
		{
			sign=1;
		}
		while(*str!='\0')
		{
			data=data*10+((int)(*str)-48);								//calculate data
			str++;
			if(data>214748364 && *str!='\0')							//check for int overflow, if present return zero
			{
				return 0;
			}
		}
		return sign*data;										//return data with sign
	}
}


//This function converts the given 32 bit data stored in big endian form starting from memory location pointed  
//at by data pointer to its little endian form. This continues for provided length. length is number 	
//of such 32 bit data entries
int8_t big_to_little32(uint32_t * data,uint32_t length)
{
	uint8_t * p;
	p=(uint8_t *)data; 				//cast 8 bit  pointer onto 32 bit data pointer to deal with each byte individually
	uint32_t i,temp;
	if( !data )						//if null pointer recieved return zero
	{
		return NULL_PTR;
	}
	if( length<=0 )
	{
		return INV_LENGTH;
	}
	for(i=1;i<=length;i++)
	{
		temp=*p;					//swap 1st and 4th bit
		*p=*(p+3);
		*(p+3)=temp;
		temp=*(p+1); 				//swap 2nd and 3rd bit
		*(p+1)=*(p+2);
		*(p+2)=temp;
		p=p+4;						//pointer increamented to point at next 4 byte data
	}
	return SUCCESS;
}

//This function converts the given 32 bit data stored in little endian form starting from memory location pointed  	
//at by data pointer to its big endian form. This continues for provided length. length is number 		
//of such 32 bit data entries

int8_t little_to_big32(uint32_t * data,uint32_t length)
{
	uint8_t * p;
	p=(uint8_t *)data; 				//cast 8 bit  pointer onto 32 bit data pointer to deal with each byte individually
	uint32_t i,temp;
	if( !data )						//if null pointer recieved return zero
	{
		return NULL_PTR;
	}
	if( length<=0 )
	{
		return INV_LENGTH;
	}
	for(i=1;i<=length;i++)
	{
		temp=*p;					//swap 1st and 4th bit
		*p=*(p+3);
		*(p+3)=temp;
		temp=*(p+1); 				//swap 2nd and 3rd bit
		*(p+1)=*(p+2);
		*(p+2)=temp;
		p=p+4;						//pointer increamented to point at next 4 byte data
	}
	return SUCCESS;
}

//This function prints contents of memory starting from memory location pointed at by start till the specified 
//length. It prints the hex equivalent of the data stored

void print_memory(uint8_t * start, uint32_t length)
{
	while(length>0)
	{
		printf("%x ",*start);			//prints hex equivalent of memory
		start++;
		length--;
	}
}
