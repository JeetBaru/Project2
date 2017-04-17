/*
 * nrf.h
 *
 *  Created on: Apr 12, 2017
 *      Author: Sudeep
 */

#ifndef SOURCES_NRF_H_
#define SOURCES_NRF_H_

#include <stdint.h>

#define __IO volatile



// SPI Command Names
#define NORDIC_R_REGISTER     (0x00)		//Read command and status registers. AAAAA = 5 bit register map address. 1-5 data bytes, LSByte first
#define NORDIC_W_REGISTER     (0x20)		//Write command and status registers. AAAAA = 5 bit register map address. 1-5 data bytes,  LSByte first
#define NORDIC_R_RX_PAYLOAD   (0x61)		//Read RX payload. 1-32 data bytes, LSByte first
#define NORDIC_W_TX_PAYLOAD   (0xA0)		//Write TX payload. 1-32 data bytes, LSByte first
#define NORDIC_FLUSH_TX       (0xE1)		//Flush TX mode. 0 data bytes
#define NORDIC_FLUSH_RX       (0xE2)		//Flush RX mode. 0 data bytes
#define NORDIC_REUSE_TX_PL    (0xE3)		//Reuse last transmitted payload. 0 data bytes
#define NORDIC_NOP            (0xFF)		//No operation. 0 data bytes


//REGISTER MAP
#define NORDIC_CONFIG		(0x00)
#define NORDIC_EN_AA		(0X01)
#define NORDIC_EN_RXADDR	(0X02)
#define NORDIC_SETUP_AW		(0x03)
#define NORDIC_SETUP_RETR	(0x04)
#define NORDIC_RF_CH		(0x05)
#define NORDIC_RF_SETUP		(0x06)
#define NORDIC_STATUS		(0x07)
#define NORDIC_OBSERVE_TX	(0x08)
#define NORDIC_TX_ADDR		(0x10)
#define NORDIC_FIFO_STATUS  (0x17)
#define FLUSH_TX 			(0XE1)
#define FLUSH_RX			(0XE2)

// CONFIG Register Bits
#define NORDIC_CONFIG_MASK_RX_DR(x)  (uint8_t)((uint8_t)(x)<<6)  	// Mask interrupt caused by RX_DR 1: Interrupt not reflected on the IRQ pin 0: Reflect RX_DR as active low interrupt on the IRQ pin
#define NORDIC_CONFIG_MASK_TX_DS(x)  (uint8_t)((uint8_t)(x)<<5)	 	// Mask interrupt caused by TX_DS 1: Interrupt not reflected on the IRQ pin 0: Reflect TX_DS as active low interrupt on the IRQ pin
#define NORDIC_CONFIG_MASK_MAX_RT(x) (uint8_t)((uint8_t)(x)<<4)  	// Mask interrupt caused by MAX_RT 1: Interrupt not reflected on the IRQ pin. 0: Reflect MAX_RT as active low interrupt on the IRQ pin
#define NORDIC_CONFIG_EN_CRC(x)      (uint8_t)((uint8_t)(x)<<3)		// Enable CRC. Forced high if one of the bits in EN_AA is high
#define NORDIC_CONFIG_CRCO_1      	 (0x00)  						// CRC encoding scheme for 1 byte
#define NORDIC_CONFIG_CRCO_2 	  	 (0x04)							// CRC encoding scheme for 2 bytes
#define NORDIC_CONFIG_POWER_UP    	 (0x02)  						// 1: Power up
#define NORDIC_CONFIG_POWER_DOWN  	 (0x00)  						// 0: Power down
#define NORDIC_CONFIG_PRIM_RX     	 (0x01)  						// 1: PRX
#define NORDIC_CONFIG_PRIM_TX     	 (0x00)  						// 0: PTX


// Function prototypes
/*****************************************************************************************************
*nrf_write_register
*	description:This function writes a byte to the register, in this function we call the SPI_write and SPI_read
*	parameters:
		register1 = The register to which the value we want to write
		value    =  The value to be written
*   return : This function does not return anything
*****************************************************************************************************/
void nrf_write_register(uint8_t register1, uint8_t value);
/*****************************************************************************************************
*nrf_read_register
*	description:This function will read the value that has been written this again involves
				the calling of SPI_write and SPI_read
*	parameters:
				register1 = The register to which the value has been previously written
*	returns:
			The return of this function is value that has been written
*****************************************************************************************************/
uint8_t nrf_read_register(uint8_t register1);
/*****************************************************************************************************
*read_status
*	description:This function reads the status after the read write combination
				in which we call SPI_write_read_byte function
*	parameters:
				This function has no parameters
*	returns:
				Returns an enum saying the buffer has been initialised, also it
				sets the size of the circular buffer
*****************************************************************************************************/
uint8_t nrf_read_status();
/*****************************************************************************************************
*nrf_write_config
*	description:The register to which we will write now is 0x00 NORDIC_CONFIG
*	parameters:
		config = The value we need to write to the register
*	returns:
			This function does not return anything
*****************************************************************************************************/
void nrf_write_config(uint8_t config);
/*****************************************************************************************************
*nrf_read_config
*	description: This function reads the value that has been written to the NORDIC_CONFIG register
*	parameters:
		This function has no parameters
*	returns:
		Returns the value that has been written to the register
*****************************************************************************************************/
uint8_t nrf_read_config();
/*****************************************************************************************************
*nrf_write_rf_setup
*	description:The value config that has to be written to NORDIC_RF_SETUP (0X06)
*	parameters:
		config = The value that we need to write to the NORDIC_RF_SETUP
*	returns:
			This function does not return anything
*****************************************************************************************************/
void nrf_write_rf_setup(uint8_t config);
/*****************************************************************************************************
*nrf_read_rf_setup
*	description:This function returns the value that has been written to the register
*	parameters:
		This function has no parameters
*	returns:
			This function returns the value that has been written to NORDIC_RF_SETUP
*****************************************************************************************************/
uint8_t nrf_read_rf_setup();
/*****************************************************************************************************
*nrf_write_rf_Ch
*	description:This function writes the value of the channel given, this
	function calls the nrf_write function
*	parameters:
		channle
*	returns:
			Returns an enum saying the buffer has been initialised, also it
			sets the size of the circular buffer
*****************************************************************************************************/
void nrf_write_rf_ch(uint8_t channel);
/*****************************************************************************************************
*nrf_read_rf_ch
*	description:This function reads the value of channel given by using macro NORDIC_RF_CH
*	parameters:
		This function has no parameters.
*	returns:
			Returns the value of the channel given in the nrf_write_ch
*****************************************************************************************************/
uint8_t nrf_read_rf_ch();
/*****************************************************************************************************
*nrf_write_TX_ADDR
*	description:This function writes 5 bytes, of the TX_ADDR[5]
*	parameters:
		uint8_t * tx_addr = This function takes the pointer to the first element in the array
*	returns:
			This function does not return anything
*****************************************************************************************************/
void nrf_write_TX_ADDR(uint8_t * tx_addr);
/*****************************************************************************************************
*nrf_read_TX_ADDR
*	description:This function reads the 5 bytes data that has been written in the above function
*	parameters:
		This function takes the pointer pointing the first element in the array defined in the main function
*	returns:
			This function does not return anything
*****************************************************************************************************/
void nrf_read_TX_ADDR(uint8_t * tx_addr);
/*****************************************************************************************************
*nrf_read_fifo_status
*	description:This function reads the fifo status, for this the function nrf_read has been called
				and the register parameter that goes into nrf_read NORDIC_FIFO_STATUS
*	parameters:
				This function has no parameters
*	returns:
				This function returns the fifo status
*****************************************************************************************************/
uint8_t nrf_read_fifo_status();
/*****************************************************************************************************
*nrf_flush_rx_fifo
*	description:This function is used to flush the TX_fifo, the macro used
				in the function SPI_write_Read_byte
 	 	 	 	is FLUSH_TX
*	parameters:
				This function has no parameters
*	returns:
				This funtion does not return anything
*****************************************************************************************************/
void nrf_flush_tx_fifo(void);
/*****************************************************************************************************
*nrf_flush_rx_fifo
*	description:This function is used to flush the RX_fifo, the macro used
				in the function SPI_write_read_byte
				is FLUSH_RX
*	parameters:
*				This function does not have any parameters
	returns:
				This function does not return anything
*****************************************************************************************************/
void nrf_flush_rx_fifo(void);

#endif /* SOURCES_NRF_H_ */
