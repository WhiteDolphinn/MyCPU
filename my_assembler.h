#ifndef MY_ASSEMBLER_H
#define MY_ASSEMBLER_H

#define MAX_COMMAND_LENGTH 15
#define NUM_OF_COMMANDS 10

struct command{
    const char* name;
    unsigned int code;
    };

enum comm{
    ERROR = 0xDED00DED,
    PUSH = 1,
    OUT = 2
};

char* convertor(struct string* strings, int num_of_lines, int num_of_symbols);
int what_command(char* ptr, char* text_asm, struct command* commands);
#endif
