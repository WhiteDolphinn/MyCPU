#ifndef SOFT_CPU_H
#define SOFT_CPU_H
#include <stdio.h>
int* read_source_file(const char* name_of_source_file);
void execute_cmds(struct stack* stack,int* commands);
#endif
