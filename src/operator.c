#include <mpfr.h>
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
		op->calc = mpfr_add;
		break;
	case '-':
		op->prec = 1;
		op->calc = mpfr_sub;
		break;
	case '*':
		op->prec = 2;
		op->calc = mpfr_mul;
		break;
	case '/':
		op->prec = 2;
		op->calc = mpfr_div;
		break;
	case '^':
		op->assoc = RIGHT_ASSOC;
		op->prec = 3;
		op->calc = mpfr_pow;
		break;
	default:
		return -1;
	}
	return 0;
}
