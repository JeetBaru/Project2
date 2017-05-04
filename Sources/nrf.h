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
#define NORDIC_CD			(0x09)
#define NORDIC_RX_ADDR_P0	(0x0A)
#define NORDIC_RX_ADDR_P1	(0x0B)
#define NORDIC_RX_ADDR_P2	(0x0C)
#define NORDIC_RX_ADDR_P3	(0x0D)
#define NORDIC_RX_ADDR_P4	(0x0E)
#define NORDIC_RX_ADDR_P5	(0x0F)
#define NORDIC_TX_ADDR		(0x10)
#define NORDIC_RX_PW_P0		(0x11)
#define NORDIC_RX_PW_P1		(0x12)
#define NORDIC_RX_PW_P2		(0x13)
#define NORDIC_RX_PW_P3		(0x14)
#define NORDIC_RX_PW_P4		(0x15)
#define NORDIC_RX_PW_P5		(0x16)
#define NORDIC_FIFO_STATUS  (0x17)
#define NORDIC_DYNPD		(0x1C)
#define NORDIC_FEATURE		(0x1D)
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

// RF Setup Register Bits
#define NORDIC_PLL_LOCK(x)					(uint8_t)((uint8_t)(x)<<4) 	//Force PLL lock signal
#define NORDIC_RF_DR_ONE					(0x00)						//Air data rate of 1Mbps
#define NORDIC_RF_DR_TWO					(0x08)						//Air data rate of 2Mbps
#define NORDIC_RF_PWR_NEGATIVE_EIGHTEEN		(0x00)						//RF output power in TX mode of -18dBm
#define NORDIC_RF_PWR_NEGATIVE_TWELVE		(0x02)						//RF output power in TX mode of -12dBm
#define NORDIC_RF_PWR_NEGATIVE_SIX			(0x04)						//RF output power in TX mode of -6dBm
#define NORDIC_RF_PWR_ZERO					(0x06)						//RF output power in TX mode of 0dBm
#define NORDIC_LNA_HCURR(x)					(uint8_t)((uint8_t)(x)<<0)	//Setup LNA gain

// Function prototypes
void nrf_write_register(uint8_t register1, uint8_t value);
uint8_t nrf_read_register(uint8_t register1);
uint8_t nrf_read_status();
void nrf_write_config(uint8_t config);
uint8_t nrf_read_config();
void nrf_write_rf_setup(uint8_t config);
uint8_t nrf_read_rf_setup();
void nrf_write_rf_ch(uint8_t channel);
uint8_t nrf_read_rf_ch();
void nrf_write_TX_ADDR(uint8_t * tx_addr);
void nrf_read_TX_ADDR(uint8_t * tx_addr);
uint8_t nrf_read_fifo_status();
void nrf_flush_tx_fifo(void);
void nrf_flush_rx_fifo(void);

#endif /* SOURCES_NRF_H_ */
