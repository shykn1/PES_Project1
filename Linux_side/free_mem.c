/**
*	@file 			free_mem.c
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

#include "free_mem.h"
INT8_t check_param_free(const param* param_input){
		INT8_t res =1;
		if(param_input->param1 > MAX_BLOCK)
			res=0;
		if(param_input->param2 != 0)
			res=0;
		if(param_input->param3 != 0)
			res=0;
		if(param_input->param4 != 0)
			res=0;
		if(param_input->param5 != 0)
			res=0;

		if(res){
			uart_num=sprintf(uplink_buffer,"valid parameters\n\r");PRINTF;}		
		else{
			uart_num=sprintf(uplink_buffer,"invalid parameters\n\r");PRINTF;}
		return res;
}
void free_mem(param* param_input){
	if(!check_param_free(param_input))
		return;
	UINT64_t index=param_input->param1;
	if( (mem[index].obsolete == 0) || (mem[index].mem_ptr ==NULL)){
		uart_num=sprintf(uplink_buffer,"block%d has not been allocated, free failed.\n\r",(UINT32_t)index);PRINTF;
	}
	else{
		free((void*)mem[index].mem_ptr);
		mem[index].obsolete =0;
		uart_num=sprintf(uplink_buffer,"block%d has been free.\n\r",(UINT32_t)index);PRINTF;
	}
	
}