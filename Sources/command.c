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

	cmd_msg[j].command = recievebyte();
	sendbyte(cmd_msg[j].command);
	if(cmd_msg[j].command == '0' || cmd_msg[j].command == '1' || cmd_msg[j].command == '6')
	{
		cmd_msg[j].length = '1';
	}
	else if(cmd_msg[j].command == '7' || cmd_msg[j].command == '8')
	{
		cmd_msg[j].length = '0';
	}
	else
	{
		cmd_msg[j].length = recievebyte();
	}
	sendbyte(cmd_msg[j].length);

	cmd_msg[j].data = malloc(sizeof(uint8_t) * (cmd_msg[j].length - 0x30));

	for(i = 0; i <cmd_msg[j].length - 0x30; i++)
	{
		*(cmd_msg[j].data + i) = recievebyte() - 0x30;
		sendbyte(*(cmd_msg[j].data + i) + 0x30);
	}
	checksum = recievebyte();
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
	if (cmd_msg[i].command == '0')
	{
		LED_ON_IT(*cmd_msg[i].data);
	}
	else if (cmd_msg[i].command == '1')
	{
		LED_OFF_IT(*cmd_msg[i].data);
	}
	else if (cmd_msg[i].command == '2')
	{
		for(;j<cmd_msg[i].length - 0x30 ;j++)
			data = data*10 + *(cmd_msg[i].data +j);
		LED_SET_BRIGHTNESS(3,data);
		data = 0;
	}
	else if (cmd_msg[i].command == '3')
	{
		for(;j<cmd_msg[i].length - 0x30 ;j++)
			data = data*10 + *(cmd_msg[i].data + j);
		LED_SET_BRIGHTNESS(0,data);
		data = 0;
	}
	else if (cmd_msg[i].command == '4')
	{
		for(;j<cmd_msg[i].length - 0x30 ;j++)
			data = data*10 + *(cmd_msg[i].data + j);
		LED_SET_BRIGHTNESS(1,data);
		data = 0;
	}
	else if (cmd_msg[i].command == '5')
	{
		for(;j<cmd_msg[i].length - 0x30 ;j++)
			data = data*10 + *(cmd_msg[i].data + j);
		LED_SET_BRIGHTNESS(2,data);
		data = 0;
	}
	else if (cmd_msg[i].command == '6')
	{
		LED_SET_COLOR(*cmd_msg[i].data);
	}
	else if (cmd_msg[i].command == '7')
	{
		sendnbytes(my_itoa(a,get_time(),16),9);
	}
	else if (cmd_msg[i].command == '8')
	{
		NVIC_SystemReset();
	}

	return 0;
}

uint16_t validate(uint8_t j)
{
	uint32_t sum = 0;
	uint16_t i;
	for(i=0;i<cmd_msg[j].length - 0x30;i++)
	{
		sum=sum+*(cmd_msg[j].data+i);
	}
	sum = sum + cmd_msg[j].command - 0x30 + cmd_msg[j].length - 0x30;
	if(sum == cmd_msg[j].checksum)
	{
		sendnbytes("Valid Data", 10);
		return 1;
	}
	else
	{
		sendnbytes("Invalid Data", 12);
		return 0;
	}
}
