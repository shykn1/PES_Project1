/**
*	@file 			parser.h
*	@brief 		A parser to convert string command to command and parameters
*	
*	@author 		Tim Chien
*	@date 			Feb 18 2019 
*	@version  	1.0
*/
#ifndef  __PARSER__
#define __PARSER__
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "common.h"



/**
*	@brief 		Check the command is valid or not
*	
*	@param 		command		parameter string
*	
*	@return 		ret
*	-value = 0		SUCCESS (valid command)
*	-value = -1		ERROR (command not found)
*/
INT8_t command_check(UINT64_t command);

/**
*	@brief 		Check the parameter is valid or not
*	
*	@param 		param_char	parameter string
*
*	@return 		ret
*	-value = 0		SUCCESS (valid parameter)
*	-value = -2		ERROR (invlid parameter)
*/
INT8_t params_check(char* params_char);

/**
*	@brief 		Convert string command to command and parameters
*	
*	@param  	input_command_string		string command users input
*	@param		output								struct buffer for command and parameters
*	
*	@return 		void.
*/
INT8_t parser(char* input_command_string, struct param* output);


#endif
