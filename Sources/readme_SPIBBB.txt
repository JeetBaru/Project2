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

This file cosists of function that deal with receiving command decoding it and validating the cammand. The command is recieved in the order of CommandID
Data length, data values and 2 digits of checksum. This is done by calling UART receive functions. On receiving the cammand we check for its validity.
For checking validity we include a checksum in the command. Our checksum checks for the sum of all elements and if checksum matches the sum we say the cammand entered is valid.
Finally if valid command is received we decode the command, depending on the command ID. This function also calls the respective LED function.  


************************LED.c*********************************
This file consists functions that configure LEDs to specific brightness. This is done by writing the brightness value to the max count value of the respective counter.
Also this file has functions that turn the LEDs on and off by writing 0 and MAX values to the registers. Also we have a function that lights the LEDs to specific
colors depending on the user input. This is done by selecting combinations of the LEDs.

*********************************PWM.c****************************
This file consists functions to initialize LEDs to their respective timer channels. A final PWM init function calls init for each LEDs.
THe brightness of each LED can be changed by writing to its max count value. 
