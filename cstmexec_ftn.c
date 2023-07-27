#include "main.h"

/**
 * cstmexec_ftn - a custom ftn to search built-in cmds
 * @dat: user data input
 * Return: (1)
 */

int cstmexec_ftn(cstmdata *dat)
{
	int (*builtin)(cstmdata *dat);

	if (dat->args[0] == NULL)
		return (1);

	builtin = cstmacqr_builtin(dat->args[0]);

	if (builtin != NULL)
		return (builtin(dat));

	return (cstm_executer_ftn(dat));
}
