#include "stack.h"
#include "errors.h"
#include "stack_check.h"
#include "log.h"
#include <stdio.h>
#include <malloc.h>
#include <execinfo.h>
#include <time.h>

void stack_init(struct stack* stack)
{
    stack->size = 10;
    stack->hash = 10 * SHORT_POISON;

    stack->data = (element_t*)malloc((size_t)stack->size * sizeof(element_t) + 2 * sizeof(unsigned int));

    unsigned int* stack_data_int = (unsigned int*)stack->data; //left_canary
    stack_data_int[0] = LEFT_DATA_CANARY;


    stack->data += sizeof(unsigned int) / sizeof(element_t);

    stack_data_int = (unsigned int*)(stack->data + stack->size); //right_canary
    *stack_data_int = RIGHT_DATA_CANARY;

    for(int i = 0; i < stack->size; i++)
        stack -> data[i] = POISON;

    stack->depth = 0;
    stack->error = 0;
    stack->is_init = 1;
    stack->is_resized = 0;
    stack->left_stack_canary = LEFT_STACK_CANARY;
    stack->right_stack_canary = RIGHT_STACK_CANARY;

    stack_check(stack);
}

void stack_delete(struct stack* stack)
{
    fprintf(get_log_file(), "Stack was deleted!!!");
    stack_check(stack);
    stack->depth = -1;
    stack->size = 0;
    stack->hash = 0;
    stack->error = 0;
    stack->is_init = 0;
    stack->data -= sizeof(unsigned int) / sizeof(element_t);
    free(stack->data);
    stack->data = 0;
}

void stack_push(struct stack* stack, element_t i)
{
    stack_check(stack);
    if(is_error(stack, __func__))
        return;

    stack -> data[stack -> depth] = i;
    stack -> depth++;

    stack -> hash += i;
    stack -> hash -= SHORT_POISON;

    if(stack->depth + 3 == stack->size)
        stack_resize(stack, 5);

    stack_check(stack);
}

element_t stack_pop(struct stack* stack)
{
    stack_check(stack);
    if(is_error(stack, __func__))
        return POISON;

    element_t last_element = stack -> data[stack -> depth - 1];
    stack->data[stack->depth - 1] = POISON;
    stack -> depth--;

    stack->hash += SHORT_POISON;
    stack->hash -= last_element;

    stack_check(stack);
    return last_element;
}

void stack_print(FILE* file, struct stack* stack)
{
    fprintf(file, "\033[34m");
    fprintf(file, "========================\n");
    for(int i = 0; i < stack->size; i++)
    {
        if(stack->data[i] != POISON)
            fprintf(file, "%d:  %d\n", i, stack -> data[i]);
        else
            fprintf(file, "%d: %X\n", i, (unsigned)POISON);
    }
    fprintf(file, "========================\n\n");
    fprintf(file, "\033[0m");
}

void stack_dump(
                FILE* file,
                struct stack* stack,
                const char* filename,
                int line,
                const char* function
                )
{
    stack_print(file, stack);

    void* arr[10] = {0};
    size_t size = (size_t)backtrace(arr, 10);

    char** logs = backtrace_symbols(arr, (int)size);
    fprintf(file, "\033[31m");
    for(size_t i = 0; i < size; i++)
        fprintf(file, "%s\n", logs[i]);



    fprintf(file, "\n\033[0m");

    fprintf(file, "File: %s\nLine: %d\nFunction: %s\n\n", filename, line, function);
    free(logs);
}

void stack_resize(struct stack* stack, int extra_mem)
{
    stack_check(stack);

    stack->is_resized = 1;
    stack->data -= sizeof(unsigned int) / sizeof(element_t);//////
    stack->data = (element_t*)realloc(stack->data, (size_t)(stack->size + extra_mem) * sizeof(element_t) + 2 * sizeof(unsigned int));

    if(stack->data != nullptr)
        stack->is_resized = 0;
    else    return;

    stack->data += sizeof(unsigned int) / sizeof(element_t);////////

    unsigned int* right_data_canary_ptr = (unsigned int*)(stack->data + stack->size + extra_mem);
    *right_data_canary_ptr = RIGHT_DATA_CANARY;

    for(int i = 0; i < extra_mem; i++)
        stack->data[stack->size + i] = POISON;

    stack->hash += extra_mem * SHORT_POISON;

    stack->size += extra_mem;

    stack_check(stack);
}
