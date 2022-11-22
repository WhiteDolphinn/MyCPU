#ifndef MY_ASSEMBLER_H
#define MY_ASSEMBLER_H
#include <stdio.h>

//#define MAX_COMMAND_LENGTH 15
//#define MAX_STR_LENGTH 15
#define NUM_OF_COMMANDS 65536
#define TO_STR(VAL) #VAL

struct command {
    const char* name;
    unsigned int code;
    };

enum cmd{
    ERROR = 0xDED00DED,
    PUSH = 1,
    OUT = 2,
    HLT = 0,
};

const char *const CMD_NAME[] =
{
    "HLT",
    "PUSH",
    "OUT",
    "ERROR",
};


bool convertor(FILE* file, struct string* strings, int num_of_lines, int num_of_symbols);
char* old_convertor(struct string* strings, int num_of_lines, int num_of_symbols);
int what_command(char* ptr, char* text_asm, struct command* commands);
#endif

