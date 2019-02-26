/**
*	@file 			allocate.h
*	@brief 		A function to allocate the memory with the size of words provided by users
*
*	@author 		
*	@date 			Feb 24 2019 
*	@version  	1.0
*/

#ifndef  __ALLOCATE__
#define __ALLOCATE__
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
*	-value = 1		SUCCESS
*/
INT8_t check_param_allocate(const param* param_input);

/**
*	@brief 		Allocate the memory with the size of words provided by users
*	
*	@param 		param_input		buffer for parameters provided by users
*	- param_input->param1			number of words need to be allocated (in HEX)
*
*	@return void.
*/
void allocate(param* param_input);
#endif