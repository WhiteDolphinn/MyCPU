#ifndef MY_ASSEMBLER_H
#define MY_ASSEMBLER_H
#include <stdio.h>

//#define MAX_COMMAND_LENGTH 15
//#define MAX_STR_LENGTH 15
#define ERROR 0xDED00DED
#define NUM_OF_COMMANDS 10
#define NUM_OF_LINKS 5
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
    ADD = 4,
    SUB = 5,
    MUL = 6,
    DIV = 7,
    JMP = 8,
};

bool convertor(FILE* file_txt, FILE* file_bin, struct string* strings, int num_of_lines, int* uncorrect_line, int* link_positions);
bool is_empty_string(const char* str);
int link_convertor(int position, int* link_positions);
int* check_links(int* link_positions, struct string* strings, int num_of_lines);
bool is_link_string(const char* str);
#endif

