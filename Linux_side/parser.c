/**
*	@file 			parser.c
*	@brief 		A parser to convert string command to command and parameters
*	
*	@param  	input_command_string		string command users input
*	@param		output								struct buffer for command and parameters
*	
*	@author 		Tim Chien
*	@date 			Feb 18 2019 
*	@version  	1.0
*/


#include "parser.h"

INT8_t flag  = 0;
INT8_t command_check(UINT64_t  command)
{
	if(command < 192 || command > 201) return -1;
		return ((INT8_t)command - 192);
}
INT8_t params_check(char* params_char)
{
    INT8_t ret = 0;
	//check the char unit in output->param<x> in order
    for(int i=0;params_char[i]!='\0';i++)
    {
			char chara=params_char[i];
			
		//printf("chara : %c, flag %d  \n",chara,flag);
		
		if( (i==0) && (chara=='-'))
		{
			flag = 1;
		}
		else if( (flag == 1) && (chara == 'a'))
		{	    
			flag = 2;
			ret = 1;
		}
		else if (flag == 2)
		{
			ret = -2;
		}
		else
		{
			if(!((chara =='x')||(chara>='A' && chara<='F')||(chara>='0' && chara<='9')|| (chara>='a' && chara<='f'))) 
				ret = -2;
			if(i > 18 ) 
				ret = -2;
		}	
    }
    return ret;
}
INT8_t parser(char* input_command_string, struct param* output)
{
	output->param1 = 0;
	output->param2 = 0;
	output->param3 = 0;
	output->param4 = 0;
	output->param5 = 0;	
	char *space = " ";
	char *c;
	int count = 0;
	INT8_t ret = 0;
	INT8_t command = 0;
	UINT64_t * addr;
	flag  = 0;
 //command get
    c = strtok(input_command_string, space);
    addr = &(output->param1);
    *addr = strtol(c, NULL, 16);
    command = command_check(output->param1);
    if( (command == -1) || (command == 0)  || (command == 1)) 
    {
        //printf("error message: %d \n",command);
        return command;
    }
	//printf("command : %d check result : %d\n", output->param1,ret); 
	output->param1 = 0;
//params get	
    while((c = strtok(NULL, space))){  
		
        ret = params_check(c);
        addr = &(output->param1)+count;
        *addr  = (UINT64_t)strtol(c, NULL, 16);
        if(ret != 0) 	
        {
            if (ret == 1) 
			{
				*addr = DASHA;
			}
			else 
			{
				//printf("error message: %d \n",ret);
				return ret;
			}
        }
        //printf("param %d check result : %d \n",count+2, ret);
        count ++;
    } 		
/*     printf("param 1 : %lx \n", (output->param1));
    printf("param 2 : %lx \n", (output->param2));
    printf("param 3 : %lx \n", (output->param3));
    printf("param 4 : %lx \n", (output->param4));
    printf("param 5 : %lx \n", (output->param5)); */
    return command;
}

/* int main()
{
    char *command_str;
    char strcom[] = "C4 120f ffff 23b45aaa 35256\0";
    command_str = strcom;
    parser(command_str,&output);
    return 0;
} */
