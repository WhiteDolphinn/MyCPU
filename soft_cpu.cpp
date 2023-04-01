#include <stdlib.h>
#include <unistd.h>
#include "soft_cpu.h"
#include "text.h"
#include "maths.h"
#include "errors.h"
#include "stack_check.h"
#include "log.h"

static int execute_jump(struct cpu* cpu, int cmd_pos);

int* read_source_file(const char* name_of_source_file)
{
    FILE* source_file = fopen(name_of_source_file, "rb");

    if(source_file == nullptr)
    {
        printf("I can't open file: <%s>\n", name_of_source_file);
        return nullptr;
    }

    int* commands = (int*)calloc((size_t)num_of_symbols(name_of_source_file), sizeof(int));
    fread(commands, sizeof(int), (size_t)num_of_symbols(name_of_source_file), source_file);

    fclose(source_file);
    return commands;
}

void start_cpu(struct cpu* cpu, int* commands)
{
    for(int i = 0; i < REGISTER_COUNT; i++)
        cpu->registers[i] = POISON;

    for(int i = 0; i < SIZE_RAM; i++)
        cpu->RAM[i] = POISON;

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
    for(int cmd_pos = 0; ; cmd_pos++)
    {
        print_cpu(cpu);
        switch(cpu->commands[cmd_pos])
        {
            case PUSH:
                stack_push(&cpu->stk, cpu->commands[++cmd_pos]);
            break;

            case PUSH_R:
                stack_push(&cpu->stk, cpu->registers[cpu->commands[++cmd_pos]]);
            break;

            case PUSH_RAM:
            {
                sleep(1);
                stack_push(&cpu->stk, cpu->RAM[cpu->commands[++cmd_pos]]);
                break;
            }

            case OUT:
            {
                printf("%.2lf\n", (double)stack_pop(&cpu->stk) / 100);
            }
            break;

            case POP:
                stack_pop(&cpu->stk);
            break;

            case POP_R:
                cpu->registers[cpu->commands[++cmd_pos]] = stack_pop(&cpu->stk);
            break;

            case POP_RAM:
            {
                sleep(1);
                cpu->RAM[cpu->commands[++cmd_pos]] = stack_pop(&cpu->stk);
                break;
            }

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

            case SQRT:
                stack_sqrt(&cpu->stk);
            break;

            case IN:
            {
                double val = 0;
                printf("Enter a value: ");
                while(!scanf("%lf", &val))
                    printf("Uncorrect input. Please, try again\n");

                if(val >= 0)
                    stack_push(&cpu->stk, (int)(val * 100 + 0.5));
                else
                    stack_push(&cpu->stk, (int)(val * 100 - 0.5));
            }
            break;

            case JMP: case JB: case JBE: case JA: case JAE: case JE: case JNE: case CALL: case RET:
            {
                cmd_pos = execute_jump(cpu, cmd_pos);
            }
            break;

            default:
                printf("Unknown command: %d\n", cpu->commands[cmd_pos]);
                print_cpu(cpu);
                return;
        }
    }
}

static int execute_jump(struct cpu* cpu, int cmd_pos)
{
    int mode = cpu->commands[cmd_pos];
    if(mode == JMP)
        return cpu->commands[cmd_pos+1] - 1;

    if(mode == CALL)
    {
        stack_push(&cpu->stk, cmd_pos+1);
        cmd_pos++;
        return cpu->commands[cmd_pos] - 1;
    }

    if(mode == RET)
        return stack_pop(&cpu->stk);

    element_t val1 = stack_pop(&cpu->stk);
    element_t val2 = stack_pop(&cpu->stk);

    cmd_pos++;
    int is_true_condition = -1;
    switch(mode)
    {
        case JB:
            is_true_condition = (val1 < val2);
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

        default: return -1;
    }

    if(is_true_condition == 1)
        return cpu->commands[cmd_pos] - 1;

    if(is_true_condition == 0)
        return cmd_pos;

    return -1;
}

void print_cpu(struct cpu* cpu)
{
    FILE* log_file = get_log_file();

    fprintf(log_file, "****************************\n");
    for(int i = 0; i < REGISTER_COUNT; i++)
        if(cpu->registers[i] == POISON)
            fprintf(log_file, "registers[%d] = %X\n", i, (unsigned)POISON);
        else
            fprintf(log_file, "registers[%d] = %d\n", i, cpu->registers[i]);

    fprintf(log_file, "****************************\n");

    for(int i = 0; i < SIZE_RAM; i++)
    {
        if(cpu->RAM[i] == POISON)
            fprintf(log_file, "p\t");
        else
            fprintf(log_file, "%d\t", cpu->RAM[i]);

        if((i + 1) % 16 == 0)
            fprintf(log_file, "\n");
    }
    fprintf(log_file, "\n");
}
