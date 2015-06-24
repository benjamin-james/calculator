#include <stdio.h>

#include "calculator.h"

void add_num(double num, union token *tok)
{
	tok->is_op = 0;
	tok->num.num = num;
}
struct number mult(struct number a, struct number b)
{
	struct number ret;
	ret.num = a.num * b.num;
	return ret;
}
void add_mult(union token *tok)
{
	tok->is_op = 1;
	tok->op.op = '*';
	tok->op.calc = mult;
}
struct number add(struct number a, struct number b)
{
	struct number ret;
	ret.num = a.num + b.num;
	return ret;
}

void add_add(union token *tok)
{
	tok->is_op = 1;
	tok->op.op = '+';
	tok->op.calc = add;
}
int main(void)
{
	union token stack[STACK_SIZE];
	int ptr = 0;
	struct number n;
	add_mult(stack + ptr++);
	add_num(7.5, stack + ptr++);
	add_add(stack + ptr++);
	add_num(4.0, stack + ptr++);
	add_num(5.0, stack + ptr++);
	eval_prefix(stack, ptr, &n);
	printf("%f\n", n.num);
}
