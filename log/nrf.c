
#include "MKL25Z4.h"
#include "spi.h"
#include "nrf.h"
#include <stdint.h>
#include "GPIO.h"

uint8_t val=0;


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

// Reading the value of the STATUS register by sending NOP command
uint8_t nrf_read_status(){
	uint8_t read_value;
	NORDIC_CS_ENABLE();
	//SPI_write_byte()
	read_value = SPI_write_read_byte(NORDIC_NOP);
	NORDIC_CS_DISABLE();
	return read_value;
}
//function to write config
void nrf_write_config(uint8_t config)
{

	nrf_write_register(NORDIC_CONFIG, config);
}
//function to read the config written
uint8_t nrf_read_config()
{
	uint8_t status = 0;
	nrf_read_register(NORDIC_CONFIG);
	status = nrf_read_register(NORDIC_NOP);
	return status;

}
//function to write rf_setup
void nrf_write_rf_setup(uint8_t config)
{

	nrf_write_register(NORDIC_RF_SETUP, config);
}
//function to read the rf_setup
uint8_t nrf_read_rf_setup()
{
	uint8_t received_val;


	received_val = nrf_read_register(NORDIC_RF_SETUP);
	return received_val;

}
//function to write to the channel
void nrf_write_rf_ch(uint8_t channel)
{
	//setting the given RF channel no
	nrf_write_register(NORDIC_RF_CH, channel);
}
//function to read the channel
uint8_t nrf_read_rf_ch()
{
	uint8_t received_ch_val;

	received_ch_val= nrf_read_register(NORDIC_RF_CH);
	return received_ch_val;
}
//function to write 5 bytes
void nrf_write_TX_ADDR(uint8_t * tx_addr)
{
	uint8_t i,a;
	  NORDIC_CS_ENABLE();    //clearing the ss bit to drive it low
	  SPI_write_read_byte(NORDIC_W_REGISTER|0x10);
	  for(i=0; i<5; i++) {
		a = *(tx_addr+i);
	    SPI_write_read_byte(a);
	  }
	  NORDIC_CS_DISABLE();	//setting the ss bit high
}
//function to read the 5 bytes
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
//function that reads the fifo status
uint8_t nrf_read_fifo_status(){
	uint8_t fifo_status;
	fifo_status = nrf_read_register(NORDIC_FIFO_STATUS);
	return fifo_status;

}
//function that flushes the the trasmit fifo
void nrf_flush_tx_fifo(void){
	SPI_write_read_byte(FLUSH_TX);
}


// Function to flush RX fifo
void nrf_flush_rx_fifo(void){
	SPI_write_read_byte(FLUSH_RX);
}
