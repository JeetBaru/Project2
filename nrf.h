#ifndef __NRF__H_
#define __NRF__H_



#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

uint16_t spi_fd;
/* Macros definition */
#define TX_ADDR_SIZE (5)
/* Macros */
#define NRF_CONFIG_REG  (0x00)
#define NRF_TXADDR_REG  (0x10)
#define NRF_EN_AA_REG   (0x01)
#define NRF_EN_RXADDR_REG       (0x02)
#define NRF_SETUP_AW_REG        (0x03)
#define NRF_SETUP_RETR_REG      (0x04)
#define NRF_RF_CH_REG   (0x05)
#define NRF_RF_SETUP_REG        (0x06)
#define NRF_STATUS_REG  (0x07)
#define RX_ADDR_P0_REG  (0x0A)
#define NRF_TX_ADDR     (0x10)
#define NRF_FIFO_STATUS_REG     (0x17)
#define NRF_PIPESIZE    (0X11) 
#define NRF_ENRXADDR    (0x02)
#define W_TXPAYLOAD     (0xA0)
#define R_RXPAYLOAD     (0x61)
    
#define NRF_R_REGISTER  (0x00)          
#define NRF_W_REGISTER  (0x20) 
#define NRF_NOP (0xFF) 
#define NRF_FLUSH_TX    (0xE1)
#define NRF_FLUSH_RX    (0xE2)

void nordic_enable(uint8_t port);

void nrf_high(uint8_t port);

void nrf_low(uint8_t port);

void nrf_write_config(uint16_t spi_fd, uint8_t port);

uint8_t nrf_read_config(uint16_t spi_fd, uint8_t port);

void nrf_write_RF_setup(uint16_t spi_fd, uint8_t port);

uint8_t nrf_read_RF_setup(uint16_t spi_fd, uint8_t port);

void nrf_write_RF_channel(uint16_t spi_fd, uint8_t port);

uint8_t nrf_read_RF_channel(uint16_t spi_fd, uint8_t port);

void nrf_write_TXADDR(uint16_t spi_fd, uint8_t port);

void nrf_read_TXADDR(uint16_t spi_fd, uint8_t port);

#endif

