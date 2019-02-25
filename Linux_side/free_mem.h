/**
*	@file 			free_mem.h
*	@brief 		A function to free the memory in specific block provided by users
*	
*	@param 		param_input				buffer for parameters provided by users
*   
*	- param_input->param1			Index of the block
*	
*	@author 		
*	@date 			Feb 24 2019 
*	@version  	1.0
*/
#ifndef  __FREE__
#define __FREE__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"


INT8_t check_param_free(const param* param_input);
void free_mem(param* param_input);
#endif