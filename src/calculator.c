#include <string.h>

#include "calculator.h"

/* returns the stack pointer */
int shunting_yard(char *s, union token *stack)
{
	int stack_ptr = 0;
	return stack_ptr;
}

struct number eval_prefix(union token *stack, int in_stack_ptr)
{
	int i, stack_ptr = STACK_SIZE - 1;
	for (i = in_stack_ptr - 1; i >= 0; i--) {
		if (stack[i].is_op && stack_ptr < STACK_SIZE - 2) {
			struct number a = stack[++stack_ptr].num;
			struct number b = stack[++stack_ptr].num;
			stack[stack_ptr--].num = stack[i].op.calc(a,b);
		} else {
			stack[stack_ptr--] = stack[i];
		}
	}
	return stack[STACK_SIZE - 1].num;
}
int calculate(char *str, struct number *ret)
{
	union token stack[STACK_SIZE];
	int ptr = shunting_yard(str, stack);
	struct number r = eval_prefix(stack, ptr);
	if (ret == NULL)
		return -1;
	memcpy(ret, &r, sizeof(r));
	return 0;
}
