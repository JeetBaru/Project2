/* Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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
	//uartinit();
	while(!(UART0_S1 & DATA_TRANSMIT_READY)){}		//wait till transmission complete
	UART0_D=data;									//trransmit data
}

//Receive single byte
uint8_t recievebyte()
{
	//uartinit();
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
	START_CRITICAL();				//first disable any interrupts
	if(UART0_C2 & 0x80)				//if transmit interrupt
	{
		send_n_bytes();				//send byte
	}
	else if (UART0_C2 & 0x20)		// if receive interrupt
	{
		UART0_C2 &= 0xDF;
		add_item(circ_pre,UART0_D);
	}
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
