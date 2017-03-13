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

#include "uart.h"

//This function is used to initialize UART
void uartinit()
{
	SIM_SOPT2 |= FLL_CLOCK_MASK;   					//select clock as MCGFLLCLK

	SIM_SCGC4 |= CLOCK_GATE_ENABLE;  				//Enable clock gate to MCGFLLCLK

	UART0_C2 = ZERO_OUT;							//initially reset control registers of UART0

	UART0_C1 = ZERO_OUT;

	UART0_C4 = OSR_MASK;							//Set OSR to 15

	UART0_BDH = BDH_MASK;							//Set Baud rate divisor modulo
	UART0_BDL = BDL_MASK;							//such that Baud Rate is 57600

	NVIC->ISER[0] |= NVIC_ISER_MASK;				//Enable IRQ12 for UART0

	UART0_C2 = RX_TX_ENABLE;						//Enable UART receiver transmitter

	SIM_SCGC5 |= ENABLE_PORTA_CLK;  				//Enable PORT A Clock
	PORTA_PCR1=PORTA_UART_PINENABLE;				//Enable PORT A pins 1 and 2 for UART
	PORTA_PCR2=PORTA_UART_PINENABLE;

	LOG_IT(log1,GPIO_INITIALIZED,1,0);				//log initialization
}

//Send single byte
void sendbyte(uint8_t data)
{
	uartinit();
	while(!(UART0_S1 & DATA_TRANSMIT_READY)){}		//wait till transmission complete
	UART0_D=data;									//trransmit data
}

//Receive single byte
uint8_t recievebyte()
{
	uartinit();
	uint8_t c;
	while(!(UART0_S1 & DATA_RECIEVED));				//wait till receive complete
	c=UART0_D;										//receive data
	return c;										//return received data
}

//Send n bytes using blocking
void sendnbytes(int8_t * ptr, int32_t l)
{
	uartinit();
	int32_t i;
	for(i=0;i<l;i++)
	{
		while(!(UART0_S1 & DATA_TRANSMIT_READY));	//send each byte by blocking
		UART0_D=*ptr;
		ptr++;
	}
}

//Receive data using interrupts
void recieve_n_bytes()
{
	while(1){
		if(is_buffer_full(circ_pre)==NO && (UART0_S1 & 40)){	//check if receive buffer full and transmission complete
			UART0_C2 |= DATA_RECIEVED;							//Enable receive interrupt
			__enable_irq();										//jumps to irq handler
		}
		else if(is_buffer_full(circ_pre)==FULL){				//if circ buffer is full
			__disable_irq();									//disable irq and continue
			break;
		}
	}
}

//send bytes using interrupts
void send_n_bytes()
{
	UART0_C2 &= 0x7F;								//disable transmit interrupt unless complete
	UART0_D = remove_item(circ_ptr);				//remove item from transmit buffer
	if(is_buffer_empty(circ_ptr) != EMPTY)			//if not empty
	{
		UART0_C2 |= 0x80;							//enable transmit interrupt
		__enable_irq();								//execution goes to IRQ handler
	}
}

void UART0_IRQHandler()
{
	__disable_irq();				//first disable any interrupts
	if(UART0_C2 & 0x80)				//if transmit interrupt
	{
		send_n_bytes();				//send byte
	}
	else if (UART0_C2 & 0x20)		// if receive interrupt
	{
		UART0_C2 &= 0xDF;
		add_item(circ_pre,UART0_D); // add item to receive buffer
	}
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
