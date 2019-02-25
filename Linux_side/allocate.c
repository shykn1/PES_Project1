#include "allocate.h"
INT8_t check_param_allocate(const param* param_input){
		INT8_t res =1;
		if( (param_input->param1 > MAX_SIZE) || (param_input->param1 ==0))
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
void allocate(param* param_input){
	if(!check_param_allocate(param_input))
		return;
	int i=0;
	for(i=0;i<MAX_BLOCK;i++)	{
		if(!mem[i].obsolete){
			uart_num=sprintf(uplink_buffer,"assigned bytes: %ld\n\r",(param_input->param1) *  (sizeof(UINT32_t)) );PRINTF;
			mem[i].mem_ptr = malloc( (param_input->param1) *  (sizeof(UINT32_t)) );
			mem[i].range = (UINT32_t)param_input->param1;
			mem[i].obsolete =1;
			uart_num=sprintf(uplink_buffer,"block %d has been allocated with size of 0x%x; address: %p \n\r",i,mem[i].range,mem[i].mem_ptr );PRINTF;
			break;
		}
	}
	if(i==MAX_BLOCK){
		uart_num=sprintf(uplink_buffer,"reach the limitation of number of blocks");PRINTF;
	}
}