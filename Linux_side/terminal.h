/**
*	@file 			terminal.h
*	@brief 		
*	
*	@param  	
*	
*	@author 		
*	@date 			Feb 18 2019 
*	@version  	1.0
*/

#ifndef  __TERMINAL__
#define __TERMINAL__
#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include "common.h"
struct termios orig_termios;


void reset_terminal_mode();
void set_conio_terminal_mode();
int kbhit();
int getch();

#endif