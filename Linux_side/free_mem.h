#ifndef  __FREE__
#define __FREE__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"


INT8_t check_param_free(const param* param_input);
void free_mem(param* param_input);
#endif