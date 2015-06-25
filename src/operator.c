#include <mpfr.h>
#include <string.h>

#include "calculator.h"
#include "operator.h"

int get_op(const char *str, struct operator *op)
{
	op->is_op = 1;
	op->op = *str;
	op->assoc = LEFT_ASSOC;
	op->prec = 1;
	if (!strcmp(str, "+")) {
		op->prec = 1;
		op->calc = mpfr_add;
	} else if (!strcmp(str, "-")) {
		op->prec = 1;
		op->calc = mpfr_sub;
	} else if (!strcmp(str, "*")) {
		op->prec = 2;
		op->calc = mpfr_mul;
	} else if (!strcmp(str, "/")) {
		op->prec = 2;
		op->calc = mpfr_div;
	} else if (!strcmp(str, "^")) {
		op->assoc = RIGHT_ASSOC;
		op->prec = 3;
		op->calc = mpfr_pow;
	} else
		return -1;
	return 0;
}
