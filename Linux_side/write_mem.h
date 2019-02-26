/**
*	@file 			write_mem.h
*	@brief 		A function to write a memory into the specific absolute address provided by users
*	
*	@param 		param_input				buffer for parameters provided by users
*   
*	@author 		
*	@date 			Feb 24 2019 
*	@version  	1.0
*/

#ifndef  __WRITE__
#define __WRITE__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

/**
*	@brief 		Check the parameters provided by users 
*	
*	@param 		param_input		buffer for parameters provided by users
*
*	@return 		res
*	-value = 0		ERROR (invalid parameters)
*	-value = 1		SUCCESS (write data with absolute address)
*	-value = 2		SUCCESS (write data with block and offset)
*/

INT8_t check_param_write_mem(const param* param_input);


/**
*	@brief 		Write data into the specific absolute address provided by users
*	
*	@param 		param_input				buffer for parameters provided by users
*	If (param_input->param3 == "DASHA")
*	- param_input->param1			Absolute address
*	- param_input->param2			data in HEX	
*	
* 	else
*	- param_input->param1			Index of the block
*	- param_input->param2			offset to specific address in this block
*	- param_input->param3			data in HEX	
*	
*	@return void
*/
void write_mem(param* param_input);
void print_data(UINT32_t* base,UINT32_t range);
#endif