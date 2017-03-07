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

#include "MKL25Z4.h"


void uartinit()
{
	//SIM_SOPT2 &= 0xF7FFFFFF;


	SIM_SOPT2 |= 0x04000000;   //select clock as MCGFLLCLK

	SIM_SCGC4 |= 0x00000400;  //Enable clock gate

	//SIM_SOPT5 &= 0xFFFEFFFB;
	UART0_C2 = 0x00;

	UART0_C4 = 0x0F;

	UART0_C1 = 0x00;

	UART0_BDH = 0x00;
	UART0_BDL = 0x17;

	NVIC->ISER[0] |= 0x00001000;

	UART0_C2 = 0x0C;

	SIM_SCGC5 |= 0x200;  //Enable PORT A Clock
	PORTA_PCR1=0x200;
	PORTA_PCR2=0x200;

}
/*
void uartinittx()
{
	SIM_SOPT2 |= 0x04000000;   //select clock as MCGFLLCLK
	//SIM_SOPT2 &= 0xF7FFFFFF;

	SIM_SCGC4 |= 0x00000400;   //Enable clock gate
	//SIM_SOPT5 &= 0xFFFEFFFC;

	UART0_C2 = 0x00;

	UART0_BDH = 0x00; //baud 57600
	UART0_BDL = 0x17;

	UART0_C4 = 0x0F;
	UART0_C1 = 0x00;
	UART0_C2 = 0x0C;

	SIM_SCGC5 |= 0x200;  //Enable PORTA clock
	PORTA_PCR2=0x200;
}
*/
void sendbyte(uint8_t data)
{
	uartinit();
	while(!(UART0_S1 & 0x80)){}
	UART0_D=data;
}

uint8_t recievebyte()
{
	uartinit();
	uint8_t c;
	while(!(UART0_S1 & 0x20));
	c=UART0_D;
	return c;
}

void sendnbytes(int8_t * ptr, int32_t l)
{
	uartinit();
	int32_t i;
	for(i=0;i<l;i++)
	{
		while(!(UART0_S1 & 0x80));
		UART0_D=*ptr;
		ptr++;
	}
}

/*
int main(void)
{
	uartinittx();
	int8_t d[] ="12345678";
	int8_t * ptr = d;
	sendnbytes(ptr, 8);
	uartinitrx();
	uint8_t data = recievebyte();
	//int8_t  = 0x11;
	uartinittx();
	sendbyte(data);
	return 0;
}
*/
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
