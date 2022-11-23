#ifndef MY_ASSEMBLER_H
#define MY_ASSEMBLER_H
#include <stdio.h>

//#define MAX_COMMAND_LENGTH 15
//#define MAX_STR_LENGTH 15
#define ERROR 0xDED00DED
#define NUM_OF_COMMANDS 10
#define TO_STR(VAL) #VAL

/*struct command {
    const char* name;
    unsigned int code;
    };*/

enum cmd{
    HLT = 0,
    PUSH = 1,
    OUT = 2,
    POP = 3,
    SUM = 4,
    SUB = 5,
    MUL = 6,
    DIV = 7,
};

bool convertor(FILE* file, struct string* strings, int num_of_lines, int* uncorrect_line);
//char* old_convertor(struct string* strings, int num_of_lines, int num_of_symbols);
//int what_command(char* ptr, char* text_asm, struct command* commands);
#endif

