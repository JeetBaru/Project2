/********************************************
*   File: spi.h
*
*   Copyrights 2016 Snehal Sanghvi and Shalin Shah
*   All Rights Reserved
*
*   The information contained herein is property of the Authors.
*   The copying and distribution of the files is prohibited except
*   by express written agreement with the Authors.
*
*
*   Author: Snehal Sanghvi and Shalin Shah
*   Date Edited: 9 Nov 2016
*
*   Description: Header file for SPI drivers
*   		
*		SPI_init
*		SPI_write_read_byte
*		SPI_status
*		SPI_flush
*
********************************************************/

#ifndef INCLUDES_SPI_H_
#define INCLUDES_SPI_H_



// Function prototypes
/*****************************************************************************************************
*SPI_init
*	description:This function configures the SPI
*	parameters:
		This function has no parameters
*   return : This function does not return anything
*****************************************************************************************************/
void SPI_init(void);

/*****************************************************************************************************
*	SPI_write_byte
*	description: This function writes the byte by using the SPI_status function SPI0_D.
*	parameters:
		uint8_t byte = The
*   return : This function does not return anything
*****************************************************************************************************/
void SPI_write_byte(uint8_t byte);
/*****************************************************************************************************
*nrf_read_register
*	description:This function reads the byte that has been written in the above function
*	parameters:
		uint8_t byte = The value that we have written in the above function
*   return : This function returns the value that has been written in SPI_write_byte
*****************************************************************************************************/

uint8_t SPI_read_byte(uint8_t byte);

/*****************************************************************************************************
*SPI_send_packet
*	description:This function sends a packet following SPI_write and SPI_read
*	parameters:
				uint8_t* p = The value that we need to write in the SPI_write function is written the address
				pointer p points to after dereferencing it

				uint8_t length = The length of the packet that we need to send
*   return : This function does not return anything
*****************************************************************************************************/
void SPI_send_packet(uint8_t* p, uint8_t length);

/*****************************************************************************************************
*SPI_write_read_byte
*	description: We need call the SPI_write and SPI_read function everytime we use it in the nrf_write and read
				to avoid the buffer overrun condition. Hence I clubbed the two function in this function to
				obtain smooth operation
*	parameters:
		uint8_t byte = 1 byte data that we need to write and read
*   return : This function does not return anything
*****************************************************************************************************/
uint8_t SPI_write_read_byte(uint8_t byte);

/*****************************************************************************************************
*SPI_status
*	description:This function is used to get the SPI_status
*	parameters:
		This function has no parameters
*   return : This function returns the SPI_status
*****************************************************************************************************/
uint8_t SPI_status(void);

/*****************************************************************************************************
*SPI_flush
*	description:The function to flush the SPI
*	parameters:
		This function has no parameters
*   return : This function does not return anything
*****************************************************************************************************/
static void SPI_flush() __attribute__((always_inline));


#endif /* INCLUDES_SPI_H_ */
