#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int8_t parser(char* input_command_string, struct param* output);
int8_t command_check(uint32_t command);
int8_t params_check(uint32_t params);

struct param
{
	uint32_t param1;
	uint32_t param2;
	uint32_t param3;
	uint32_t param4;  
	uint32_t param5;
}output;

int8_t command_check(uint32_t  command)
{
    if(command < 192 || command > 197) return -1;
    return 0;
}
int8_t params_check(uint32_t  param)
{
    // not sure how to check
    return 0;
}
int8_t parser(char* input_command_string, struct param* output)
{
	char *space = " ";
	char *c;
	int count = 0;
	int8_t ret = 0;
	uint32_t* addr;
	
//command get
	c = strtok(input_command_string, space);
    addr = &(output->param1);
    *addr = strtol(c, NULL, 16);
    ret = command_check(output->param1);
    //if(ret != 0) return ret;
	printf("command : %d check result : %d\n", output->param1,ret); 
	
//params get	
	while((c = strtok(NULL, space))){  
        addr = &(output->param2)+count;
        *addr  = strtol(c, NULL, 16);
        ret = params_check(*addr);
        //if(ret != 0) return ret;
        printf("param %d check result : %d \n",count+2, ret);
        count ++;
    }	
	printf("param 1 : %x \n", (output->param1));
    printf("param 2 : %x \n", (output->param2));
    printf("param 3 : %x \n", (output->param3));
    printf("param 4 : %x \n", (output->param4));
    printf("param 5 : %x \n", (output->param5));
    
}

int main()
{
    char *command_str;
    char strcom[] = "C8 123f ffff 23b45aaaa asdfa  35256  \0";
    command_str = strcom;
    parser(command_str,&output);
    return 0;
}


