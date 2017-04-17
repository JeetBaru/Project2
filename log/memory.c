# include "memory.h"
# include <stdint.h>

/*////////////////////////////////////////////////////////////////////////
//Name	   : my_memmov													//
//Params   : source pointer, destination pointer, length				//
//Function : This function moves data of specified length 				//	
//			 from source location to destination. The on moving 		//
//			 to the destination the data at source is made zero.		//
//Returns  : 0 for error, 1 for successful operation					//
////////////////////////////////////////////////////////////////////////*/	

int8_t my_memmov(uint8_t * scr, uint8_t * dest,uint32_t length)
{
	int8_t i;
	if((!scr) || (!dest))					// if either pointer arguement is null return zero
	{
		return 0;
	}
	if(scr>dest)							// if source pointer is less than dest pointer begin moving from begining
	{
		for(i=0;i<length;i++)
		{
			*(dest+i)=*(scr+i);				// copy contents from source to destination
			*(scr+i)=0;						//set contents of source to 0 post moving
		}
	}
	else 									// if source pointer is greater than dest pointer begin moving from end
	{
		for(i=length-1;i>=0;i--)
		{
			*(dest+i)=*(scr+i);				// copy contents from source to destination
			*(scr+i)=0;						//set contents of source to 0 post moving
		}		
	}
	return 1;
}

//////////////////////////////////////////////////////////////////////////
//Name	   : my_memset													//
//Params   : source pointer, data, length								//
//Function : This function copies the specified value of data onto 		//	
//			 the memory location pointed by the source pointer for 		//
//			 length l. The data in memory from address of source 		//
//			 pointer till specified length is overwritten by value.		// 
//Returns  : 0 for error, 1 for successful operation					//
////////////////////////////////////////////////////////////////////////*/

int8_t my_memset(uint8_t * scr, uint32_t length,uint8_t value)
{
	int8_t i;
	if(!scr)							// if pointer arguement is null return zero
	{
		return 0;
	}
	for(i=0;i<length;i++)
	{
		*(scr+i)=value;					// set the value of mem location to value
	}	
	return 1;	
}

/*////////////////////////////////////////////////////////////////////////
//Name	   : my_memzero													//
//Params   : source pointer, length										//
//Function : This function copies 0 onto the memory location pointed	//	
//			 by the source pointer for given length. The data in memory	//
//			 from address of source pointer till specified length		//
//			 is overwritten by 0.										// 
//Returns  : 0 for error, 1 for successful operation					//
////////////////////////////////////////////////////////////////////////*/

int8_t my_memzero(uint8_t *scr, uint32_t length)
{
	int8_t i;
	if(!scr)							// if pointer arguement is null return zero
	{
		return 0;
	}
	for(i=0;i<length;i++)
	{
		*(scr+i)=0; 					// set the value of mem location to value
	}
	return 1;
}

/*////////////////////////////////////////////////////////////////////////
//Name	   : my_rev														//
//Params   : source pointer, length										//
//Function : This function reverses an array of all elements in   		//	
//			 the memorylocation starting at address pointed by  		//
//			 the source pointer till length specified.  				// 
//Returns  : 0 for error, 1 for successful operation					//
////////////////////////////////////////////////////////////////////////*/

int8_t my_rev(uint8_t * ptr,uint32_t length)
{
	length=length-1; 
	int32_t l;
	if(length%2==0)						// For even length, l=length for swapping
	{
		l=length/2;
	}
	else 								// For odd length
	{
		l=(length-1)/2;
	}
	int8_t i;
	int8_t temp;
	for(i=0;i<=l;i++)
	{
		temp=*(ptr+i);					//swapping data on mem to reverse 
		*(ptr+i)=*(ptr+length-i);
		*(ptr+length-i)=temp;
	}
	return 1;
}
