#include <stdio.h>
#include <string.h>

#include "calculator.h"
#include "operator.h"

int main(int argc, char **argv)
{
	union token stack[STACK_SIZE];
	int ptr = 0;
	struct number n;
	char buffer[256];
	if (argc < 2)
		return -1;
	strcpy(buffer, argv[1]);
	calculate(buffer, &n);
	printf("%f\n", n.num);
	return 0;
}
