#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "calculator.h"
#include "operator.h"

int main(void)
{
	struct number n;
	char *input, buffer[256];
	rl_bind_key('\t', rl_complete);
	while (1) {
		snprintf(buffer, sizeof(buffer), ">");
		input = readline(buffer);
		if (!input || !strcmp(input, "exit"))
			break;
		add_history(input);
		calculate(input, &n);
//		snprintf(buffer, sizeof(buffer), "%%.%ldRf\n", mpfr_get_prec(n.num));
		mpfr_printf("%RNf\n", n.num);
		mpfr_clear(n.num);
		free(input);
	}
	return 0;
}
