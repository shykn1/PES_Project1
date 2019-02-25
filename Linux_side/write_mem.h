#ifndef  __WRITE__
#define __WRITE__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"


INT8_t check_param_write_mem(const param* param_input);
void write_mem(param* param_input);
void print_data(UINT32_t* base,UINT32_t range);
#endif