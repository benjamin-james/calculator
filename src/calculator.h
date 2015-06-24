#ifndef CALCULATOR_H
#define CALCULATOR_H

#define OP_TYPE 1
#define NUM_TYPE 2
#define LPARENS_TYPE 4
#define RPARENS_TYPE 8

#include <stdbool.h>

struct number {
	bool type;
	double num;
};

struct operator {
	bool type;
	char op;
	struct number (*calc)(struct number a, struct number b);
};

union token {
	bool type;
	struct operator op;
	struct number num;
};
int calculate(char *str, struct number *ret);

#endif
