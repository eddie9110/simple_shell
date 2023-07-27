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
