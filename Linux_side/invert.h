#ifndef  __INVERT__
#define __INVERT__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"


INT8_t check_param_invert(const param* param_input);
void invert(param* param_input);
void invert_data(UINT32_t* base,UINT32_t range);

#endif