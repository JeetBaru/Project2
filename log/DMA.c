/*
 * DMA.c
 *
 *  Created on: Apr 13, 2017
 *      Author: Jeet
 */

#include "MKL25Z4.h"
#include <stdint.h>
#include "DMA.h"
#include "profiler.h"
#include "memory.h"

dma_status dma_memmove(int8_t * source, int8_t * dest, int16_t length)
{
	if(!source || !dest)
	{
		return DMA_NULL_POINTER;
	}
	if (dest < source)
		dma_move(source,dest,length);
	else
	{
		if(dest >= (source+length))
			dma_move(source,dest,length);
		else
		{
			uint8_t * temp = (int8_t *)malloc(length - (dest - source));
			dma_move(dest , temp, length - (dest - source));
			dma_move(source, dest , (dest-source));
			dma_move(&temp, dest + (dest-source), length-(dest-source) );
		}
	}
	return DMA_SUCCESS;
}

dma_status dma_memzero_32(int8_t * d, int16_t l)
{
	if(!d)
	{
		return DMA_NULL_POINTER;
	}

	if(l==0)
	{
		return DMA_NULL_LENGTH;
	}

	SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
	SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;


	DMA_DSR_BCR0 &= ~DMA_DSR_BCR_DONE_MASK;
	DMA_DCR0 &= ~DMA_DCR_EINT_MASK;

	DMAMUX0_CHCFG0 = 0x00;					//disable DMA

	DMA_DCR0 = 0;

	int32_t s [1]= {0};

	DMA_SAR0 = (uint32_t)&s;

	DMA_DSR_BCR0 |= l;

	DMA_DCR0 |= ( DMA_DCR_EINT_MASK
				| DMA_DCR_EADREQ_MASK		//Enable Async. DMA Requests
				| DMA_DCR_DINC_MASK			//Destination address increments
				| DMA_DCR_D_REQ_MASK		//DMA request is cleared
				);

	DMA_DCR0 &= ~(0x11<<20);
	DMA_DCR0 &= ~(0x11<<17);

	DMA_DAR0 = (uint32_t)d;

	DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK | DMAMUX_CHCFG_SOURCE(60);

	NVIC_EnableIRQ(DMA0_IRQn);
	__enable_irq();

	DMA_DCR0 |= DMA_DCR_START_MASK;

	if(l%4 != 0)
		my_memzero(d+l-l%4,l%4);

	return DMA_SUCCESS;
}

dma_status dma_memzero_16(int8_t * d, int16_t l)
{
	if(!d)
	{
		return DMA_NULL_POINTER;
	}

	if(l==0)
	{
		return DMA_NULL_LENGTH;
	}

	SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
	SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;

	DMA_DSR_BCR0 &= ~DMA_DSR_BCR_DONE_MASK;
	DMA_DCR0 &= ~DMA_DCR_EINT_MASK;

	DMAMUX0_CHCFG0 = 0x00;					//disable DMA

	DMA_DCR0 = 0;

	int32_t s [1]= {0};

	DMA_SAR0 = (uint32_t)&s;

	DMA_DSR_BCR0 |= l;

	DMA_DCR0 |= ( DMA_DCR_EINT_MASK
				| DMA_DCR_EADREQ_MASK		//Enable Async. DMA Requests
				| DMA_DCR_SSIZE(2)			//Source size is 8-bit
				| DMA_DCR_DINC_MASK			//Destination address increments
				| DMA_DCR_DSIZE(2)			//Destination size is 8-bit
				| DMA_DCR_D_REQ_MASK		//DMA request is cleared
				);

	DMA_DAR0 = (uint32_t)d;

	DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK | DMAMUX_CHCFG_SOURCE(60);

	NVIC_EnableIRQ(DMA0_IRQn);
	__enable_irq();

	DMA_DCR0 |= DMA_DCR_START_MASK;

	if(l%4 != 0)
		my_memzero(d+l-l%4,l%4);

	return DMA_SUCCESS;
}

dma_status dma_memzero_8(int8_t * d, int16_t l)
{
	if(!d)
	{
		return DMA_NULL_POINTER;
	}

	if(l==0)
	{
		return DMA_NULL_LENGTH;
	}

	SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
	SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;


	DMA_DSR_BCR0 &= ~DMA_DSR_BCR_DONE_MASK;
	DMA_DCR0 &= ~DMA_DCR_EINT_MASK;

	DMAMUX0_CHCFG0 = 0x00;					//disable DMA

	DMA_DCR0 = 0;

	int32_t s [1]= {0};

	DMA_SAR0 = (uint32_t)&s;

	DMA_DSR_BCR0 |= l;

	DMA_DCR0 |= ( DMA_DCR_EINT_MASK
				| DMA_DCR_EADREQ_MASK		//Enable Async. DMA Requests
				| DMA_DCR_SSIZE(1)			//Source size is 8-bit
				| DMA_DCR_DINC_MASK			//Destination address increments
				| DMA_DCR_DSIZE(1)			//Destination size is 8-bit
				| DMA_DCR_D_REQ_MASK		//DMA request is cleared
				);

	DMA_DAR0 = (uint32_t)d;

	DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK | DMAMUX_CHCFG_SOURCE(60);

	NVIC_EnableIRQ(DMA0_IRQn);
	__enable_irq();

	DMA_DCR0 |= DMA_DCR_START_MASK;

	return DMA_SUCCESS;
}

dma_status dma_memmove_32(int8_t * s, int8_t * d, int16_t l)
{
	if(!d || !s)
	{
		return DMA_NULL_POINTER;
	}

	if(l==0)
	{
		return DMA_NULL_LENGTH;
	}

	if(d == s)
	{
		return DMA_SUCCESS;
	}

	SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
	SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;


	DMA_DSR_BCR0 &= ~DMA_DSR_BCR_DONE_MASK;
	DMA_DCR0 &= ~DMA_DCR_EINT_MASK;

	DMAMUX0_CHCFG0 = 0x00;					//disable DMA

	DMA_DCR0 = 0;

	DMA_SAR0 = (uint32_t)s;

	DMA_DSR_BCR0 |= l;

	DMA_DCR0 |= ( DMA_DCR_EINT_MASK
				| DMA_DCR_EADREQ_MASK		//Enable Async. DMA Requests
				| DMA_DCR_SINC_MASK			//Increment source address after a successful transfer
				| DMA_DCR_DINC_MASK			//Destination address increments
				| DMA_DCR_D_REQ_MASK		//DMA request is cleared
				);

	DMA_DCR0 &= ~(0x11<<20);
	DMA_DCR0 &= ~(0x11<<17);

	DMA_DAR0 = (uint32_t)d;

	DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK | DMAMUX_CHCFG_SOURCE(60);

	NVIC_EnableIRQ(DMA0_IRQn);
	__enable_irq();

	DMA_DCR0 |= DMA_DCR_START_MASK;

	if(l%4 != 0)
		my_memmov(s+l-l%4,d+l-l%4,l%4);

	return DMA_SUCCESS;
}

dma_status dma_memmove_16(int8_t * s, int8_t * d, int16_t l)
{
	SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
	SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;


	DMA_DSR_BCR0 &= ~DMA_DSR_BCR_DONE_MASK;
	DMA_DCR0 &= ~DMA_DCR_EINT_MASK;

	DMAMUX0_CHCFG0 = 0x00;					//disable DMA

	DMA_DCR0 = 0;

	DMA_SAR0 = (uint32_t)s;

	DMA_DSR_BCR0 |= l;

	DMA_DCR0 |= ( DMA_DCR_EINT_MASK
				| DMA_DCR_EADREQ_MASK		//Enable Async. DMA Requests
				| DMA_DCR_SSIZE(2)			//Source size is 8-bit
				| DMA_DCR_SINC_MASK			//Increment source address after a succesful transfer
				| DMA_DCR_DINC_MASK			//Destination address increments
				| DMA_DCR_DSIZE(2)			//Destination size is 8-bit
				| DMA_DCR_D_REQ_MASK		//DMA request is cleared
				);

	DMA_DAR0 = (uint32_t)d;

	DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK | DMAMUX_CHCFG_SOURCE(60);

	NVIC_EnableIRQ(DMA0_IRQn);
	__enable_irq();

	DMA_DCR0 |= DMA_DCR_START_MASK;

	if(l%2 != 0)
		my_memmov(s+l-l%4,d+l-l%4,l%4);

	return DMA_SUCCESS;
}

dma_status dma_memmove_8(int8_t * s, int8_t * d, int16_t l)
{
	if(!d || !s)
	{
		return DMA_NULL_POINTER;
	}

	if(l==0)
	{
		return DMA_NULL_LENGTH;
	}

	if(d == s)
	{
		return DMA_SUCCESS;
	}

	SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
	SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;


	DMA_DSR_BCR0 &= ~DMA_DSR_BCR_DONE_MASK;
	DMA_DCR0 &= ~DMA_DCR_EINT_MASK;

	DMAMUX0_CHCFG0 = 0x00;					//disable DMA

	DMA_DCR0 = 0;

	DMA_SAR0 = (uint32_t)s;

	DMA_DSR_BCR0 |= l;

	DMA_DCR0 |= ( DMA_DCR_EINT_MASK
				| DMA_DCR_EADREQ_MASK		//Enable Async. DMA Requests
				| DMA_DCR_SSIZE(1)			//Source size is 8-bit
				| DMA_DCR_SINC_MASK			//Increment source address after a succesful transfer
				| DMA_DCR_DINC_MASK			//Destination address increments
				| DMA_DCR_DSIZE(1)			//Destination size is 8-bit
				| DMA_DCR_D_REQ_MASK		//DMA request is cleared
				);

	DMA_DAR0 = (uint32_t)d;

	DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK | DMAMUX_CHCFG_SOURCE(60);

	NVIC_EnableIRQ(DMA0_IRQn);
	__enable_irq();

	DMA_DCR0 |= DMA_DCR_START_MASK;

	return DMA_SUCCESS;
}

void dma_move(int8_t * s, int8_t * d, int16_t l)
{
	if(!d || !s)
	{
		return DMA_NULL_POINTER;
	}

	if(l==0)
	{
		return DMA_NULL_LENGTH;
	}

	if(d == s)
	{
		return DMA_SUCCESS;
	}

	uint16_t l1 = l % 4;
	uint16_t l2 = l1 % 2;


	SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
	SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;


	DMA_DSR_BCR0 &= ~DMA_DSR_BCR_DONE_MASK;
	DMA_DCR0 &= ~DMA_DCR_EINT_MASK;

	DMAMUX0_CHCFG0 = 0x00;					//disable DMA

	DMA_DCR0 = 0;

	DMA_SAR0 = (uint32_t)s;

	DMA_DSR_BCR0 |= l - l1;

	DMA_DCR0 |= ( DMA_DCR_EADREQ_MASK		//Enable Async. DMA Requests
				| DMA_DCR_SINC_MASK			//Increment source address after a successful transfer
				| DMA_DCR_DINC_MASK			//Destination address increments
				| DMA_DCR_D_REQ_MASK		//DMA request is cleared
				);

	DMA_DCR0 &= ~(0x11<<20);
	DMA_DCR0 &= ~(0x11<<17);

	DMA_DAR0 = (uint32_t)d;

	DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK | DMAMUX_CHCFG_SOURCE(60);

	DMA_DCR0 |= DMA_DCR_START_MASK;

	DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;

	DMAMUX0_CHCFG0 = 0x00;					//disable DMA

	DMA_DCR0 = 0;

	DMA_SAR0 = s+(l-l1);

	DMA_DSR_BCR0 |= l1-l2;

	DMA_DCR0 |= ( DMA_DCR_EADREQ_MASK		//Enable Async. DMA Requests
				| DMA_DCR_SSIZE(2)			//Source size is 8-bit
				| DMA_DCR_SINC_MASK			//Increment source address after a succesful transfer
				| DMA_DCR_DINC_MASK			//Destination address increments
				| DMA_DCR_DSIZE(2)			//Destination size is 8-bit
				| DMA_DCR_D_REQ_MASK		//DMA request is cleared
				);

	DMA_DAR0 = d+(l-l1);

	DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK | DMAMUX_CHCFG_SOURCE(60);

	DMA_DCR0 |= DMA_DCR_START_MASK;

	DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;

	DMAMUX0_CHCFG0 = 0x00;					//disable DMA

	DMA_DCR0 = 0;

	DMA_SAR0 = s+(l-l2);

	DMA_DSR_BCR0 |= l2;

	DMA_DCR0 |= ( DMA_DCR_EINT_MASK
				| DMA_DCR_EADREQ_MASK		//Enable Async. DMA Requests
				| DMA_DCR_SSIZE(1)			//Source size is 8-bit
				| DMA_DCR_SINC_MASK			//Increment source address after a succesful transfer
				| DMA_DCR_DINC_MASK			//Destination address increments
				| DMA_DCR_DSIZE(1)			//Destination size is 8-bit
				| DMA_DCR_D_REQ_MASK		//DMA request is cleared
				);

	DMA_DAR0 = d+(l-l2);

	DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK | DMAMUX_CHCFG_SOURCE(60);

	NVIC_EnableIRQ(DMA0_IRQn);
	__enable_irq();

	DMA_DCR0 |= DMA_DCR_START_MASK;
}

dma_status dma_memzero( int8_t * d, int16_t l)
{
	if(!d)
	{
		return DMA_NULL_POINTER;
	}

	uint16_t l1 = l % 4;
	uint16_t l2 = l1 % 2;


	SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
	SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;

	DMAMUX0_CHCFG0 = 0x00;					//disable DMA

	DMA_DCR0 = 0;

	DMA_DSR_BCR0 &= ~DMA_DSR_BCR_DONE_MASK;
	DMA_DCR0 &= ~DMA_DCR_EINT_MASK;

	int32_t s [1]= {0};

	DMA_SAR0 = (uint32_t)&s;

	DMA_DSR_BCR0 |= l-l1;

	DMA_DCR0 |= (DMA_DCR_EADREQ_MASK		//Enable Async. DMA Requests
				| DMA_DCR_DINC_MASK			//Destination address increments
				| DMA_DCR_D_REQ_MASK		//DMA request is cleared
				);

	DMA_DCR0 &= ~(DMA_DCR_SINC_MASK);
	DMA_DCR0 &= ~(0x11<<20);
	DMA_DCR0 &= ~(0x11<<17);

	DMA_DAR0 = (uint32_t)d;

	DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK | DMAMUX_CHCFG_SOURCE(60);

	DMA_DCR0 |= DMA_DCR_START_MASK;

	DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;

	DMAMUX0_CHCFG0 = 0x00;					//disable DMA
	DMA_DCR0 = 0x0;

	DMA_SAR0 = (uint32_t)(&s);

	DMA_DSR_BCR0 |= l1 - l2;

	DMA_DCR0 |= ( DMA_DCR_EINT_MASK
				| DMA_DCR_EADREQ_MASK		//Enable Async. DMA Requests
				| DMA_DCR_SSIZE(2)			//Source size is 8-bit
				| DMA_DCR_DINC_MASK			//Destination address increments
				| DMA_DCR_DSIZE(2)			//Destination size is 8-bit
				| DMA_DCR_D_REQ_MASK		//DMA request is cleared
				);

	DMA_DCR0 &= ~(DMA_DCR_SINC_MASK);

	DMA_DAR0 = d+(l-l1);

	DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK | DMAMUX_CHCFG_SOURCE(60);

	DMA_DCR0 |= DMA_DCR_START_MASK;

	DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;

	DMAMUX0_CHCFG0 = 0x00;					//disable DMA

	DMA_DCR0 = 0;

	DMA_SAR0 = (uint32_t)(&s);

	DMA_DSR_BCR0 |= l2;

	DMA_DCR0 |= ( DMA_DCR_EADREQ_MASK		//Enable Async. DMA Requests
				| DMA_DCR_SSIZE(1)			//Source size is 8-bit
				| DMA_DCR_DINC_MASK			//Destination address increments
				| DMA_DCR_DSIZE(1)			//Destination size is 8-bit
				| DMA_DCR_D_REQ_MASK		//DMA request is cleared
				);

	DMA_DCR0 &= ~(DMA_DCR_SINC_MASK);

	DMA_DAR0 = d+(l-l2);

	DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK | DMAMUX_CHCFG_SOURCE(60);

	NVIC_EnableIRQ(DMA0_IRQn);
	__enable_irq();

	DMA_DCR0 |= DMA_DCR_START_MASK;

	return DMA_SUCCESS;
}

void DMA0_IRQHandler(void)
{
	stop_time = STOP_TIMER();
	__disable_irq();
	DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;
}
