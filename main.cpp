#include <stdio.h>
#include <stdlib.h>
#include "my_assembler.h"
#include "text.h"
#include "soft_cpu.h"
#include "stack.h"
#include "stack_check.h"
#include "maths.h"
#include "errors.h"
#include "log.h"

void help();

int main(int argc, const char* argv[])
{
    if(argc != 2)
    {
        help();
        return 0;
    }

    const char* name_of_source_file = argv[1];
    int* commands = read_source_file(name_of_source_file);

    struct stack stk;
    stack_init(&stk);
    execute_cmds(&stk, commands);
    stack_delete(&stk);

    free(commands);
    return 0;
}

void help()
{
    printf("You should write name of file after the ./a.out\n");
    printf("./a.out \"name_of_source_file\"\n");
}
