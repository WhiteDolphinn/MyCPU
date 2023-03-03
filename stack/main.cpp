#include "stack.h"
#include "errors.h"
#include "maths.h"
#include "log.h"
#include <stdio.h>
#include <malloc.h>

int main()
{
  	struct stack stack;
	stack_init(&stack);
    stack_push(&stack, 3);
    stack_push(&stack, 4);
	//stack_delete(&stack);
	stack_push(&stack, 5);
	//stack.depth = -2;
	stack_push(&stack, 7);
	stack_push(&stack, 6);
	stack_push(&stack, 6);
	stack_push(&stack, 6);
	stack_push(&stack, 6);
	stack_push(&stack, 6);
	stack_push(&stack, 6);
	stack_push(&stack, 6);
	stack_push(&stack, 6);
	stack_push(&stack, 6);
	stack_div(&stack);
	stack_add(&stack);
	stack_sub(&stack);
	int i = stack_pop(&stack);
    //stack_dump(get_log_file() ,&stack, __FILE__, __LINE__, __func__);
	stack_delete(&stack);
	//printf("%d\n", i);
	//fclose(get_log_file());

    return 0;
}
