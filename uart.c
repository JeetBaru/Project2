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


void uartinit()
{
	SIM_SOPT2 |= FLL_CLOCK_MASK;   //select clock as MCGFLLCLK

	SIM_SCGC4 |= CLOCK_GATE_ENABLE;  //Enable clock gate

	UART0_C2 = ZERO_OUT;

	UART0_C1 = ZERO_OUT;

	UART0_C4 = OSR_MASK;

	UART0_BDH = BDH_MASK;
	UART0_BDL = BDL_MASK;

	NVIC->ISER[0] |= NVIC_ISER_MASK;

	UART0_C2 = RX_TX_ENABLE;

	SIM_SCGC5 |= ENABLE_PORTA_CLK;  //Enable PORT A Clock
	PORTA_PCR1=PORTA_UART_PINENABLE;
	PORTA_PCR2=PORTA_UART_PINENABLE;

	LOG_IT(log1,GPIO_INITIALIZED,1,0);

}

void sendbyte(uint8_t data)
{
	uartinit();
	while(!(UART0_S1 & DATA_TRANSMIT_READY)){}
	UART0_D=data;
}

uint8_t recievebyte()
{
	uartinit();
	uint8_t c;
	while(!(UART0_S1 & DATA_RECIEVED));
	c=UART0_D;
	return c;
}

void sendnbytes(int8_t * ptr, int32_t l)
{
	uartinit();
	int32_t i;
	for(i=0;i<l;i++)
	{
		while(!(UART0_S1 & DATA_TRANSMIT_READY));
		UART0_D=*ptr;
		ptr++;
	}
}

void recieve_n_bytes()
{
	while(1){
		if(is_buffer_full(circ_pre)==NO && (UART0_S1 & 40)){
			UART0_C2 |= DATA_RECIEVED;
			__enable_irq();
		}
		else if(is_buffer_full(circ_pre)==FULL){
			__disable_irq();
			break;
		}
	}
}

void send_n_bytes()
{
	UART0_C2 &= 0x7F;
	UART0_D = remove_item(circ_ptr);
	if(is_buffer_empty(circ_ptr) != EMPTY)
	{
		UART0_C2 |= 0x80;
		__enable_irq();
	}
}

void UART0_IRQHandler()
{
	__disable_irq();
	if(UART0_C2 & 0x80)
	{
		send_n_bytes();
	}
	else if (UART0_C2 & 0x20)
	{
		UART0_C2 &= 0xDF;
		add_item(circ_pre,UART0_D);
	}
}


////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
