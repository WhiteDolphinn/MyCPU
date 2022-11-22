#include <string.h>
#include <stdlib.h>
#include "text.h"
#include "my_assembler.h"

bool convertor(FILE* file, struct string* strings, int num_of_lines, int* uncorrect_line)
{
    struct command *commands = (struct command*)calloc(NUM_OF_COMMANDS, sizeof(struct command));
    commands[PUSH] = {.name = TO_STR(PUSH), .code = PUSH};
    commands[OUT] = {.name = TO_STR(OUT), .code = OUT};

    for (int i = 0; i < num_of_lines - 1; i++)
    {
        *uncorrect_line = i + 1;
        char cmd_buffer[MAX_STR_LENGTH] = "";

        sscanf(strings[i].position, " %14s", cmd_buffer);

        if(!stricmp(cmd_buffer, TO_STR(PUSH)))
        {
            fprintf(file, "%d", PUSH);
            double arg_d = 0;
            if(!sscanf(strings[i].position + strlen(TO_STR(PUSH)), " %lf", &arg_d))
            {
                free(commands);
                return false;
            }
            int arg_i = (int)(arg_d * 100);
            fprintf(file, " %d", arg_i);
        }
        else if(!stricmp(cmd_buffer, TO_STR(OUT)))
        {
            fprintf(file, "%d", OUT);
            char symbol = '\0';
            sscanf(strings[i].position + strlen(TO_STR(OUT)), " %c", &symbol);
            //printf("%d\n", symbol);
            if(symbol)
            {
                free(commands);
                return false;
            }
        }
        else if(!stricmp(cmd_buffer, TO_STR(HLT)))
        {
            fprintf(file, "%d", HLT);
            char symbol = '\0';
            sscanf(strings[i].position + strlen(TO_STR(HLT)), " %c", &symbol);
            if(symbol)
            {
                free(commands);
                return false;
            }
        }
        else if(!stricmp(cmd_buffer, TO_STR(POP)))
        {
            fprintf(file, "%d", POP);
            char symbol = '\0';
            sscanf(strings[i].position + strlen(TO_STR(POP)), " %c", &symbol);
            if(symbol)
            {
                free(commands);
                return false;
            }
        }
        else if(!stricmp(cmd_buffer, TO_STR(SUM)))
        {
            fprintf(file, "%d", SUM);
            char symbol = '\0';
            sscanf(strings[i].position + strlen(TO_STR(SUM)), " %c", &symbol);
            if(symbol)
            {
                free(commands);
                return false;
            }
        }
        else if(!stricmp(cmd_buffer, TO_STR(SUB)))
        {
            fprintf(file, "%d", SUB);
            char symbol = '\0';
            sscanf(strings[i].position + strlen(TO_STR(SUB)), " %c", &symbol);
            if(symbol)
            {
                free(commands);
                return false;
            }
        }
        else if(!stricmp(cmd_buffer, TO_STR(MUL)))
        {
            fprintf(file, "%d", MUL);
            char symbol = '\0';
            sscanf(strings[i].position + strlen(TO_STR(MUL)), " %c", &symbol);
            if(symbol)
            {
                free(commands);
                return false;
            }
        }
        else if(!stricmp(cmd_buffer, TO_STR(DIV)))
        {
            fprintf(file, "%d", DIV);
            char symbol = '\0';
            sscanf(strings[i].position + strlen(TO_STR(DIV)), " %c", &symbol);
            if(symbol)
            {
                free(commands);
                return false;
            }
        }
        else
        {
            free(commands);
            return false;
        }
        fprintf(file, "\n");
    }
    free(commands);
    return true;
}

/*int what_command(char* ptr, char* text_asm, struct command* commands)
{
    char word[MAX_STR_LENGTH];

    if(sscanf(ptr, "%s", word) == 0)
        return ERROR;

    for(int i = 1; i < NUM_OF_COMMANDS; i++)
        if(!strcmp(word, commands[i].name))
            return commands[i].code;

    return 0;
}*/

/*char* old_convertor(struct string* strings, int num_of_lines, int num_of_symbols)
{
    struct command* commands = (struct command*)calloc(num_of_lines, sizeof(struct command));
    commands[PUSH] = {.name = TO_STR(PUSH), .code = PUSH};
    commands[OUT] = {.name = TO_STR(OUT), .code = OUT};



    char* ptr = strings[0].position; //text
    char* text_asm = (char*)calloc(num_of_symbols, sizeof(char));

    int comm_code = what_command(ptr, text_asm, commands);
    for(int i = 0; i < num_of_lines && comm_code != ERROR; i++)
    {
        ptr = strings[i].position;

      //  strcat(text_asm, commands[comm_code].name);
        //strcat(text_asm, (char*)commands[comm_code].code);
       // sprintf(text_asm, "%d", commands[comm_code].code);
        //text_position++;
        text_asm[i] = commands[comm_code].code;

        if(comm_code == PUSH)
            if(!strcmp(ptr+strlen(commands[comm_code].name), ""))
                strcat(text_asm, ptr+strlen(commands[comm_code].name));
            else
                strcat(text_asm, "ERROR_IN_PUSH!!!");

        strcat(text_asm, "\n");
        comm_code = what_command(ptr, text_asm, commands);
    }
    return text_asm;
}*/
