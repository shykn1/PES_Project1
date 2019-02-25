/**
*	@file 			terminal.c
*	@brief 		
*	
*	@param  	
*	
*	@author 		
*	@date 			Feb 18 2019 
*	@version  	1.0
*/

#include "terminal.h"


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