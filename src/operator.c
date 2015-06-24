#include <math.h>

#include "calculator.h"
#include "operator.h"

int get_op(const char *str, struct operator *op)
{
	op->is_op = 1;
	op->op = *str;
	op->assoc = LEFT_ASSOC;
	op->prec = 1;
	switch (*str) {
	case '+':
		op->prec = 1;
		op->calc = add;
		break;
	case '-':
		op->prec = 1;
		op->calc = subtract;
		break;
	case '*':
		op->prec = 2;
		op->calc = multiply;
		break;
	case '/':
		op->prec = 2;
		op->calc = divide;
		break;
	case '^':
		op->assoc = RIGHT_ASSOC;
		op->prec = 3;
		op->calc = power;
		break;
	default:
		return -1;
	}
	return 0;
}

struct number add(struct number a, struct number b)
{
	struct number ret;
	ret.num = a.num + b.num;
	return ret;
}

struct number subtract(struct number a, struct number b)
{
	struct number ret;
	ret.num = b.num - a.num;
	return ret;
}

struct number multiply(struct number a, struct number b)
{
	struct number ret;
	ret.num = a.num * b.num;
	return ret;
}

struct number divide(struct number a, struct number b)
{
	struct number ret;
	ret.num = b.num / a.num;
	return ret;
}

struct number power(struct number a, struct number b)
{
	struct number ret;
	ret.num = pow(b.num, a.num);
	return ret;
}



