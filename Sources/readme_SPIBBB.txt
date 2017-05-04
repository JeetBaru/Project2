The beaglebone is configured for the spi and made connections accordingly with the nordic chip for transmit and receive. The repo was cloned into BBB and the HDMI was disabled by giving the command as instructed. Then by executing the ping test due to the Radio function gpio is exported in /sys/class/gpio/

The same gpio was used to configure for the interface.

***************************** spi_d.c **************************

This source file has the nrf.h included. We are using predefined library unistd, ioctl, types, spidev. The write and read functions used in the main () are derived from the ioctl library. 

The SPI functions defined are written by taking reference from online source. The SPI_setMaxFrequency(), setClockMode(), enable3wire(), setBitOrder(), setBitsPerWord() are intilised to setup the configuration. 

The direction is set to out for the gpio 117 after exporting it and the pin is set to low before every write command and high after every read command.

The status of read_Config register, RF_setup register, RF_channel register is read and the screenshot of the same is pasted in the document.

The TXADDR register is written with multiple bytes and the same values are then read by read commands.


****************************nrf.c***************************

The nordic_enable() function sets the direction and exporting of the gpio pin. the nrf_low(), nrf_high(), are written for setting the gpio pin to zero and low before and after the read and writes.

The functions nrf_write() and nrf_read() for different registers are written and the values are checked for the correct operation, if are getting received correctly after sending.

***************************nrf.h*********************************

All the macros for different registers are included in the library and the function prototypes of all the functions used in source file is included with the proper include guard.


*************************command.c********************************



*************************command.h********************************
Getting the command from the user then decoding and validation is done in the library file of command. The proper include guards and the function definition are included in the library


*************************profiler.h********************************
The start timer stop timer, difference, overflow are defined in the library files and the, This library has the functios which configure and implement the timer. And has function to disable the irq and incrementing the overflow flag and then clearing, with proper include guards

************************profiler.c*********************************
