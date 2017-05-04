#include "nrf.h"

void nordic_enable(uint8_t port)
{
        //uint8_t A[]= {0x11, 0x12, 0x13, 0x14, 0x15};
        FILE *f;
        f = fopen("/sys/class/gpio/export", "w");
        fprintf(f, "%d\n", port);
        fclose(f);

        char file[128];
        sprintf(file, "/sys/class/gpio/gpio%d/direction", port);
        f = fopen(file, "w");
        fprintf(f, "out\n");
        fclose(f);
}

void nrf_low(uint8_t port)
{
        FILE *IO_Value;
        char file1[128];
        sprintf(file1, "/sys/class/gpio/gpio%d/value", port);
        IO_Value = fopen(file1, "w");
        fprintf(IO_Value, "0\n");
        fclose(IO_Value);

}

void nrf_high(uint8_t port)

{
        FILE *IO_Value1;
        char file2[128];
        sprintf(file2, "/sys/class/gpio/gpio%d/value", port);
        IO_Value1 = fopen(file2, "w");
        fprintf(IO_Value1, "1\n");
        fclose(IO_Value1);


}

void nrf_write_config(uint16_t spi_d, uint8_t port)
{

        nordic_enable(117);

        uint8_t reg= (0x20|0x00);
        uint8_t value = 0x03;

        nrf_low(117);

        write(spi_fd,&reg,sizeof(reg)/sizeof(uint8_t));
        write(spi_fd,&value,1);

        nrf_high(117);
}

uint8_t nrf_read_config(uint16_t spi_d, uint8_t port)
{
        nrf_low(117);
        uint8_t read_config;

        uint8_t nop = NRF_NOP;
        uint8_t reg1 = (NRF_R_REGISTER|0x00);
        write(spi_fd,&reg1,sizeof(reg1)/sizeof(uint8_t));
        write(spi_fd,&nop,sizeof(nop)/sizeof(uint8_t));
        read(spi_fd,&read_config,1);

        return read_config;
        nrf_high(117);
}

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
void nrf_write_RF_channel(uint16_t spi_fd, uint8_t port)
{
        nordic_enable(117);

        //uint8_t read_status[10];

        uint8_t reg= (0x20|0x05);
        uint8_t value = 0x03;

        nrf_low(117);

        write(spi_fd,&reg,sizeof(reg)/sizeof(uint8_t));
        write(spi_fd,&value,1);

        nrf_high(117);
}


uint8_t nrf_read_RF_channel(uint16_t spi_fd, uint8_t port)
{
        nrf_low(117);



        uint8_t read_RF_channel;

        uint8_t nop = NRF_NOP;
        uint8_t reg1 = (NRF_R_REGISTER|0x05);
        write(spi_fd,&reg1,sizeof(reg1)/sizeof(uint8_t));
        write(spi_fd,&nop,sizeof(nop)/sizeof(uint8_t));
        read(spi_fd,&read_RF_channel,1);

        nrf_high(117);
        return read_RF_channel;
}
void nrf_write_TXADDR(uint16_t spi_fd, uint8_t port)
{
        uint8_t A[]= {0x11,0x12,0x13,0x14,0x15};

        nordic_enable(117);
        //uint8_t read_status[10];

        uint8_t reg= (0x20|0x10);
        //uint8_t value = 0x03;

        nrf_low(117);

        write(spi_fd,&reg,sizeof(reg)/sizeof(uint8_t));
        write(spi_fd,&A,5);

        nrf_high(117);

}

void nrf_read_TXADDR(uint16_t spi_fd, uint8_t port)

{

        nrf_low(117);

        uint8_t read_status[10];

        uint8_t nop = NRF_NOP;
        uint8_t reg1 = (NRF_R_REGISTER|0x10);
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



