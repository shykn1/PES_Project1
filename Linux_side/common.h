/**
*	@file 			common.h
*	@brief 		Some common functions for this project
*	
*
*	@author 		
*	@date 			Feb 18 2019 
*	@version  	1.0
*/
#ifndef  __COMMON__
#define __COMMON__
#include <time.h>
#define MAX_BLOCK (100)
#define MAX_SIZE (0xffffffff)
#define MAX_U32 (0xffffffff)
#define DASHA ((UINT64_t)(0-1))
#define NSEC_PER_SEC (1000000000)
#define NSEC_PER_MSEC (1000000)
#define NSEC_PER_MICROSEC (1000)


#define PRINTF  \
for(int p=0;p<uart_num;p++){\
	printf("%c",uplink_buffer[p]);\
}


typedef struct param param; 
typedef unsigned long int UINT64_t;
typedef unsigned int UINT32_t;
typedef char INT8_t ;
typedef unsigned char UINT8_t ;

typedef struct{
	UINT32_t* mem_ptr;
	UINT32_t range;
	INT8_t obsolete;
}mem_array;

struct param
{
	UINT64_t param1;
	UINT64_t param2;
	UINT64_t param3;
	UINT64_t param4;  
	UINT64_t param5;
}output;

void (*evt_ptr)(param*);
mem_array mem[MAX_BLOCK];
UINT32_t uart_num;
char uplink_buffer[255];

 
/**
*	@brief 		Check the memory is full or not
*	
*	@param 		addr		parameter string
*	
*	@return 		
*	-	 0				ERROR		(number of block is reach the maximum value)
*	-	-1				SUCCESS  	(memory is allocated)
*/
INT8_t check_addr(UINT64_t addr);

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
INT8_t check_blk(UINT32_t blk_index, UINT32_t offset);
void print_data(UINT32_t* base,UINT32_t range);
INT8_t align_addr_check(UINT64_t addr);
int delta_t(struct timespec *stop, struct timespec *start, struct timespec *delta_t);
#endif