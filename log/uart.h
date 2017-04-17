/*
 * uart.h
 *
 *  Created on: Mar 3, 2017
 *      Author: Jeet
 */

#ifndef _UART_H_
#define _UART_H_

#include <stdint.h>
#include "MKL25Z4.h"
#include "logger.h"
#include "cirbuff.h"

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

void uartinit();
void sendbyte(uint8_t data);
uint8_t recievebyte();
void sendnbytes(int8_t * ptr, int32_t l);
void recieve_n_bytes();

#endif /* SOURCES_UART_H_ */
