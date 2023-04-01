#include <math.h>
#include "maths.h"
#include "stack.h"
#include "errors.h"
#include "stack_check.h"
#include "log.h"


void stack_add(struct stack* stack)
{
    stack_check(stack);
    if(is_error(stack, __func__))
        return;

    int x = stack_pop(stack);
    int y = stack_pop(stack);
    stack_push(stack, y + x);

    stack_check(stack);
}

void stack_sub(struct stack* stack)
{
    stack_check(stack);
    if(is_error(stack, __func__))
        return;

    int x = stack_pop(stack);
    int y = stack_pop(stack);
    stack_push(stack, y - x);

    stack_check(stack);
}

void stack_mul(struct stack* stack)
{
    stack_check(stack);
    if(is_error(stack, __func__))
        return;

    int x = stack_pop(stack);
    int y = stack_pop(stack);
    stack_push(stack, (y/10) * (x /10));

    stack_check(stack);
}

void stack_div(struct stack* stack)
{
    stack_check(stack);
    if(is_error(stack, __func__))
        return;

    int x = stack_pop(stack);
    int y = stack_pop(stack);
    double res = (double)y / (double)x;
    stack_push(stack, (int)(res * 100));

    stack_check(stack);
}

void stack_sqrt(struct stack* stack)
{
    stack_check(stack);
    if(is_error(stack, __func__))
        return;

    int x = stack_pop(stack);
    double res = sqrt((double)x);
    stack_push(stack, (int)(res * 10));

    stack_check(stack);
}
