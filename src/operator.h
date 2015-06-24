#ifndef OPERATOR_H
#define OPERATOR_H

#include "calculator.h"

int get_op(const char *tok, struct operator *op);

struct number add(struct number a, struct number b);
struct number subtract(struct number a, struct number b);
struct number multiply(struct number a, struct number b);
struct number divide(struct number a, struct number b);
struct number power(struct number a, struct number b);

#endif
