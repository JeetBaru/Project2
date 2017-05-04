/*
 * command.h
 *
 *  Created on: Apr 25, 2017
 *      Author: Jeet
 */

#ifndef SOURCES_COMMAND_H_
#define SOURCES_COMMAND_H_

typedef enum{
	LED_ON = 0x30, LED_OFF, BRIGHTNESS_R, BRIGHTNESS_G, BRIGHTNESS_B, BRIGHTNESS_ALL, COLOR, TIMESTAMP, RESET
}cmd;

typedef struct{
	cmd command;
	uint8_t length;
	uint8_t * data;
	uint16_t checksum;
}CI_msg;

CI_msg cmd_msg[5];


/****************************************************************************************************
*get_command
*	description:This Function receives command from user using UART

*	parameters:
		i - number of command which are to be received

*	returns:
			None
*****************************************************************************************************/
uint16_t get_command(uint8_t i);

/****************************************************************************************************
*decode_command
*	description:This Function decodes command received from the user

*	parameters:
		i - number of command which are to be decoded

*	returns:
			None
*****************************************************************************************************/
uint16_t decode_command(uint8_t i);

/****************************************************************************************************
*decode_command
*	description:This Function validates command received from the user using checksum

*	parameters:
		i - number of command which are to be validated

*	returns:
			None
*****************************************************************************************************/
uint16_t validate(uint8_t i);

#endif /* SOURCES_COMMAND_H_ */
