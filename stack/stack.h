#ifndef STACK_H
#define STACK_H

#include <stdio.h>

#define PRINT_IN_CONSOLE 0
//#define SIZE 15
#define POISON (int)0xDED32DED
#define SHORT_POISON 228
#define LEFT_DATA_CANARY 0xBADEDA1
#define RIGHT_DATA_CANARY 0xBADEDA2
#define LEFT_STACK_CANARY 0xEDABAD1
#define RIGHT_STACK_CANARY 0xEDABAD2

#define STACK_DUMP(STACK)\
    stack_dump(get_log_file(), STACK, __FILE__, __LINE__, "stack_dump");

typedef int element_t;

struct stack{
    unsigned int left_stack_canary;
    element_t *data;
    int depth;
    int size;
    int error;
    long long int hash;
    char is_init;
    char is_resized;
    unsigned int right_stack_canary;
    };

void stack_init(struct stack* stack);
void stack_delete(struct stack* stack);
void stack_push(struct stack* stack, element_t i);
element_t stack_pop(struct stack* stack);
void stack_print(FILE* file, struct stack* stack);
void stack_dump(FILE* file, struct stack* stack, const char* filename, int line, const char* function);

void stack_resize(struct stack* stack, int extra_mem);

#endif
