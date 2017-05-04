#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include "nrf.h"

typedef enum {
  SPI_MSBFIRST, ///< Most significant bit first
  SPI_LSBFIRST  ///< Least significant bit first
} SPI_bit_order;

//uint8_t spi_fd;
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
/* CONFIG Register Bits */
#define NRF_CONFIG_MASK_TX_DS(x)        (uint8_t)((uint8_t)(x)<<5) /* Mask interrupt caused by TX_DS 1: Interrupt not reflected on the IRQ pin 0: Reflect TX_DS as active low interrupt on the IRQ pin */
#define NRF_CONFIG_MASK_MAX_RT(x)       (uint8_t)((uint8_t)(x)<<4) /* Mask interrupt caused by MAX_RT 1: Interrupt not reflected on the IRQ pin. 0: Reflect MAX_RT as active low interrupt on the IRQ pin */
#define NRF_CONFIG_EN_CRC(x)    (uint8_t)((uint8_t)(x)<<3)         /* Enable CRC. Forced high if one of the bits in EN_AA is high
#define NRF_CONFIG_CRCO_1       (0x00)                                                     /* CRC encoding scheme for 1 byte */
#define NORDIC_CONFIG_CRCO_2    (0x04)
#define NRF_CONFIG_POWER_UP     (0x02)                                                     /* 1: Power up */
#define NRF_CONFIG_POWER_DOWN   (0x00)                                             /* 0: Power down */
#define NRF_CONFIG_PRIM_RX      (0x01)                                                 /* 1: PRX */
#define NRF_CONFIG_PRIM_TX      (0x00)                                                     /* 0: PTX */

/* RF Setup Register Bits */
#define NORDIC_PLL_LOCK(x)                                      (uint8_t)((uint8_t)(x)<<4)      /* Force PLL lock signal */
#define NORDIC_RF_DR_ONE                                        (0x00)                                          /* Air data rate of 1Mbps */
#define NORDIC_RF_DR_TWO                                        (0x08)                                          /* Air data rate of 2Mbps */
#define NORDIC_RF_PWR_NEGATIVE_EIGHTEEN         (0x00)                                          /* RF output power in TX mode of -18dBm */
#define NORDIC_RF_PWR_NEGATIVE_TWELVE           (0x02)                                          /* RF output power in TX mode of -12dBm */
#define NORDIC_RF_PWR_NEGATIVE_SIX                      (0x04)                                          /* RF output power in TX mode of -6dBm */
#define NORDIC_RF_PWR_ZERO                                      (0x06)                                          /* RF output power in TX mode of 0dBm */
#define NORDIC_LNA_HCURR(x) (uint8_t)((uint8_t)(x)<<0)                                  /* Setup LNA gain */


/// Buffer size at least large enough to fit the max length of "/dev/spidevX.Y"
#define SPIDEV_PATH_LEN 20
 /// Maximum transfer size set to standard page size of 4096 bytes
#define MAX_TRANSFER_SIZE 4096

int SPI_open(uint8_t bus, uint8_t cs) {
  char device[SPIDEV_PATH_LEN];
  sprintf(device, "/dev/spidev%d.%d", bus, cs);
  return open(device, O_RDWR, 0);
}

int SPI_setMode(int spidev_fd, uint8_t mode) {
  if (ioctl(spidev_fd, SPI_IOC_WR_MODE, &mode) < 0) return -1;
  return 0;
}

void SPI_close(int spidev_fd) {
  close(spidev_fd);
}
int SPI_read(int spidev_fd, void *rx_buffer, int n_words) {
  uint8_t bits_per_word;
  uint32_t n_bytes;
  struct spi_ioc_transfer transfer;
  bits_per_word = SPI_getBitsPerWord(spidev_fd);
  if (bits_per_word < 0) return bits_per_word;
  // Round up to the next biggest number of bytes:
  n_bytes = (uint32_t) (((float) (bits_per_word * n_words)) / 8.0 + 0.5);
  if (!n_bytes) return 0;
  if (n_bytes > MAX_TRANSFER_SIZE) n_bytes = MAX_TRANSFER_SIZE;

  memset((void *) &transfer, 0, sizeof(struct spi_ioc_transfer));
  transfer.tx_buf = 0;
  transfer.rx_buf = (uintptr_t) rx_buffer;
  transfer.len = n_bytes;
  transfer.speed_hz = 0;
  transfer.delay_usecs = 0;
transfer.bits_per_word = bits_per_word;
  transfer.cs_change = 0;
  if (ioctl(spidev_fd, SPI_IOC_MESSAGE(1), &transfer) < 0) return -1;
  return (n_bytes<<3) / bits_per_word;
}

int SPI_write(int spidev_fd, void *tx_buffer, int n_words) {
  uint8_t bits_per_word;
  uint32_t n_bytes;
  struct spi_ioc_transfer transfer;
  bits_per_word = SPI_getBitsPerWord(spidev_fd);
  if (bits_per_word < 0) return bits_per_word;
  n_bytes = (uint32_t) (((float) (bits_per_word * n_words)) / 8.0 + 0.5);
  if (!n_bytes) return 0;
  if (n_bytes > MAX_TRANSFER_SIZE) n_bytes = MAX_TRANSFER_SIZE;

  memset((void *) &transfer, 0, sizeof(struct spi_ioc_transfer));
  transfer.tx_buf = (uintptr_t) tx_buffer;
  transfer.rx_buf = 0;
  transfer.len = n_bytes;
  transfer.speed_hz = 0;
  transfer.delay_usecs = 0;
  transfer.bits_per_word = bits_per_word;
  transfer.cs_change = 0;
  if (ioctl(spidev_fd, SPI_IOC_MESSAGE(1), &transfer) < 0) return -1;
 return (n_bytes<<3) / bits_per_word;
}

int SPI_transaction(int spidev_fd, void *tx_buffer, int n_tx_words,
                    void *rx_buffer, int n_rx_words) {
  uint8_t bits_per_word;
  uint32_t n_tx_bytes, n_rx_bytes;
  struct spi_ioc_transfer transfers[2];
  int n_transfers;
  bits_per_word = SPI_getBitsPerWord(spidev_fd);
  if (bits_per_word < 0) return bits_per_word;
  // Round up to the next biggest number of bytes:
  n_tx_bytes = (uint32_t) (((float) (bits_per_word * n_tx_words)) / 8.0 + 0.5);
  n_rx_bytes = (uint32_t) (((float) (bits_per_word * n_rx_words)) / 8.0 + 0.5);
  if (!n_rx_bytes && !n_tx_bytes) return 0;
  if (n_rx_bytes > MAX_TRANSFER_SIZE) n_rx_bytes = MAX_TRANSFER_SIZE;
  if (n_tx_bytes > MAX_TRANSFER_SIZE) n_tx_bytes = MAX_TRANSFER_SIZE;


n_transfers = 0;
  if (n_tx_bytes) {
      memset((void *) &transfers[n_transfers], 0,
             sizeof(struct spi_ioc_transfer));

      transfers[n_transfers].tx_buf = (uintptr_t) tx_buffer;
      transfers[n_transfers].rx_buf = 0;
      transfers[n_transfers].len = n_tx_bytes;
      transfers[n_transfers].speed_hz = 0;
      transfers[n_transfers].delay_usecs = 0;
      transfers[n_transfers].bits_per_word = bits_per_word;
      transfers[n_transfers].cs_change = 0;

      ++n_transfers;
  }

  if (n_rx_bytes) {
      memset((void *) &transfers[n_transfers], 0,
             sizeof(struct spi_ioc_transfer));

      transfers[n_transfers].tx_buf = 0;
      transfers[n_transfers].rx_buf = (uintptr_t) rx_buffer;
transfers[n_transfers].len = n_rx_bytes + 1;
      transfers[n_transfers].speed_hz = 0;
      transfers[n_transfers].delay_usecs = 0;
      transfers[n_transfers].bits_per_word = bits_per_word;
      transfers[n_transfers].cs_change = 0;

      ++n_transfers;
  }
}
int SPI_transfer(int spidev_fd, void *tx_buffer, void *rx_buffer, int n_words) {
  uint8_t bits_per_word;
  uint32_t n_bytes;
  struct spi_ioc_transfer transfer;
  bits_per_word = SPI_getBitsPerWord(spidev_fd);
  if (bits_per_word < 0) return bits_per_word;
  n_bytes = (uint32_t) (((float) (bits_per_word * n_words)) / 8.0 + 0.5);
  if (!n_bytes) return 0;
  if (n_bytes > MAX_TRANSFER_SIZE) n_bytes = MAX_TRANSFER_SIZE;

  memset((void *) &transfer, 0, sizeof(struct spi_ioc_transfer));
  transfer.tx_buf = (uintptr_t) tx_buffer;
  transfer.rx_buf = (uintptr_t) rx_buffer;
  transfer.len = n_bytes;
  transfer.speed_hz = 0;
  transfer.delay_usecs = 0;
  transfer.bits_per_word = bits_per_word;
  transfer.cs_change = 0;
  if (ioctl(spidev_fd, SPI_IOC_MESSAGE(1), &transfer) < 0) return -1;
  return (n_bytes<<3) / bits_per_word;
}

int SPI_setBitOrder(int spidev_fd, SPI_bit_order bit_order) {
  uint8_t order = (uint8_t) bit_order; // Just to be safe
  if (ioctl(spidev_fd, SPI_IOC_WR_LSB_FIRST, &order) < 0) return -1;
  return 0;
}
int SPI_setBitOrder(int spidev_fd, SPI_bit_order bit_order) {
  uint8_t order = (uint8_t) bit_order; // Just to be safe
  if (ioctl(spidev_fd, SPI_IOC_WR_LSB_FIRST, &order) < 0) return -1;
  return 0;
}

int SPI_setBitsPerWord(int spidev_fd, uint8_t bits_per_word) {
  if (ioctl(spidev_fd, SPI_IOC_WR_BITS_PER_WORD, &bits_per_word) < 0) {
    return -1;

}
}
int SPI_setMaxFrequency(int spidev_fd, uint32_t frequency) {
  if (ioctl(spidev_fd, SPI_IOC_WR_MAX_SPEED_HZ, &frequency) < 0) return -1;
  return 0;
}
int SPI_getBitsPerWord(int spidev_fd) {
  uint8_t bits_per_word;
  if (ioctl(spidev_fd, SPI_IOC_RD_BITS_PER_WORD, &bits_per_word) < 0) {
    return -1;
  }
  return bits_per_word == 0 ? 8 : bits_per_word;
}

int SPI_getMaxFrequency(int spidev_fd) {
  uint32_t frequency;
  if (ioctl(spidev_fd, SPI_IOC_RD_MAX_SPEED_HZ, &frequency) < 0) return -1;
  return frequency;
}

int SPI_setClockMode(int spidev_fd, uint8_t clock_mode) {
  uint8_t mode;
  mode = SPI_getMode(spidev_fd);
  if (mode < 0) return mode;
  mode &= ~0x3;
  mode |= clock_mode & 0x3;
  return SPI_setMode(spidev_fd, mode);
}

int SPI_getClockMode(int spidev_fd) {
  uint8_t clock_mode;
  clock_mode = SPI_getMode(spidev_fd);
  if (clock_mode < 0) return clock_mode;
  return clock_mode & 0x3;
}

int SPI_setCSActiveLow(int spidev_fd) {
  int mode = SPI_getMode(spidev_fd);
  if (mode < 0) return -1;
  return SPI_setMode(spidev_fd, mode & ~SPI_CS_HIGH);
}

int SPI_setCSActiveHigh(int spidev_fd) {
  int mode = SPI_getMode(spidev_fd);
  if (mode < 0) return -1;
  return SPI_setMode(spidev_fd, mode | SPI_CS_HIGH);
}
int SPI_enableCS(int spidev_fd) {
  int mode = SPI_getMode(spidev_fd);
  if (mode < 0) return -1;
  return SPI_setMode(spidev_fd, mode & ~SPI_NO_CS);
}

int SPI_disableCS(int spidev_fd) {
  int mode = SPI_getMode(spidev_fd);
  if (mode < 0) return -1;
  return SPI_setMode(spidev_fd, mode | SPI_NO_CS);
}
int SPI_enableLoopback(int spidev_fd) {
  int mode = SPI_getMode(spidev_fd);
  if (mode < 0) return -1;
  return SPI_setMode(spidev_fd, mode | SPI_LOOP);
}

int SPI_disableLoopback(int spidev_fd) {
  int mode = SPI_getMode(spidev_fd);
  if (mode < 0) return -1;
  return SPI_setMode(spidev_fd, mode & ~SPI_LOOP);
}

int SPI_enable3Wire(int spidev_fd) {
  int mode = SPI_getMode(spidev_fd);
  if (mode < 0) return -1;
  return SPI_setMode(spidev_fd, mode | SPI_3WIRE);
}

int SPI_disable3Wire(int spidev_fd) {
  int mode = SPI_getMode(spidev_fd);
  if (mode < 0) return -1;
  return SPI_setMode(spidev_fd, mode & ~SPI_3WIRE);
}
int SPI_getMode(int spidev_fd) {
  uint8_t mode;
  if (ioctl(spidev_fd, SPI_IOC_RD_MODE, &mode) < 0) return -1;
  return mode;
}

int main(){

//      uint16_t spi_fd;
        spi_fd = SPI_open(1,0);

        uint8_t read_config, read_RF_setup, read_RF_channel;

        SPI_setMaxFrequency(spi_fd,1000000);
        SPI_setClockMode(spi_fd,0);
        SPI_enable3Wire(spi_fd);
        SPI_setBitOrder(spi_fd,0);
        SPI_setBitsPerWord(spi_fd,8);

        uint8_t port = 117;
        uint8_t A[]= {0x01,0x02,0x03,0x4,0x5};
        nrf_write_config(spi_fd, port);
        read_config = nrf_read_config(spi_fd, port);

        printf("read_config = %x   \n", read_config);

        nrf_write_RF_setup(spi_fd, port);

        read_RF_setup= nrf_read_RF_setup(spi_fd, port);

        printf("read_RF_config = %x   \n", read_RF_setup);


        nrf_write_RF_channel(spi_fd, port);
        read_RF_channel= nrf_read_RF_channel(spi_fd, port);

        printf("read_RF_channel = %x   \n", read_RF_channel);

        nrf_write_TXADDR(spi_fd, port);
        nrf_read_TXADDR(spi_fd, port);

        //for (int i=0;i<5;i++){
 //printf("value= %x \n",read_status[i]);

        //}
}

