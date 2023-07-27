#include "main.h"

/**
 * cstm_readline - a ftn that reads the user's input
 * @endf: user's input
 * Return: input string
 */

char *cstm_readline(int *endf)
{
	size_t bufrr = 0;
	char *ipt = NULL;


	*endf = getline(&ipt, &bufrr, stdin);

	return (ipt);
}
