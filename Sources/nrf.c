
#include "MKL25Z4.h"
#include "spi.h"
#include "nrf.h"
#include <stdint.h>
#include "GPIO.h"

uint8_t val=0;

#define RF_CHANNEL 2	// channel 2 is also the default channel
#define PAYLOAD_SIZE 1	// payload size
uint8_t flag=0;

// Function to write a byte to the register
void nrf_write_register(uint8_t register1, uint8_t value){
	NORDIC_CS_ENABLE();
	SPI_write_read_byte(NORDIC_W_REGISTER|register1); //sending the write command
	SPI_write_read_byte(value);	    				  //sending the value
	NORDIC_CS_DISABLE();
}


//Function to read register
uint8_t nrf_read_register(uint8_t register1){
	uint8_t a,b;
	NORDIC_CS_ENABLE();
	a = SPI_write_read_byte(NORDIC_R_REGISTER|register1);
	b = SPI_write_read_byte(NORDIC_NOP);	// to read the value, NOP command or 0xFF has to be sent
	NORDIC_CS_DISABLE();
	return b;
}

//read status is remaining
// Reading the value of the STATUS register by sending NOP command
uint8_t nrf_read_status(){
	uint8_t read_value;
	NORDIC_CS_ENABLE();
	//SPI_write_byte()
	read_value = SPI_write_read_byte(NORDIC_NOP);
	NORDIC_CS_DISABLE();
	return read_value;
}

void nrf_write_config(uint8_t config)
{

	nrf_write_register(NORDIC_CONFIG, config);
}
uint8_t nrf_read_config()
{
	uint8_t status = 0;
	nrf_read_register(NORDIC_CONFIG);
	status = nrf_read_register(NORDIC_NOP);
	return status;

}
void nrf_write_rf_setup(uint8_t config)
{

	nrf_write_register(NORDIC_RF_SETUP, config);
}
uint8_t nrf_read_rf_setup()
{
	uint8_t received_val;


	received_val = nrf_read_register(NORDIC_RF_SETUP);
	return received_val;

}
void nrf_write_rf_ch(uint8_t channel)
{
	//setting the given RF channel no
	nrf_write_register(NORDIC_RF_CH, channel);
}

uint8_t nrf_read_rf_ch()
{
	uint8_t received_ch_val;

	received_ch_val= nrf_read_register(NORDIC_RF_CH);
	return received_ch_val;
}

void nrf_write_TX_ADDR(uint8_t * tx_addr)
{
	uint8_t i,a;
	  NORDIC_CS_ENABLE();    //clearing the ss bit to drive it low
	  SPI_write_read_byte(NORDIC_W_REGISTER|0x10);
	  //const uint8_t TX_ADDR[5] = {0x17, 0x37, 0x27, 0x37, 0x97};
	  for(i=0; i<5; i++) {
		a = *(tx_addr+i);
	    SPI_write_read_byte(a);
	  }
	  NORDIC_CS_DISABLE();	//setting the ss bit high
}

void nrf_read_TX_ADDR(uint8_t * tx_addr)
{
	uint8_t i=0;
		uint8_t val=0;
		NORDIC_CS_ENABLE();

		SPI_write_read_byte(NORDIC_R_REGISTER|0x10);

		*tx_addr= SPI_write_read_byte(NORDIC_NOP);
		tx_addr++;
		*tx_addr = SPI_write_read_byte(NORDIC_NOP);
		tx_addr++;
		*tx_addr = SPI_write_read_byte(NORDIC_NOP);
		tx_addr++;
		*tx_addr = SPI_write_read_byte(NORDIC_NOP);
		tx_addr++;
		*tx_addr = SPI_write_read_byte(NORDIC_NOP);

		NORDIC_CS_DISABLE();	//setting the ss bit high
}

uint8_t nrf_read_fifo_status(){
	uint8_t fifo_status;
	fifo_status = nrf_read_register(NORDIC_FIFO_STATUS);
	return fifo_status;

}
void nrf_flush_tx_fifo(void){
	SPI_write_read_byte(FLUSH_TX);
}


// Function to flush RX
void nrf_flush_rx_fifo(void){
	SPI_write_read_byte(FLUSH_RX);
}
