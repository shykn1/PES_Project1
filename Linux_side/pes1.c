#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>
#include "parser.h"

struct termios orig_termios;
/*https://stackoverflow.com/questions/448944/c-non-blocking-keyboard-input*/
void reset_terminal_mode()
{
    tcsetattr(0, TCSANOW, &orig_termios);
}

void set_conio_terminal_mode()
{
    struct termios new_termios;

    /* take two copies - one for now, one for later */
    tcgetattr(0, &orig_termios);
    memcpy(&new_termios, &orig_termios, sizeof(new_termios));

    /* register cleanup handler, and set the new terminal mode */
    atexit(reset_terminal_mode);
    cfmakeraw(&new_termios);
	new_termios.c_iflag  |= ICRNL ;
	new_termios.c_lflag  |= ECHO | ICANON | ECHOE;
	new_termios.c_oflag  |= OPOST;
    tcsetattr(0, TCSANOW, &new_termios);
}

int kbhit()
{
    struct timeval tv = { 0L, 0L };
    fd_set fds;
	char res=0;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    res = select(1, &fds, NULL, NULL, &tv);
	return res;
}

int getch()
{
    int r;
    unsigned char c;
    if ((r = read(0, &c, sizeof(c))) < 0) {
        return r;
    } else {
        return c;
    }
}
void inital_message(){
	printf("Press command starting with a \"C\": C0 means command 0 and C1 means command 1\r\n");
	printf("Command 0: help; Command 1:exit\r\n");
};

void help_message(){
	printf("Press command starting with a \"C\": C0 means command 0 and C1 means command 1\r\n");
	printf("Command 0: help; Command 1:exit\r\n");
};
void evt_handler(){
	switch(output.param1){
		case 0:
			help_message();
			break;
		case 1:
			exit(0);
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
	buffer_ptr=0;
	UINT32_t* test_buffer = malloc(0x100);UINT32_t* test_buffer1 = malloc(100);
	UINT64_t addr = (UINT64_t)test_buffer;
	printf("\n\r%p %p %p",test_buffer,test_buffer1,(UINT32_t* )	addr);
	exit(0);
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
				parser((char* )buffer,&output);
				evt_handler();
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
