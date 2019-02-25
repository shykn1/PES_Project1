#ifndef  __COMMON__
#define __COMMON__

#define MAX_BLOCK 100

#define PRINTF  \
for(int p=0;p<uart_num;p++){\
	printf("%c",uplink_buffer[p]);\
}


typedef struct param param; 
typedef unsigned long int UINT64_t;
typedef unsigned int UINT32_t;
typedef char INT8_t ;

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


#endif