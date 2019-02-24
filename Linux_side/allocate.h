#ifndef  __ALLOCATE__
#define __ALLOCATE__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

#define MAX_SIZE 0xffffffff
INT8_t check_param_allocate(const param* param_input);
void allocate(param* param_input);
#endif