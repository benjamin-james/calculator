#ifndef CALCULATOR_H
#define CALCULATOR_H

#define OP_TYPE 1
#define NUM_TYPE 2
#define LPARENS_TYPE 4
#define RPARENS_TYPE 8

#include <stdbool.h>

#define STACK_SIZE 256
struct number {
	bool is_op;
	double num;
};

struct operator {
	bool is_op;
	char op;
	struct number (*calc)(struct number a, struct number b);
};

union token {
	bool is_op;
	struct operator op;
	struct number num;
};
int calculate(char *str, struct number *ret);
struct number eval_prefix(union token *in_stack, int in_stack_ptr);
#endif
