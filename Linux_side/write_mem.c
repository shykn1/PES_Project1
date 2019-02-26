/**
*	@file 			write_mem.c
*	@brief 		A function to write a memory into the specific absolute address provided by users
*	
*	@author 		
*	@date 			Feb 24 2019 
*	@version  	1.0
*/

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

#include "write_mem.h"
INT8_t check_param_write_mem(const param* param_input){
		INT8_t res =3;
		if(param_input->param3 == DASHA){
			res =2;
			if((param_input->param2 > MAX_U32) )
				res=0;
			if(param_input->param4 != 0)
				res=0;
			if(param_input->param5 != 0)
				res=0;
		}
		else{
			res =1;
			if(param_input->param1 > MAX_BLOCK)
				res=0;
			if(param_input->param2 > MAX_SIZE)
				res=0;
			if((param_input->param3 > MAX_U32))
				res=0;
			if(param_input->param4 != 0)
				res=0;
			if(param_input->param5 != 0)
				res=0;
		}	

		if( (res == 1) || (res ==2)){
			uart_num=sprintf(uplink_buffer,"valid parameters\n\r");PRINTF;}		
		else{
			uart_num=sprintf(uplink_buffer,"invalid parameters\n\r");PRINTF;}
		return res;
}

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

void write_mem(param* param_input){
	INT8_t cmd_type = check_param_write_mem(param_input);
	UINT64_t addr;
	UINT32_t index,offset,data;
	if(!cmd_type)
		return;
	int i=0;
	switch (cmd_type){
		case 2:
			addr=param_input->param1;
			data = (UINT32_t)param_input->param2;
			if(check_addr(addr) ){
				*((UINT32_t*)addr) = data;
				print_data((UINT32_t*)addr,1);
			}				
			else{
				uart_num=sprintf(uplink_buffer,"address has not been allocated\n\r");PRINTF;
			}
			break;
		case 1:
			index=(UINT32_t)param_input->param1;
			offset =(UINT32_t)param_input->param2;
			data =(UINT32_t)param_input->param3;
			if(check_blk(index,offset)){
				*((UINT32_t*)mem[index].mem_ptr+offset) = data;
				print_data(mem[index].mem_ptr+offset,1);
			}
			else{
				uart_num=sprintf(uplink_buffer,"the offset exceeds the boundary for this block\n\r");PRINTF;
			}			
			break;
		default:
			break;
	}	
}

