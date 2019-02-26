/**
*	@file 			common.c
*	@brief 		Some common functions for this project
*
*	@author 		
*	@date 			Feb 18 2019 
*	@version  	1.0
*/

#include "common.h"
#include <stdlib.h>
#include <stdio.h>
 
/**
*	@brief 		Check the memory is full or not
*	
*	@param 		addr		parameter string
*	
*	@return 		
*	-	 0				ERROR		(number of block is reach the maximum value)
*	-	-1				SUCCESS  	(memory is allocated)
*/
INT8_t check_addr(UINT64_t addr){
	UINT64_t start_addr, end_addr;
	int i=0;
	for(i=0;i<MAX_BLOCK;i++){
		if(mem[i].obsolete == 0)
			continue;
		start_addr =(UINT64_t)mem[i].mem_ptr;
		end_addr = start_addr+ mem[i].range*sizeof(UINT32_t);
		if((addr>=start_addr)&&(addr<end_addr))
			return 1;
	}
	if(i==MAX_BLOCK){
		//uart_num=sprintf(uplink_buffer,"address has not been allocated\n\r");PRINTF;
		return 0;
	}
}

/**
*	@brief 		Check the memory is full or not
*	
*	@param 		blk_index		index of block has been allocated
*	@param 		offset 			index of address in the block
*	
*	@return 		res	
*	-	 0				ERROR		(offset value out of range |  block index is invalid)
*	-	-1				SUCCESS  	
*/
INT8_t check_blk(UINT32_t blk_index, UINT32_t offset){
	INT8_t res =1;
	UINT32_t range_test = mem[blk_index].range;
	if(mem[blk_index].obsolete == 0)
		res =0;
	if(offset>=range_test)
		res =0;
	return res;
}

void print_data(UINT32_t* base,UINT32_t range){
	UINT32_t i;
	for(i=0;i<range;i++){
		uart_num=sprintf(uplink_buffer,"ADDR %16p: 0x%-8x\n\r",base+i,*(base+i));PRINTF;
	}
}


int delta_t(struct timespec *stop, struct timespec *start, struct timespec *delta_t)
{
  int dt_sec=stop->tv_sec - start->tv_sec;
  int dt_nsec=stop->tv_nsec - start->tv_nsec;

  if(dt_sec >= 0)
  {
    if(dt_nsec >= 0)
    {
      delta_t->tv_sec=dt_sec;
      delta_t->tv_nsec=dt_nsec;
    }
    else
    {
      delta_t->tv_sec=dt_sec-1;
      delta_t->tv_nsec=NSEC_PER_SEC+dt_nsec;
    }
  }
  else
  {
    if(dt_nsec >= 0)
    {
      delta_t->tv_sec=dt_sec;
      delta_t->tv_nsec=dt_nsec;
    }
    else
    {
      delta_t->tv_sec=dt_sec-1;
      delta_t->tv_nsec=NSEC_PER_SEC+dt_nsec;
    }
  }

  return(1);
}