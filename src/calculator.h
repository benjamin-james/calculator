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
	int assoc, prec;
	struct number (*calc)(struct number a, struct number b);
};

union token {
	bool is_op;
	struct operator op;
	struct number num;
};
enum assoc { NO_ASSOC, LEFT_ASSOC, RIGHT_ASSOC };
int calculate(char *str, struct number *ret);
int eval_prefix(union token *stack, int stack_ptr, struct number *ret);
int shunting_yard(char *s, union token *queue);
int get_type(const char *str);
int get_num(const char *tok, struct number *num);
#endif
