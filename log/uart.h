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

#ifndef _UART_H_
#define _UART_H_

#include <stdint.h>
#include "MKL25Z4.h"
#include "logger.h"
#include "cirbuff.h"

//Macros to various MASKS to UARTD registers
#define FLL_CLOCK_MASK 0x04000000
#define CLOCK_GATE_ENABLE 0x00000400
#define ZERO_OUT 0x0
#define OSR_MASK 0x0F
#define BDH_MASK 0x00
#define BDL_MASK 0x17
#define NVIC_ISER_MASK 0x00001000
#define RX_TX_ENABLE 0x0C
#define ENABLE_PORTA_CLK 0x200
#define PORTA_UART_PINENABLE 0x200
#define DATA_RECIEVED 0x20
#define DATA_TRANSMIT_READY 0x80
#define DATA_TRANSMITTED 0x40

/*****************************************************************************************************
*uartinit
*	description:This function initializes UART registers to required values

*****************************************************************************************************/
void uartinit();

/*****************************************************************************************************
*send byte
*	description:this function send single byte using polling
*	parameters:
		uint8_t data - data to be sent
*****************************************************************************************************/
void sendbyte(uint8_t data);

/*****************************************************************************************************
*recieve byte
*	description:this function recieves single byte using polling
*	returntype:
		uint8_t data - data to be received
*****************************************************************************************************/
uint8_t recievebyte();

/*****************************************************************************************************
*send byte
*	description:this function send n bytes using polling
*	parameters:
		uint8_t * ptr - pointer to data to be sent
		int32_t l - length of data to be sent
*****************************************************************************************************/
void sendnbytes(int8_t * ptr, int32_t l);

/*****************************************************************************************************
*recieve n bytes
*	description:this function recieve multiple byte using interrupts
		data recieved is stored in circ_pre receiver buffer
*****************************************************************************************************/
void recieve_n_bytes();

/*****************************************************************************************************
*send n bytes
*	description:this function send multiple byte using interrupts
		data is sent from th transmit buffer
*****************************************************************************************************/
void send_n_bytes()

#endif /* SOURCES_UART_H_ */
