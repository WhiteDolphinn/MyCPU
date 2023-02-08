#include <string.h>
#include <stdlib.h>
#include "my_assembler.h"

static bool is_empty_string(const char* str);
static bool is_link_string(const char* str);
static bool check_regist_command(const char* str, int* code_buffer, int* code_reg);
static int reg_cmd(const char* buf_reg);
static void get_func_code(struct link* func, char links[][NUM_OF_LINKS], int* link_positions);

bool convertor(
               FILE* file_txt,
               FILE* file_bin,
               struct string* strings,
               int num_of_lines,
               int* uncorrect_line,
               int* link_positions,
               int mode
               )
{
    int data_bin[num_of_lines * 2] = {};/////
    int cur_data_position = 0;
    static char links[MAX_STR_LENGTH][NUM_OF_LINKS] = {};

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
            static int cur_link_num = 0;
            char link_name[MAX_STR_LENGTH] = "";
            sscanf(cmd_buffer, " :%s ", link_name);

            for(int i = 0; link_name[i] != '\0'; i++)
                links[cur_link_num][i] = link_name[i];

            link_positions[cur_link_num] = cur_data_position;
            cur_link_num++;

            if(!is_empty_string(strings[i].position + strlen(cmd_buffer)))
                return false;

            fprintf(file_txt, "\n");
            continue;

        }

        #define DEFCMD(COMMAND, CODE)                    \
        if(!stricmp(cmd_buffer, TO_STR(COMMAND)))        \
            code_buffer = COMMAND;

        int code_buffer = ERROR;
        #include "get_command.h"
        #undef DEFCMD


        int arg_reg = ERROR;
        if(code_buffer == PUSH || code_buffer == POP)
            if(check_regist_command(strings[i].position, &code_buffer, &arg_reg))
            {
                EMIT(code_buffer);
                EMIT(arg_reg);
                fprintf(file_txt, "\n");
                continue;
            }

        switch(code_buffer)
        {
            case PUSH:  //1 argument command
            {
                double arg_d = 0;
                if(!sscanf(strings[i].position + strlen(TO_STR(PUSH)), " %lf", &arg_d))
                    return false;

                int arg_i = 0;
                if(arg_d >= 0)
                    arg_i = (int)(arg_d * 100 + 0.5);
                else
                    arg_i = (int)(arg_d * 100 - 0.5);

                EMIT(PUSH);
                EMIT(arg_i);
            }
            break;

            case JMP: case JB: case JBE: case JA: case JAE: case JE: case JNE: case CALL:
            {
                struct link func = {};
                bool is_link = false;
                char first_symbol = '\0';

                sscanf(strings[i].position + strlen(cmd_buffer), " %c", &first_symbol);

                if(first_symbol == ':')
                    is_link = true;

                if(sscanf(strings[i].position + strlen(cmd_buffer), " %c%s", &first_symbol, func.name) != 2)
                    return false;

                EMIT(code_buffer);

                if(is_link)
                {
                    get_func_code(&func, links, link_positions);

                    if(mode == 2 && func.code == -1)
                        return false;
                }

                char* func_pos = strchr(strings[i].position, ':');
                if(!is_empty_string(func_pos + strlen(func.name) + 1))
                    return false;

                EMIT(func.code);
            }
            break;

            case HLT: case OUT: case POP: case ADD: case SUB: case MUL: case DIV: case RET: case SQRT: case IN: //0 argument command
            {
                if(!is_empty_string(strings[i].position + strlen(cmd_buffer)))
                    return false;

                EMIT(code_buffer);
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

static bool is_empty_string(const char* str)
{
    char buf1 = 0;
    char buf2 = 0;

    sscanf(str, " %c", &buf1);

    if(buf1)
    {
        sscanf(str, " %c%c", &buf1, &buf2);
        return (buf1 == buf2) && (buf1 == '/');
    }
    else
        return true;

}

static bool is_link_string(const char* str)
{
    return *str == ':';
}

static bool check_regist_command(const char* str, int* code_buffer, int* code_reg)
{
    char buf_cmd[MAX_STR_LENGTH] = {};
    char buf_reg[MAX_STR_LENGTH] = {};

    if(sscanf(str, "%s %s", buf_cmd, buf_reg) == 2)
    {
        *code_reg = reg_cmd(buf_reg);
        if(*code_reg != -1)
        {
            switch(*code_buffer)
            {
                case PUSH:
                *code_buffer = PUSH_R;
                break;

                case POP:
                *code_buffer = POP_R;
                break;
            }
            return true;
        }
    }

    return false;
}

static int reg_cmd(const char* buf_reg)
{
    int cmd_code = -1;

    #define GETREG(REGIST, CODE)                \
        if(!stricmp(buf_reg, TO_STR(REGIST)))   \
            cmd_code = REGIST;
    #include "get_regist.h"

    #undef GETREG

    return cmd_code;
}

static void get_func_code(struct link* func, char links[][NUM_OF_LINKS], int* link_positions)
{
    for(int i = 0; i < NUM_OF_LINKS; i++)
    {
        if(!stricmp(links[i],func->name))
        {
            func->code = link_positions[i];
            return;
        }
    }
}
