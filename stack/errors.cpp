#include "errors.h"
#include "log.h"
#include <stdio.h>

static long long sum_of_elements(struct stack* stack);

int stack_test(struct stack* stack)
{
    int error = 0;


    if(stack -> data == nullptr)     //ERR_DATA
        error |= (0x01 << 0);

    if(stack -> depth >= stack->size || stack->depth < 0)          //ERR_DEPTH
        error |= (0x01 << 1);

    if(stack -> is_init == 0)               //ERR_INIT
        error |= (0x01 << 2);

    if(stack->is_resized == 1)           //ERR_RESIZE
        error |= (0x01 << 3);

    if(stack->left_stack_canary != LEFT_STACK_CANARY)       //ERR_LEFT_STACK_CANARY
        error |= (0x01 << 4);

    if(stack->right_stack_canary != RIGHT_STACK_CANARY)         //ERR_RIGHT_STACK_CANARY
        error |= (0x01 << 5);

    unsigned int* left_data_canary_ptr = (unsigned int*)(stack->data - sizeof(unsigned int)/sizeof(element_t));
    if(*left_data_canary_ptr != LEFT_DATA_CANARY)             //ERR_LEFT_DATA_CANARY
        error |= (0x01 << 6);

    unsigned int* right_data_canary_ptr = (unsigned int*)(stack->data + stack->size);
    if(*right_data_canary_ptr != RIGHT_DATA_CANARY)             //ERR_RIGHT_DATA_CANARY
        error |= (0x01 << 7);

    if(stack->hash != sum_of_elements(stack))
    {
        printf("%lld %lld %lld\n", stack->hash, sum_of_elements(stack), stack->hash - sum_of_elements(stack));
        error |= (0x01 << 8);
    }

    stack->error = error;
    return error;
}

void print_errors(FILE* file, int error)
{
  static struct error errors[NUM_OF_ERRORS];
    errors[0] = {.name = "OK", .code = 0};
    errors[1] = {.name = "ERR_DATA", .code = 1};
    errors[2] = {.name = "ERR_DEPTH", .code = 2};
    errors[3] = {.name = "ERR_INIT", .code = 3};
    errors[4] = {.name = "ERR_RESIZE", .code = 4};
    errors[5] = {.name = "ERR_LEFT_STACK_CANARY", .code = 5};
    errors[6] = {.name = "ERR_RIGHT_STACK_CANARY", .code = 6};
    errors[7] = {.name = "ERR_LEFT_DATA_CANARY", .code = 7};
    errors[8] = {.name = "ERR_RIGHT_DATA_CANARY", .code = 8};
    errors[9] = {.name = "ERR_HASH", .code = 9};//last error (const num_of_errors = 10)

    for(int i = 1; i <= NUM_OF_ERRORS; i++)
    {
        if((error | 1) == error)
        {
            fprintf(file, "\033[33mError!!!\t %s\t Code: %d\033[0m\n", errors[i].name, i);
        }
        error = error >> 1;
    }
}

int is_error(struct stack* stack, const char* function)
{
    if(stack->error != 0)
    {
        FILE* log_file = get_log_file();
        print_errors(log_file, stack->error);
        fprintf(log_file, "%s wasn't work\n", function);
      //  fclose(log_file);

        return 1;
    }
    return 0;
}

static long long int sum_of_elements(struct stack* stack)
{
    long long int sum_of_elements = 0;

    for(int i = 0; i < stack->size; i++)
        if(stack->data[i] == POISON)
            sum_of_elements += SHORT_POISON;
        else
            sum_of_elements += stack->data[i];

    return sum_of_elements;
}
