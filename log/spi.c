
#include "MKL25Z4.h"
#include "spi.h"
#include <stdint.h>
#include "GPIO.h"

//initializing the spi module
void SPI_init(void){

	//Enabling the clock gate for SPI0
	SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;   //0x400000u
	//Gpio_Init();
	//selecting port C for SPI0 and configuring its GPIO pins
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
	PORTC_PCR4 |= PORT_PCR_MUX(1); 			//Select Alternate function 1 (or gpio pin) for SPI0_PCS0 (or SPI SS)
	PORTC_PCR5 |= PORT_PCR_MUX(2);			//Select Alternate function 2 for SPI0_SCK
	PORTC_PCR6 |= PORT_PCR_MUX(2); 			//Select Alternate function 2 for SPI0_MOSI
	PORTC_PCR7 |= PORT_PCR_MUX(2); 			//Select Alternate function 2 for SPI0_MISO
	PORTC_PCR3 |= PORT_PCR_MUX(1);			//For CE pin

		//configuring the ss pin

	//configuring the ss pin
	PTC->PDDR |= 0x10;                      //selecting the ss pin as output (---1 ----)
	PTC->PSOR = 0x10;						//making the ss pin high (or idle, since its active low)

	//Selecting master mode for the SPI on MCU
	SPI0->C1 |= SPI_C1_MSTR_MASK;
	SPI0->C1 &= ~SPI_C1_CPHA_MASK;

	SPI0->C2 = 0x00;

	//setting a baud rate divisor of 4
	SPI0->BR = SPI_BR_SPR(1);

	//enabling the SPI module
	SPI0->C1 |= SPI_C1_SPE_MASK;
}


//function to return status of SPI
uint8_t SPI_status() {
	return SPI0->S;
}


//function to re-initialize the spi module
void SPI_flush()
{
	//disable the SPI module by making SPE=0
	SPI0_C1 &= 0xBF;
	//Call the initialization function
	SPI_init();
}

//transmitting and receiving a byte it includes write, read and send byte function
uint8_t SPI_write_read_byte(uint8_t byte){
	unsigned char temp = 0;

	//waiting for transmit buffer to become empty
	while(!(SPI_status() & 0x20));
	SPI0->D = byte; //writing the character to data register

	//waiting for data to become available in the receive buffer
	while(!(SPI_status() & 0x80));
	temp = SPI0_D;   //clears SPRF

	return temp;
}
//function to write a byte
void SPI_write_byte(uint8_t byte)
{
	while(!(SPI_status() & 0x20));
	SPI0->D = byte; //writing the character to data register
}
//function to read a byte
uint8_t SPI_read_byte(uint8_t byte)
{
	uint8_t temp;
	while(!(SPI_status() & 0x80));
		temp = SPI0_D;   //clears SPRF
	return temp;
}
//function to send the packet
void SPI_send_packet(uint8_t* p, uint8_t length)
{
	uint8_t i=0;
	for(i=0; i<length; i++)
	{
		while(!(SPI_status() & 0x20));
			SPI0->D = *p;
		while(!(SPI_status() & 0x80));
			*p = SPI0_D;   //clears SPRF
		p++;
	}

}




