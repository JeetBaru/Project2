/*
 * command.c
 *
 *  Created on: Apr 25, 2017
 *      Author: Jeet
 */

#include "uart.h"
#include "logger.h"
#include <stdint.h>
#include "command.h"
#include "LED.h"
#include "MKL25Z4.h"
#include "RTC.h"

uint16_t get_command(uint8_t j)
{
	uint8_t i = 0;
	uint16_t checksum;

	cmd_msg[j].command = recievebyte();									//receive the first comandID
	sendbyte(cmd_msg[j].command);
	if(cmd_msg[j].command == LED_ON || cmd_msg[j].command == LED_OFF || cmd_msg[j].command == COLOR)
	{
		cmd_msg[j].length = '1';										//if command is LED On LED off or LED color set length of data to 1
	}
	else if(cmd_msg[j].command == TIMESTAMP || cmd_msg[j].command == RESET)
	{
		cmd_msg[j].length = '0';										//if reset or timestamp length is 0
	}
	else
	{
		cmd_msg[j].length = recievebyte();								//else receive length
	}
	sendbyte(cmd_msg[j].length);

	cmd_msg[j].data = malloc(sizeof(uint8_t) * (cmd_msg[j].length - 0x30)); // assign variabled sized memory to data

	for(i = 0; i <cmd_msg[j].length - 0x30; i++)
	{
		*(cmd_msg[j].data + i) = recievebyte() - 0x30;					//receive array of data
		sendbyte(*(cmd_msg[j].data + i) + 0x30);
	}
	checksum = recievebyte();											//receive 2 digit checksum
	sendbyte(checksum);
	cmd_msg[j].checksum = (checksum - 0x30)*10 + (recievebyte() - 0x30);
	sendbyte(cmd_msg[j].checksum + 0x30);

	return 0;
}

uint16_t decode_command(uint8_t i)
{
	uint8_t j=0;					
	uint32_t data = 0;
	int a[8];
	if (cmd_msg[i].command == LED_ON)							
	{
		LED_ON_IT(*cmd_msg[i].data);									//call LED on
	}
	else if (cmd_msg[i].command == LED_OFF)
	{
		LED_OFF_IT(*cmd_msg[i].data);									//call LED off
	}
	else if (cmd_msg[i].command == BRIGHTNESS_R)
	{
		for(;j<cmd_msg[i].length - 0x30 ;j++)
			data = data*10 + *(cmd_msg[i].data +j);
		LED_SET_BRIGHTNESS(3,data);
		data = 0;
	}
	else if (cmd_msg[i].command == BRIGHTNESS_G)									//Call LED brightness for individual LEDs
	{
		for(;j<cmd_msg[i].length - 0x30 ;j++)
			data = data*10 + *(cmd_msg[i].data + j);
		LED_SET_BRIGHTNESS(0,data);
		data = 0;
	}
	else if (cmd_msg[i].command == BRIGHTNESS_B)
	{
		for(;j<cmd_msg[i].length - 0x30 ;j++)
			data = data*10 + *(cmd_msg[i].data + j);
		LED_SET_BRIGHTNESS(1,data);
		data = 0;
	}
	else if (cmd_msg[i].command == BRIGHTNESS_ALL)
	{
		for(;j<cmd_msg[i].length - 0x30 ;j++)
			data = data*10 + *(cmd_msg[i].data + j);
		LED_SET_BRIGHTNESS(2,data);
		data = 0;
	}
	else if (cmd_msg[i].command == COLOR)									//call LED set color
	{
		LED_SET_COLOR(*cmd_msg[i].data);
	}
	else if (cmd_msg[i].command == TIMESTAMP)
	{
		sendnbytes(my_itoa(a,get_time(),16),9);							//call timestamp
	}
	else if (cmd_msg[i].command == RESET)
	{
		NVIC_SystemReset();												//call system reset
	}
	else
	{
		sendnbytes("Invalid Command",15);
		return 0;
	}
	
	return 1;
}

uint16_t validate(uint8_t j)
{
	uint32_t sum = 0;
	uint16_t i;
	for(i=0;i<cmd_msg[j].length - 0x30;i++)
	{
		sum=sum+*(cmd_msg[j].data+i);									//calculate sum of data digits
	}
	sum = sum + cmd_msg[j].command - 0x30 + cmd_msg[j].length - 0x30;	//include sum of cammand IDs and length
	if(sum == cmd_msg[j].checksum)
	{
		sendnbytes("Valid Data", 10);									//log validity of Data
		return 1;
	}
	else
	{
		sendnbytes("Invalid Data", 12);
		return 0;
	}
}
