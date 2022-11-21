#include <string.h>
#include <stdlib.h>
#include "text.h"
#include "my_assembler.h"

char* convertor( struct string* strings, int num_of_lines, int num_of_symbols)
{
    struct command commands[NUM_OF_COMMANDS] = {};
    commands[PUSH] = {.name = "push", .code = PUSH};
    commands[OUT] = {.name = "out", .code = OUT};

    char* ptr = strings[0].position; //text
    //printf("%d", num_of_symbols);
    char* text_asm = (char*)calloc(num_of_symbols, sizeof(char));

    int comm_code = what_command(ptr, text_asm, commands);
    for(int i = 0; i < num_of_lines && comm_code != ERROR; i++)
    {
        ptr = strings[i].position;

      //  strcat(text_asm, commands[comm_code].name);
        //strcat(text_asm, (char*)commands[comm_code].code);
        sprintf(text_asm, "%d", commands[comm_code].code);

        if(comm_code == PUSH)
            if(!strcmp(ptr+strlen(commands[comm_code].name), ""))
                strcat(text_asm, ptr+strlen(commands[comm_code].name));
            else
                strcat(text_asm, "ERROR_IN_PUSH!!!");

        comm_code = what_command(ptr, text_asm, commands);
    }
    return text_asm;
}

int what_command(char* ptr, char* text_asm, struct command* commands)
{
    char word[MAX_COMMAND_LENGTH];

    if(sscanf(ptr, "%s", word) == 0)
        return ERROR;

    for(int i = 1; i < NUM_OF_COMMANDS; i++)
        if(!strcmp(word, commands[i].name))
            return commands[i].code;

    return 0;
}

/*void command_to_num(int num_of_command, char* text_asm)
{
    strcat(text_asm, num_of_command);
}*/
