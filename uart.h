/*
 * uart.h
 *
 *  Created on: Mar 3, 2017
 *      Author: Jeet
 */

#ifndef SOURCES_UART_H_
#define SOURCES_UART_H_

void uartinitrx();
void uartinittx();
void sendbyte(uint8_t data);
uint8_t recievebyte();
void sendnbytes(int8_t * ptr, int32_t l);

#endif /* SOURCES_UART_H_ */
