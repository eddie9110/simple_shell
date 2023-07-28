#include "main.h"

/**
 * cstmacqr_builtin - a ftn that is used to get the built-in cmds
 * @ucmds: user's input cmd
 * Return: fptr of the built-in commands
 */

int (*cstmacqr_builtin(char *ucmds))(cstmdata *)
{
	cstm_builtin cmds_builtins[] = {
		{ "env", cstm_retrieve_env },
		{ "exit", cstm_my_exit },
		{ "setenv", cstmftn_setenv },
		{ "unsetenv", cstm_unset_envt },
		{ "cd", cstmcd_drctry },
		{ NULL, NULL }
	};

	int mq;

	for (mq = 0; cmds_builtins[mq].cmnd; mq++)
	{
		if (cstmftn_str_cmp(cmds_builtins[mq].cmnd, ucmds) == 0)
			break;
	}

	return (cmds_builtins[mq].f);
}


/**
 * cstm_my_exit - a custom ftn to exit the simple shell
 * @dat: user's input
 * Return: 0 on success / 1 -failure
 */

int cstm_my_exit(cstmdata *dat)
{
	unsigned int stts;
	int stlgth;
	int no;
	int dgt;

	if (dat->args[1] != NULL)
	{
		stts = cstm_ftnatoi(dat->args[1]);
		dgt = ftnifdigt(dat->args[1]);
		stlgth = cstmstr_lgth(dat->args[1]);
		no = stts > (unsigned int)INT_MAX;

		if (!dgt || stlgth > 10 || no)
		{
			cstm_error_fetcher(dat, 2);
			dat->status = 2;
			return (1);
		}

		dat->status = (stts % 256);
	}

	return (0);
}



/**
 * cstm_sigint - a cstm ftn to handle crtl + c signal
 * @sghndlr: parameter reps Signal handler
 */

void cstm_sigint(int sghndlr)
{
	(void)sghndlr;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
