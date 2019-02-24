
#include "parser.h"

//int8_t parser(char* input_command_string, struct param* output);
//int8_t params_check(uint32_t params);



INT8_t command_check(UINT64_t  command)
{
    if(command < 192 || command > 197) return -1;
    return ((INT8_t)command - 192);
}
INT8_t params_check(char* params_char)
{
    for(int i=0;params_char[i];i++)
    {
        char chara=params_char[i];
	bool flag  = 0;
	if(i==0 && chara==45)
	    flag = 1;
	}
        else if(flag == 1 && chara == 97)
	{
	    flag = 2;
	}
	else if(flag == 2)
	{
	    if( chara == 0) return 1;
	} 	
	else
	{
	    if(chara>102||(chara>70 && chara<97)||(chara>58 && chara<65)||chara<48) return -2;
	    if(i > 7 ) return -2;
	}	
    }
    return 0;
}
INT8_t parser(char* input_command_string, struct param* output)
{
	char *space = " ";
	char *c;
	int count = 0;
	INT8_t ret = 0;
	INT8_t command = 0;
	UINT64_t * addr;
	
//command get
    c = strtok(input_command_string, space);
    addr = &(output->param1);
    *addr = strtol(c, NULL, 16);
    command = command_check(output->param1);
    if(ret != 0) 
    {
        printf("error message: %d \n",ret);
        return ret;
    }
	output->param1 -= 192;
	printf("command : %d check result : %d\n", output->param1,ret); 
	
//params get	
    while((c = strtok(NULL, space))){  
        ret = params_check(c);
        addr = &(output->param1)+count;
        *addr  = strtol(c, NULL, 16);
        if(ret != 0) 
        {
            if (ret == 1) 
	    {
	     *addr = 1;
	    }
	    else 
	    {
		printf("error message: %d \n",ret);
	        return ret;
	    }
        }
        printf("param %d check result : %d \n",count+2, ret);
        count ++;
    }	
    printf("param 1 : %x \n", (output->param1));
    printf("param 2 : %x \n", (output->param2));
    printf("param 3 : %x \n", (output->param3));
    printf("param 4 : %x \n", (output->param4));
    printf("param 5 : %x \n", (output->param5));
    return count;
}

/* int main()
{
    char *command_str;
    char strcom[] = "C4 120f ffff 23b45aaa 35256\0";
    command_str = strcom;
    parser(command_str,&output);
    return 0;
} */
