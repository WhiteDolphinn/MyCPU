#include <string.h>
#include <stdlib.h>
#include "text.h"
#include "my_assembler.h"

#define GET_CMD_CODE(COMMAND, CODE)\
    do{\
        if(!stricmp(COMMAND, TO_STR(PUSH)))\
            CODE = PUSH;\
        if(!stricmp(COMMAND, TO_STR(HLT)))\
            CODE = HLT;\
        if(!stricmp(COMMAND, TO_STR(OUT)))\
            CODE = OUT;\
        if(!stricmp(COMMAND, TO_STR(POP)))\
            CODE = POP;\
        if(!stricmp(COMMAND, TO_STR(ADD)))\
            CODE = ADD;\
        if(!stricmp(COMMAND, TO_STR(SUB)))\
            CODE = SUB;\
        if(!stricmp(COMMAND, TO_STR(MUL)))\
            CODE = MUL;\
        if(!stricmp(COMMAND, TO_STR(DIV)))\
            CODE = DIV;\
    }while(0)\

bool convertor(FILE* file_txt, FILE* file_bin,  struct string* strings, int num_of_lines, int* uncorrect_line)
{
    int data_bin[num_of_lines * 2] = {};/////
    int cur_data_position = 0;

    for (int i = 0; i < num_of_lines - 1; i++)
    {
        *uncorrect_line = i + 1;
        char cmd_buffer[MAX_STR_LENGTH] = "";

        sscanf(strings[i].position, " %14s", cmd_buffer);

    if(is_empty_string(cmd_buffer))
    {
        fprintf(file_txt, "\n");
        continue;
    }
        int code_buffer = ERROR;
        GET_CMD_CODE(cmd_buffer, code_buffer);

        switch(code_buffer)
        {
            case PUSH:  //1 argument command
            {
                double arg_d = 0;
                if(!sscanf(strings[i].position + strlen(TO_STR(PUSH)), " %lf", &arg_d))
                    return false;

                int arg_i = (int)(arg_d * 100 + 0.5);

                fprintf(file_txt, "%d", PUSH);
                data_bin[cur_data_position++] = PUSH;
                data_bin[cur_data_position++] = arg_i;
                fprintf(file_txt, " %d", arg_i);
            }
            break;

            case HLT: case OUT: case POP: case ADD: case SUB: case MUL: case DIV: //0 argument command
            {
                fprintf(file_txt, "%d", code_buffer);
                char symbol = '\0';
                sscanf(strings[i].position + strlen(cmd_buffer), " %c", &symbol);

                if(symbol)
                    return false;

                data_bin[cur_data_position++] = code_buffer;
            }
            break;

            default:
                return false;
        }

        fprintf(file_txt, "\n");
    }

    fwrite(data_bin, sizeof(int), cur_data_position, file_bin);

    return true;
}

bool is_empty_string(const char* str)
{
    if(*str == '\0')
        return true;
    else
        return false;
}
