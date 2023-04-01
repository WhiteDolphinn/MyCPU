#ifndef MY_ASSEMBLER_H
#define MY_ASSEMBLER_H
#include <stdio.h>
#include "text.h"

#define ERROR (int)0xDED00DED
#define NUM_OF_COMMANDS 25
#define NUM_OF_LINKS 50
#define REGISTER_COUNT 6
#define TO_STR(VAL) #VAL

#define EMIT(BUFF)                          \
    fprintf(file_txt, "%d ", BUFF);         \
    data_bin[cur_data_position++] = BUFF

struct link{
    char name[MAX_STR_LENGTH];
    int code;
};

#define DEFCMD(COMMAND, CODE)\
    COMMAND = CODE,

enum cmd{
    #include "get_command.h"
    PUSH_R = 15,
    POP_R = 16,         //NUM_OF_COMMANDS == 25
    PUSH_RAM = 21,
    POP_RAM = 22,
    #undef DEFCMD
};

#define GETREG(REGIST, CODE)\
    REGIST = CODE,

enum regist{
    #include "get_regist.h"
    #undef GETREG
     //REGISTER_COUNT == 6
};

bool convertor(
               FILE* file_txt,
               FILE* file_bin,
               struct string* strings,
               int num_of_lines,
               int* uncorrect_line,
               int* link_positions,
               int mode
               );
#endif

