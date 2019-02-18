#ifndef  __PARSER__
#define __PARSER__
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>



struct param
{
	uint32_t param1;
	uint32_t param2;
	uint32_t param3;
	uint32_t param4;  
	uint32_t param5;
}output;



int8_t command_check(uint32_t command);
int8_t params_check(char* params_char);
int8_t parser(char* input_command_string, struct param* output);

#endif