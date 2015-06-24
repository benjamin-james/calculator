#include <stdlib.h>
#include <string.h>

#include "calculator.h"

enum assoc { NO_ASSOC, LEFT_ASSOC, RIGHT_ASSOC };
/* returns the stack pointer */
int shunting_yard(char *s, union token *queue)
{
	int stack_ptr = 0, queue_ptr = 0;
	struct operator stack[STACK_SIZE];
	const char *skip = "\t\n\r\f ";
	char *tok;
	int paren_mask = 0;
#define push(a) { stack[stack_ptr++] = a; }
#define pop() { stack[--stack_ptr]; }
#define qpush(a) { queue[queue_ptr++] = a; }
	for (tok = strtok(s, skip); tok; tok = strtok(NULL, skip)) {
		union token temp;
		int type = get_type(tok);
		switch (type) {
		case OP_TYPE:
			temp.is_op = 1;
			get_op(tok, &temp.op);
			temp.op.prec += paren_mask;
			while (stack_ptr > 0) {
				struct operator *t = stack + stack_ptr - 1;
				if (!(t->prec == temp.op.prec && t->assoc == LEFT_ASSOC) && t->prec <= temp.op.prec)
					break;
				queue[queue_ptr].is_op = 1;
				queue[queue_ptr++].op = stack[--stack_ptr];
			}
			push(temp.op);
			break;
		case NUM_TYPE:
			temp.is_op = 0;
			get_num(tok, &temp.num);
			qpush(temp);
			break;
		case LPARENS_TYPE:
			paren_mask += 10;
			break;
		case RPARENS_TYPE:
			paren_mask -= 10;
			break;
		}
	}
#undef qpush
#undef pop
#undef push
	return queue_ptr;
}

int eval_prefix(union token *stack, int in_stack_ptr, struct number *ret)
{
	int i, stack_ptr = STACK_SIZE - 1;
	for (i = in_stack_ptr - 1; i >= 0; i--) {
		if (stack[i].is_op && stack_ptr < STACK_SIZE - 2) {
			struct number a = stack[++stack_ptr].num;
			struct number b = stack[++stack_ptr].num;
			stack[stack_ptr--].num = stack[i].op.calc(a,b);
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
	return eval_prefix(stack, ptr, ret);
}

int get_type(const char *str)
{
	char *c;
	double num;
	if (*str == '(')
		return LPARENS_TYPE;
	if (*str == ')')
		return RPARENS_TYPE;
	num = strtod(str, &c);
	if (c > str)
		return NUM_TYPE;
	return OP_TYPE;
}
int get_op(const char *str, struct operator *op)
{
	return 0;
}
int get_num(const char *str, struct number *num)
{
	char *c;
	num->num = strtod(str, &c);
	return (c > str) - 1;
}
