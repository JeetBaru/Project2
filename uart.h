/*
 * uart.h
 *
 *  Created on: Mar 3, 2017
 *      Author: Jeet
 */

#ifndef _UART_H_
#define _UART_H_

#include <stdint.h>i

void uartinit();
void sendbyte(uint8_t data);
uint8_t recievebyte();
void sendnbytes(int8_t * ptr, int32_t l);
void recieve_n_bytes();

#endif /* SOURCES_UART_H_ */
