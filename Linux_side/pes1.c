#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include "terminal.h"
#include "parser.h"


void inital_message(){
	printf("Press command starting with a \"C\": C0 means command 0 and C1 means command 1\r\n");
	printf("Command 0: help; Command 1:exit\r\n");
};

void help_message(){
	printf("Press command starting with a \"C\": C0 means command 0 and C1 means command 1\r\n");
	printf("Command 0: help; Command 1:exit\r\n");
};
void evt_handler(INT8_t index){
	switch(index){
		case 0:
			help_message();
			break;
		case 1:
			exit(0);
			break;
			
		case -1:
			printf("Command Not defined\r\n");
			break;
		default:
			printf("Command Not defined\r\n");
			break;
	}
}

volatile char buffer[255];
volatile unsigned char buffer_ptr;
volatile char command_flag = 0;
int main(int argc, char *argv[])
{
	inital_message();
    set_conio_terminal_mode();
	char c =0;
	int cnt_charactor =0;
	INT8_t command_index;
	buffer_ptr=0;
	/* UINT32_t* test_buffer = malloc(0x100);UINT32_t* test_buffer1 = malloc(100);
	UINT64_t addr = (UINT64_t)test_buffer;
	printf("\n\r%p %p %p",test_buffer,test_buffer1,(UINT32_t* )	addr);
	exit(0); */
	while(1){
		while (!kbhit()) {   
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
				evt_handler(command_index);
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
