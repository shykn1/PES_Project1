/**
*	@file 			pes1.c
*	@brief 		A function to trigger specific event with the command index provided by parser.c
*	
*	@author 		
*	@date 			Feb 18 2019 
*	@version  	1.0
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "terminal.h"
#include "parser.h"
#include "allocate.h"
#include "free_mem.h"
#include "display.h"
#include "write_mem.h"
#include "invert.h"
#include "PRG.h"
#include "pattern_check.h"


/**
*	@brief 		Printf the information for users while program starting
*	
*	@return   	void.
*/
void inital_message(){
	printf("Press command starting with a \"C\": C0 means command 0 and C1 means command 1\r\n");
	printf("Command 0: help; Command 1:exit\r\n");
	printf("To find More detail, use help\r\n");
	
};


/**
*	@brief 		Printf the information for users while receiving C0 
*	
*	@return   	void.
*/
void help_message(){
	uart_num=sprintf(uplink_buffer,"Command 0: help; Command 1:exit\r\n");PRINTF;
	uart_num=sprintf(uplink_buffer,"To allocate a block: C2 <N of words in Hex>\r\n");PRINTF;
	uart_num=sprintf(uplink_buffer,"To free a block: C3 <index of the block>\r\n");PRINTF;
	uart_num=sprintf(uplink_buffer,"To display a range of memory with block and offset: C4 <index of the block> <offset> <range in terms of words(4-byte)>\r\n");PRINTF;
	uart_num=sprintf(uplink_buffer,"To display a range of memory with absolute address: C4 <addr> <range in terms of words(4-byte)> -a\r\n");PRINTF;
	uart_num=sprintf(uplink_buffer,"To write an location with block and offset: C5 <index of the block> <offset> <data in HEX>\r\n");PRINTF;
	uart_num=sprintf(uplink_buffer,"To write an location with absolute address: C5 <addr> <data in HEX> -a\r\n");PRINTF;
	uart_num=sprintf(uplink_buffer,"To invert a range of memory with block and offset: C6 <index of the block> <offset> <range in terms of words(4-byte)>\r\n");PRINTF;
	uart_num=sprintf(uplink_buffer,"To invert a range of memory with absolute address: C6 <addr> <range in terms of words(4-byte)> -a\r\n");PRINTF;
	uart_num=sprintf(uplink_buffer,"Current blocks status:\r\n");PRINTF;
	UINT8_t flag_displayed =0;
	for(UINT8_t i=0;i<MAX_BLOCK;i++){
		if(mem[i].obsolete == 1){
			uart_num=sprintf(uplink_buffer,"block%d, capacity:0x%x words (0x%x bytes), address: %p\n\r",i,mem[i].range,mem[i].range*4,mem[i].mem_ptr);PRINTF;
			flag_displayed=1;
		}
	}
	if(flag_displayed==0){
		uart_num=sprintf(uplink_buffer,"no block assigned\n\r");PRINTF;
	}
}

/**
*	@brief 		Check event with the command index provided by parser.c
*	
*	@param		index			command input 
*   - value = 0		Show the help message for all command			
*   - value = 1		End the program
*   - value = 2		Allocate a heap of memory into block		(more detail are in allocate.c)			
*   - value = 3		Free the block memory with block index 	(more detail are in free_mem.c)
*   - value = 4		Display the data in specific address 		(more detail are in display.c)
*   - value = 5		Write the data into specific address 		(more detail are in write_mem.c) 
*   - value = 6		Invert the data in specific address			(more detail are in invert.c) 
*	
*	@return   	void.
*/

INT8_t evt_handler(INT8_t index){
	INT8_t evt_trigger=1;
	evt_ptr =NULL;
	switch(index){
		case 0:
			help_message();
			evt_trigger =0;
			break;
		case 1:
			exit(0);
			break;
		case 2:
			evt_ptr = &allocate;
			break;		
		case 3:
			evt_ptr = &free_mem;
			break;	
		case 4:
			evt_ptr = &display;
			break;	
		case 5:
			evt_ptr = &write_mem;
			break;
		case 6:
			evt_ptr = &invert;
			break;
		case 7:
			evt_ptr = &PRG;
			break;
		case 8:
			evt_ptr = &pattern_check;
			break;
		case -1:
			printf("Command Not defined\r\n");
			evt_trigger =0;
			break;
		default:
			printf("Command Not defined\r\n");
			evt_trigger =0;
			break;
	}
	return evt_trigger;
}

volatile char buffer[255];
volatile unsigned char buffer_ptr;
volatile char command_flag = 0;


/**
*	@brief 		Trigger specific event with the command index provided by parser.c
*	
*	
*	@return void.
*/

int main()
{
	inital_message();
    //set_conio_terminal_mode();
	char c =0;
	int cnt_charactor =0;
	INT8_t command_index;
	buffer_ptr=0;    int time=0;
	while(1){
		while (!kbhit() || command_flag) {   
		/* main loop */
			if(command_flag){
				//printf("%s\r\n",buffer); 
				if(cnt_charactor == 0){
					buffer_ptr =0;
					command_flag = 0;
					buffer[0]=0;
					memset((char *)buffer,0,255);
					break;
				}
				command_index = parser((char* )buffer,&output);
				//printf("error message: %d \n",command_index);
				if( (evt_handler(command_index)) != 0)
					evt_ptr(&output);
				uart_num=sprintf(uplink_buffer,"\n\n\r");PRINTF;
				cnt_charactor =0;
				buffer_ptr =0;
				command_flag = 0;
			}
		}
			/* consume the character(emulate the interrupt on the FRDM) */
			
			c = (char)getch();
			if( (c=='\n')||(c=='\r')){
				command_flag =1;	
				c='\0';
			}
			else
				cnt_charactor++;
			
			
			buffer[buffer_ptr++] =c;

	}
	exit(0);
}
