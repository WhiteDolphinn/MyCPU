#ifndef ERRORS_H
#define ERRORS_H
#include "stack.h"

#define NUM_OF_ERRORS 10

struct error{

char name[50];
unsigned int code;
};

int stack_test(struct stack* stack);
void print_errors(FILE* file, int error);
int is_error(struct stack* stack, const char* function);

#endif
