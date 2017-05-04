/***************************************************************************
file name : nrf.c

Author : Sudeep Kulkarniirlekar
	Jeet Baru

Description : This is the nordic chip configuration, sending and receiving
		the data using spi

****************************************************************************/
#include "nrf.h"

//function to enable the nordic
void nordic_enable(uint8_t port)
{
        //uint8_t A[]= {0x11, 0x12, 0x13, 0x14, 0x15};

	//enabling the gpio117
        FILE *f;
        f = fopen("/sys/class/gpio/export", "w");
        fprintf(f, "%d\n", port);
        fclose(f);

        char file[128];
	//setting the gpio117 out
        sprintf(file, "/sys/class/gpio/gpio%d/direction", port);
        f = fopen(file, "w");
        fprintf(f, "out\n");
        fclose(f);
}
//setting the gpio pin to low before write, read
void nrf_low(uint8_t port)
{	
	//setting the gpio pin to low
        FILE *IO_Value;
        char file1[128];
        sprintf(file1, "/sys/class/gpio/gpio%d/value", port);
        IO_Value = fopen(file1, "w");
	//setting the value of the gpio to '0'
        fprintf(IO_Value, "0\n");
        fclose(IO_Value);

}
//setting the gpio pin high after write, read
void nrf_high(uint8_t port)

{
        FILE *IO_Value1;
        char file2[128];
        sprintf(file2, "/sys/class/gpio/gpio%d/value", port);
        IO_Value1 = fopen(file2, "w");
	//setting value of IO to '1'
        fprintf(IO_Value1, "1\n");
        fclose(IO_Value1);


}
//writing to the config register
void nrf_write_config(uint16_t spi_d, uint8_t port)
{
	
        nordic_enable(117);                                   //enabling the nordic

        uint8_t reg= (0x20|0x00);
        uint8_t value = 0x03;

        nrf_low(117);						//setting the gpio pin to low CSN
	//sending the write command
        write(spi_fd,&reg,sizeof(reg)/sizeof(uint8_t));
        write(spi_fd,&value,1);

        nrf_high(117);
}
//reading the status of the confing register
uint8_t nrf_read_config(uint16_t spi_d, uint8_t port)
{
        nrf_low(117);
        uint8_t read_config;

        uint8_t nop = NRF_NOP;
        uint8_t reg1 = (NRF_R_REGISTER|0x00);
	//sending the write command
        write(spi_fd,&reg1,sizeof(reg1)/sizeof(uint8_t));
	//sending the nop command        
	write(spi_fd,&nop,sizeof(nop)/sizeof(uint8_t));
        read(spi_fd,&read_config,1);

        return read_config;
        nrf_high(117);
}
//writing to the RF_setup register
void nrf_write_RF_setup(uint16_t spi_d, uint8_t port)
{
        //uint8_t A[]= {0x01,0x02,0x03,0x4,0x5};


        nordic_enable(117);

        //uint8_t read_status[10];

        uint8_t reg= (0x20|0x06);
        uint8_t value = 0x01;

        nrf_low(117);
        write(spi_fd,&reg,sizeof(reg)/sizeof(uint8_t));

        write(spi_fd,&value,1);

        nrf_high(117);
}
//reading the status of RF_setup register
uint8_t nrf_read_RF_setup(uint16_t spi_d, uint8_t port)
{

        nrf_low(117);
        uint8_t read_RF_setup;

        uint8_t nop = NRF_NOP;
        uint8_t reg1 = (0x00|0x06);
        write(spi_fd,&reg1,sizeof(reg1)/sizeof(uint8_t));
        write(spi_fd,&nop,sizeof(nop)/sizeof(uint8_t));
        write(spi_fd,&nop,sizeof(nop)/sizeof(uint8_t));
        write(spi_fd,&nop,sizeof(nop)/sizeof(uint8_t));
        read(spi_fd,&read_RF_setup,1);
        nrf_high(117);

}
//writing to the RF_channel register
void nrf_write_RF_channel(uint16_t spi_fd, uint8_t port)
{
        nordic_enable(117);

        //uint8_t read_status[10];

        uint8_t reg= (0x20|0x05);
        uint8_t value = 0x03;

        nrf_low(117);
	//sending the write command 
        write(spi_fd,&reg,sizeof(reg)/sizeof(uint8_t));
	
        write(spi_fd,&value,1);

        nrf_high(117);
}

//reading the status of the RF_channel
uint8_t nrf_read_RF_channel(uint16_t spi_fd, uint8_t port)
{
        nrf_low(117);

        uint8_t read_RF_channel;

        uint8_t nop = NRF_NOP;

        uint8_t reg1 = (NRF_R_REGISTER|0x05);

        write(spi_fd,&reg1,sizeof(reg1)/sizeof(uint8_t));               //sending the read command
        write(spi_fd,&nop,sizeof(nop)/sizeof(uint8_t));			//sending nop to read the value
        read(spi_fd,&read_RF_channel,1);

        nrf_high(117);
        return read_RF_channel;
}
//writing mulitiple bytes
void nrf_write_TXADDR(uint16_t spi_fd, uint8_t port)
{
        uint8_t A[]= {0x11,0x12,0x13,0x14,0x15};

        nordic_enable(117);		
        //uint8_t read_status[10];

        uint8_t reg= (0x20|0x10);                                    	//sending the write command
        //uint8_t value = 0x03;

        nrf_low(117);
	//sending the write command 
        write(spi_fd,&reg,sizeof(reg)/sizeof(uint8_t));
        write(spi_fd,&A,5);

        nrf_high(117);

}
//reading the multiple values  
void nrf_read_TXADDR(uint16_t spi_fd, uint8_t port)
{

        nrf_low(117);

        uint8_t read_status[10];

	
        uint8_t nop = NRF_NOP;
        uint8_t reg1 = (NRF_R_REGISTER|0x10);				//sending the read command

	//sending the nops for reading the values
        write(spi_fd,&reg1,sizeof(reg1)/sizeof(uint8_t));
        write(spi_fd,&nop,sizeof(nop)/sizeof(uint8_t));
        write(spi_fd,&nop,sizeof(nop)/sizeof(uint8_t));
        write(spi_fd,&nop,sizeof(nop)/sizeof(uint8_t));
        write(spi_fd,&nop,sizeof(nop)/sizeof(uint8_t));
        write(spi_fd,&nop,sizeof(nop)/sizeof(uint8_t));
        write(spi_fd,&nop,sizeof(nop)/sizeof(uint8_t));
        write(spi_fd,&nop,sizeof(nop)/sizeof(uint8_t));
        write(spi_fd,&nop,sizeof(nop)/sizeof(uint8_t));
        read(spi_fd,&read_status,5);

        nrf_high(117);

        for (int i=0;i<5;i++){

        printf("value= %x \n",read_status[i]);

        }

}



