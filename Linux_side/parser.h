#ifndef  __PARSER__
#define __PARSER__
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

typedef unsigned long int UINT64_t;
typedef unsigned int UINT32_t;
typedef char INT8_t  ;

struct param
{
	UINT64_t param1;
	UINT64_t param2;
	UINT64_t param3;
	UINT64_t param4;  
	UINT64_t param5;
}output;



INT8_t command_check(UINT64_t command);
INT8_t params_check(char* params_char);
INT8_t parser(char* input_command_string, struct param* output);

#endif
