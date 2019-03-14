/**
*	@file 			invert.c
*	@brief 		A function to invert the data in specific address provided by users
*	
*	@author 		
*	@date 			Feb 24 2019 
*	@version  	1.0
*/



#include "invert.h"


/**
*	@brief 		Check the parameters provided by users 
*	
*	@param 		param_input		buffer for parameters provided by users
*
*	@return 		res
*	-value = 0		ERROR (invalid parameters)
*	-value = 1		SUCCESS (invert data with absolute address)
*	-value = 2		SUCCESS (invert data with block and offset)
*/

INT8_t check_param_invert(const param* param_input){
		INT8_t res =3;
		if(param_input->param3 == DASHA){
			res =2;
			if((param_input->param2 > MAX_SIZE)   || (param_input->param2 == 0)  )
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
			if((param_input->param3 > MAX_SIZE)   || (param_input->param3 == 0) )
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
*	@brief 		Invert the data in specific address provided by users
*	
*	@param 		param_input		buffer for parameters provided by users
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
*	@return void.
*/
void invert(param* param_input){
	INT8_t cmd_type = check_param_invert(param_input);
	UINT64_t addr;
	UINT32_t range,index,offset;
	struct timespec start_time,end_time,delta_time;	
	if(!cmd_type)
		return;
	
	switch (cmd_type){
		case 2:
			addr=param_input->param1;
			range =(UINT32_t)param_input->param2;
			uart_num=sprintf(uplink_buffer,"According to the parameters, try to invert: address starting at %lx, range: 0x%x\n\r",addr,range);PRINTF;
			if(!align_addr_check(addr))
				break;			
			if(!(check_addr(addr) && check_addr( addr+range*sizeof(UINT32_t)-1) )){
				uart_num=sprintf(uplink_buffer,"warning: address range has not been allocated\n\r");PRINTF;
			}
			clock_gettime(CLOCK_REALTIME   , &start_time);
			invert_data((UINT32_t*)addr,range);
			clock_gettime(CLOCK_REALTIME   , &end_time);
			//print_data((UINT32_t*)addr,range);				
			delta_t(&end_time, &start_time, &delta_time);
			printf("Bitwise inversion finished at %ld sec, %ld microsec (%ld nanosec)\n\r", delta_time.tv_sec, (delta_time.tv_nsec / NSEC_PER_MICROSEC), (delta_time.tv_nsec));
			break;
		case 1:
			index=(UINT32_t)param_input->param1;
			offset =(UINT32_t)param_input->param2;
			range =(UINT32_t)param_input->param3;
			uart_num=sprintf(uplink_buffer,"According to the parameters, try to invert: Block%d, offset starting at 0x%x, range: 0x%x\n\r",index,offset,range);PRINTF;
			if(check_blk(index,offset) && check_blk( index,offset+range-1) ){
				clock_gettime(CLOCK_REALTIME   , &start_time);
				invert_data(mem[index].mem_ptr+offset,range);
				clock_gettime(CLOCK_REALTIME   , &end_time);
				//print_data(mem[index].mem_ptr+offset,range);		
				delta_t(&end_time, &start_time, &delta_time);
				printf("Bitwise inversion finished at %ld sec, %ld microsec (%ld nanosec)\n\r", delta_time.tv_sec, (delta_time.tv_nsec / NSEC_PER_MICROSEC), (delta_time.tv_nsec));				
			}
			else{
				uart_num=sprintf(uplink_buffer,"the range exceeds the boundary for this set of block and offset\n\r");PRINTF;
			}			
			break;
		default:
			break;
	}	
}

void invert_data(UINT32_t* base,UINT32_t range){
	UINT32_t i;
	UINT8_t* base_u8 = (UINT8_t*)base;
	for(i=0;i<range*4;i++){
		*(base_u8+i) = ~ (*(base_u8+i));
	}
}
