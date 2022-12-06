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
        if(!stricmp(COMMAND, TO_STR(JMP)))\
            CODE = JMP;\
    }while(0)\

bool convertor(FILE* file_txt, FILE* file_bin,  struct string* strings, int num_of_lines, int* uncorrect_line, int* link_positions)
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

    if(is_link_string(cmd_buffer))
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

            case JMP:
            {
                int position = 0;
                bool is_link = false;
                char first_symbol = '\0';

                sscanf(strings[i].position + strlen(TO_STR(JMP)), " %c", &first_symbol);

                if(first_symbol == ':')
                    is_link = true;
                //printf("vsovm");
                if(sscanf(strings[i].position + strlen(TO_STR(JMP)), " %c%d", &first_symbol, &position) != 2)
                {
                    //printf("%c %d\n", first_symbol, position);
                    return false;
                }

                fprintf(file_txt, "%d", JMP);
                data_bin[cur_data_position++] = JMP;

                if(is_link)
                {
                    position = link_positions[position];

                    if(position == -1)
                        return false;
                }

                data_bin[cur_data_position++] = position;
                fprintf(file_txt, " %d", position);
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

int link_convertor(int position, int* link_positions)
{
    return link_positions[position];
}

int* check_links(int* link_positions, struct string* strings, int num_of_lines)
{
   // int link_positions[NUM_OF_LINKS] = {};

    for(int i = 0; i < NUM_OF_LINKS; i++)
        link_positions[i] = -1;

    for(int i = 0; i < num_of_lines; i++)
    {
        char first_symbol = '\0';
        int link_num = 0;

        sscanf(strings[i].position, " %c", &first_symbol);

        if(first_symbol == ':')
        {
            if(sscanf(strings[i].position, " %c%d", &first_symbol, &link_num) == 2)
            {
                link_positions[link_num] = i + 1; //или i
                //printf("link_positions[%d] = %d\n", link_num, i+1);
            }
            else
            {
                printf("Error in %d line!!!", i+1);
                free(link_positions);
                return nullptr;
            }
        }
    }
    return link_positions;
}

bool is_link_string(const char* str)
{
    if(*str == ':')
        return true;
    else
        return false;
}
