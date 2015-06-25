#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mpfr.h>

#include "calculator.h"
#include "operator.h"

int op_loop(struct operator *stack, int *stack_ptr, union token *queue, int *queue_ptr, int prec)
{
	while (*stack_ptr > 0) {
		struct operator *t = stack + *stack_ptr - 1;
		if (!(t->prec == prec && t->assoc == LEFT_ASSOC) && t->prec <= prec)
			break;
		queue[*queue_ptr].is_op = 1;
		queue[(*queue_ptr)++].op = stack[--(*stack_ptr)];
	}
	return 0;
}
/*
void display(struct operator *stack, int stack_ptr, union token *queue, int queue_ptr)
{
	puts("");
	int i;
	for (i = 0; i < stack_ptr; i++) {
		printf("%c ", stack[i].op);
	}
	puts("");
	for (i = 0; i < queue_ptr; i++) {
		if (queue->is_op)
			printf("%c ", queue[i].op.op);
		else
			printf("%f ", queue[i].num.num);
	}
	puts("\n");
	}*/
/* returns the stack pointer */
int shunting_yard(char *s, union token *queue)
{
	int stack_ptr = 0, queue_ptr = 0;
	struct operator stack[STACK_SIZE];
	const char *skip = "\t\n\r\f ";
	char *tok;
	int paren_mask = 0;
	for (tok = strtok(s, skip); tok; tok = strtok(NULL, skip)) {
		union token temp;
		int type = get_type(tok);
		switch (type) {
		case OP_TYPE:
			temp.is_op = 1;
			get_op(tok, &temp.op);
			temp.op.prec += paren_mask;
			op_loop(stack, &stack_ptr, queue, &queue_ptr, temp.op.prec);
			stack[stack_ptr++] = temp.op;
			break;
		case NUM_TYPE:
			temp.is_op = 0;
			get_num(tok, &temp.num);
			queue[queue_ptr++] = temp;
			break;
		case LPARENS_TYPE:
			paren_mask += 10;
			break;
		case RPARENS_TYPE:
			if (paren_mask < 10)
				return -1;
			op_loop(stack, &stack_ptr, queue, &queue_ptr, paren_mask);
			paren_mask -= 10;
			break;
		}
	}
	while (stack_ptr > 0)
		queue[queue_ptr++].op = stack[--stack_ptr];
	return queue_ptr;
}

int eval_postfix(union token *stack, int in_stack_ptr, struct number *ret)
{
	int i, stack_ptr = STACK_SIZE - 1;
	for (i = 0; i < in_stack_ptr; i++) {
		if (stack[i].is_op && stack_ptr < STACK_SIZE - 2) {
			stack[i].op.calc(stack[stack_ptr+2].num.num, stack[stack_ptr+2].num.num, stack[stack_ptr+1].num.num, MPFR_RNDN);
			stack_ptr++;
			//mpfr_clear(a.num);
			//mpfr_clear(b.num);
		} else if (!stack[i].is_op)
			stack[stack_ptr--] = stack[i];
		else
			return -1;

	}
	*ret = stack[STACK_SIZE-1].num;
	return 0;
}
int eval_prefix(union token *stack, int in_stack_ptr, struct number *ret)
{
	int i, stack_ptr = STACK_SIZE - 1;
	for (i = in_stack_ptr - 1; i >= 0; i--) {
		if (stack[i].is_op && stack_ptr < STACK_SIZE - 2) {
/*			struct number a = stack[++stack_ptr].num;
			struct number b = stack[++stack_ptr].num;
			stack[stack_ptr--].num = stack[i].op.calc(a,b);
			mpfr_clear(a.num);
			mpfr_clear(b.num);*/
		} else if (!stack[i].is_op)
			stack[stack_ptr--] = stack[i];
		else
			return -1;
	}
	memcpy(ret, &stack[STACK_SIZE-1].num, sizeof(*ret));
	return 0;
}
int calculate(char *str, struct number *ret)
{
	union token stack[STACK_SIZE];
	int ptr = shunting_yard(str, stack);
	if (ptr == -1)
		return -1;
	return eval_postfix(stack, ptr, ret);
}

int get_type(const char *str)
{
	struct operator op;
	if (*str == '(')
		return LPARENS_TYPE;
	if (*str == ')')
		return RPARENS_TYPE;
	if (get_op(str, &op) == 0)
		return OP_TYPE;
	return NUM_TYPE;
}
int get_num(const char *str, struct number *num)
{
	int ret = mpfr_init_set_str(num->num, str, 0, MPFR_RNDN);
}
