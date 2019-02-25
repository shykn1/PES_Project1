/**
*	@file 			display.h
*	@brief 		A function to display the data in specific address provided by users
*	
*	@param 		param_input				buffer for parameters provided by users
*   
*	If (param_input->param3 == "DASHA")
*	- param_input->param1			Absolute address
*	- param_input->param2			The range in term of words(4-byte)
*	
* 	else
*	- param_input->param1			Index of the block
*	- param_input->param2			Offset to specific address in this block
*	- param_input->param3			The range in term of words(4-byte)	
*	
*	@author 		
*	@date 			Feb 24 2019 
*	@version  	1.0
*/
#ifndef  __DISPLAY__
#define __DISPLAY__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"


INT8_t check_param_display(const param* param_input);
void display(param* param_input);
#endif