#include <stdlib.h>
#include "soft_cpu.h"
#include "my_assembler.h"
#include "text.h"
#include "stack.h"
#include "maths.h"
#include "errors.h"
#include "stack_check.h"
#include "log.h"
#include <assert.h>

int* read_source_file(const char* name_of_source_file)
{
    FILE* source_file = fopen(name_of_source_file, "rb");

    if(source_file == nullptr)
    {
        printf("I can't open file: <%s>", name_of_source_file);
        fclose(source_file);
        return nullptr;
    }

    int* commands = (int*)calloc(num_of_symbols(name_of_source_file), sizeof(int));
    fread(commands, sizeof(int), num_of_symbols(name_of_source_file), source_file);

    fclose(source_file);
    return commands;
}

void execute_cmds(struct stack* stack, int* commands)
{
    for(int i = 0; ; i++)
    {
        switch(commands[i])
        {
            case PUSH:
                stack_push(stack, commands[++i]);
            break;

            case OUT:
            {
                printf("%d\n", stack_pop(stack));
            }
            break;

            case POP:
            {
                element_t val = stack_pop(stack);
            }
            break;

            case SUM:
                stack_add(stack);
            break;

            case SUB:
                stack_sub(stack);
            break;

            case MUL:
                stack_mul(stack);
            break;

            case DIV:
                stack_div(stack);
            break;

            case HLT:
                return;

            default:
                assert(0);

        }
    }
}
