#ifndef STACK_CHECK_H
#define STACK_CHECK_H
#include "stack.h"
#include "errors.h"

#define stack_check(STRUCT)                                     \
do                                                              \
{                                                               \
    FILE* file = get_log_file();                                \
    if(stack->data != nullptr)                                  \
        stack_dump(file, stack, __FILE__, __LINE__, __func__);  \
    if(stack_test(STRUCT))                                      \
    {                                                           \
        int error = stack_test(STRUCT);                         \
        print_errors(file, error);                              \
        }                                                       \
} while (0)

#endif
