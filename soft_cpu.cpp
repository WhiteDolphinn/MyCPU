#include <stdlib.h>
#include "soft_cpu.h"
#include "text.h"
#include "maths.h"
#include "errors.h"
#include "stack_check.h"
#include "log.h"

static int execute_jump(struct cpu* cpu, int i);

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
        cpu->registers[i] = POISON;

    cpu->commands = commands;

    stack_init(&cpu->stk);
}

void stop_cpu(struct cpu* cpu)
{
    free(cpu->commands);
    stack_delete(&cpu->stk);
}

void execute_cmds(struct cpu* cpu)
{
    for(int i = 0; ; i++)
    {
        print_cpu(cpu);
        switch(cpu->commands[i])
        {
            case PUSH:
                stack_push(&cpu->stk, cpu->commands[++i]);
            break;

            case PUSH_R:
                stack_push(&cpu->stk, cpu->registers[cpu->commands[++i]]);
            break;

            case OUT:
            {
                printf("%.2lf\n", (double)stack_pop(&cpu->stk) / 100);
            }
            break;

            case POP:
                stack_pop(&cpu->stk);
            break;

            case POP_R:
                cpu->registers[cpu->commands[++i]] = stack_pop(&cpu->stk);
            break;

            case ADD:
                stack_add(&cpu->stk);
            break;

            case SUB:
                stack_sub(&cpu->stk);
            break;

            case MUL:
                stack_mul(&cpu->stk);
            break;

            case DIV:
                stack_div(&cpu->stk);
            break;

            case HLT:
                return;

            case JMP: case JB: case JBE: case JA: case JAE: case JE: case JNE: case CALL: case RET:
            {
                i = execute_jump(cpu, i);
            }
            break;

            default:
                printf("Unknown command: %d\n", cpu->commands[i]);
                print_cpu(cpu);
                return;
        }
    }
}

static int execute_jump(struct cpu* cpu, int i)
{
    int mode = cpu->commands[i];
    if(mode == JMP)
        return cpu->commands[i+1] - 1;

    if(mode == CALL)
    {
        stack_push(&cpu->stk, i+1);
        i++;
        return cpu->commands[i] - 1;
    }

    if(mode == RET)
        return stack_pop(&cpu->stk);

    element_t val1 = stack_pop(&cpu->stk);
    element_t val2 = stack_pop(&cpu->stk);

    i++;
    int is_true_condition = -1;
    switch(mode)
    {
        case JB:
            is_true_condition = val1 < val2;
        break;

        case JBE:
            is_true_condition = val1 <= val2;
        break;

        case JA:
            is_true_condition = val1 > val2;
        break;

        case JAE:
            is_true_condition = val1 >= val2;
        break;

        case JE:
            is_true_condition = val1 == val2;
        break;

        case JNE:
            is_true_condition = val1 != val2;
        break;
    }

    if(is_true_condition == 1)
        return cpu->commands[i] - 1;

    if(is_true_condition == 0)
        return i;

    return -1;
}

void print_cpu(struct cpu* cpu)
{
    FILE* log_file = get_log_file();

    fprintf(log_file, "****************************\n");
    for(int i = 0; i < REGISTER_COUNT; i++)
        if(cpu->registers[i] == (int)POISON)
            fprintf(log_file, "registers[%d] = %X\n", i, cpu->registers[i]);
        else
            fprintf(log_file, "registers[%d] = %d\n", i, cpu->registers[i]);
}
