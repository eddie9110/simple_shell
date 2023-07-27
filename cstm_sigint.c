#include "main.h"

/**
 * cstm_sigint - a cstm ftn to handle crtl + c signal
 * @sghndlr: parameter reps Signal handler
 */

void cstm_sigint(int sghndlr)
{
	(void)sghndlr;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
