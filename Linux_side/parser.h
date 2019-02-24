#ifndef  __PARSER__
#define __PARSER__
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "common.h"






INT8_t command_check(UINT64_t command);
INT8_t params_check(char* params_char);
INT8_t parser(char* input_command_string, struct param* output);


#endif
