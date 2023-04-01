#ifndef SOFT_CPU_H
#define SOFT_CPU_H
#include <stdio.h>
#include "stack.h"
#include "my_assembler.h"

#define SIZE_RAM 256

struct cpu{
    struct stack stk;
    int* commands;
    element_t registers[REGISTER_COUNT];
    element_t RAM[SIZE_RAM];
};

int* read_source_file(const char* name_of_source_file);
void start_cpu(struct cpu* cpu, int* commands);
void stop_cpu(struct cpu* cpu);
void execute_cmds(struct cpu* cpu);
void print_cpu(struct cpu* cpu);
#endif
