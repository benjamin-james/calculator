#include <string.h>

#include "calculator.h"

/* returns the stack pointer */
int shunting_yard(char *s, union token *stack)
{
	int stack_ptr = 0;
}

struct number eval(union token *in_stack, int in_stack_ptr)
{
	int i;
	struct number stack[256];
	int stack_ptr = 0;
	for (i = 0; i < in_stack_ptr, i++) {
		if (in_stack[i].is_op && stack_ptr > 1) {
			struct number a = stack[stack_ptr--];
			struct number b = stack[stack_ptr--];
			stack[stack_ptr++] = in_stack[i].op.calc(a,b);
		} else {
			stack[stack_ptr++] = in_stack[i].num;
		}
	}
	return *stack;
}
int calculate(char *str, struct number *ret)
{
	union token stack[256];
	int ptr = shunting_yard(str, stack);
	struct number *r = eval(stack, ptr);
	if (r == NULL)
		return -1;
	*ret = *r;
	return 0;
}
