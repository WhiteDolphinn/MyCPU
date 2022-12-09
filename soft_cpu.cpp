#include <stdlib.h>
#include "soft_cpu.h"
#include "my_assembler.h"
#include "text.h"
#include "maths.h"
#include "errors.h"
#include "stack_check.h"
#include "log.h"
#include <assert.h>

static int execute_jump(struct stack* stack, int* commands, int mode, int i);

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

void start_cpu(struct cpu* cpu, int* commands)
{
    for(int i = 0; i < REGISTER_COUNT; i++)
        cpu->registers[i] = 0;

    cpu->commands = commands;

    stack_init(&cpu->stk);
}

void stop_cpu(struct cpu* cpu)
{
    free(cpu->commands);
    stack_delete(&cpu->stk);
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
                printf("%d\n", stack_pop(stack) / 100);
            }
            break;

            case POP:
            {
                element_t val = stack_pop(stack);
            }
            break;

            case ADD:
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

            case JMP: case JB: case JBE: case JA: case JAE: case JE: case JNE:
            {
                i = execute_jump(stack, commands, commands[i], i);
            }
            break;

            default:
                printf("Unknown command: %d\n", commands[i]);
                assert(0);

        }
    }
}

static int execute_jump(struct stack* stack, int* commands, int mode, int i)
{
    if(mode == JMP)
        return commands[i+1] - 1;

    element_t val1 = stack_pop(stack);
    element_t val2 = stack_pop(stack);

    i++;
    int is_true_condition = -1;
    switch(mode)
    {
        case JB:
            if(val1 < val2)
                is_true_condition = 1;
            else
                is_true_condition = 0;
        break;

        case JBE:
            if(val1 <= val2)
                is_true_condition = 1;
            else
                is_true_condition = 0;
        break;

        case JA:
            if(val1 > val2)
                is_true_condition = 1;
            else
                is_true_condition = 0;
        break;

        case JAE:
            if(val1 >= val2)
                is_true_condition = 1;
            else
                is_true_condition = 0;
        break;

        case JE:
            if(val1 == val2)
                is_true_condition = 1;
            else
                is_true_condition = 0;
        break;

        case JNE:
            if(val1 != val2)
                is_true_condition = 1;
            else
                is_true_condition = 0;
        break;
    }

    if(is_true_condition == 1)
        return commands[i] - 1;

    if(is_true_condition == 0)
        return i;

    return -1;
}
