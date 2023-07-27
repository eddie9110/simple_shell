#include "main.h"

/**
 * cstm_checkifin_dir - a custom ftn that checks if file is in the current dir
 * @pth: pth
 * @iptr: int ptr
 * Return: 1 / 0
 */

int cstm_checkifin_dir(char *pth, int *iptr)
{
	if (pth[*iptr] == ':')
		return (1);

	while (pth[*iptr] != ':' && pth[*iptr])
	{
		*iptr += 1;
	}

	if (pth[*iptr])
		*iptr += 1;

	return (0);
}

/**
 * cstmfnd_cmd - a custom ftn to find a command
 * @cmd: cmd from user
 * @_environ: envt varble
 * Return: (cmd)
 */

char *cstmfnd_cmd(char *cmd, char **_environ)
{
	int drctylgth, cmdlgth;
	struct stat st;
	char *pth, *toknpth, *drcty, *ptrpth;
	int jd = 0;

	pth = cstmget_env("PATH", _environ);
	if (pth)
	{
		ptrpth = cstmstr_dup(pth);
		cmdlgth = cstmstr_lgth(cmd);
		toknpth = ftnstr_tokn(ptrpth, ":");

		while (toknpth != NULL)
		{
			if (cstm_checkifin_dir(pth, &jd))
				if (stat(cmd, &st) == 0)
					return (cmd);

			drctylgth = cstmstr_lgth(toknpth);
			drcty = malloc(drctylgth + cmdlgth + 2);
			cstmftn_str_cpy(drcty, toknpth);
			cstmftn_str_cat(drcty, "/");
			cstmftn_str_cat(drcty, cmd);
			cstmftn_str_cat(drcty, "\0");

			if (stat(drcty, &st) == 0)
			{
				free(ptrpth);
				return (drcty);
			}

			free(drcty);

			toknpth = ftnstr_tokn(NULL, ":");
		}

		free(ptrpth);
/* */
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}

	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);

	return (NULL);
}

/**
 * cstm_checkif_executable - a custom ftn to determine if cmd is an executable type
 * @dat: struct
 * Return: 0 - execable, otherwise 1
 */

int cstm_checkif_executable(cstmdata *dat)
{
	struct stat st;
	int kd;
	char *input;

	input = dat->args[0];

	for (kd = 0; input[kd]; kd++)
	{
		if (input[kd] == '.')
		{
			if (input[kd + 1] == '.')
				return (0);
			if (input[kd + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[kd] == '/' && kd != 0)
		{
			if (input[kd + 1] == '.')
				continue;
			kd++;
			break;
		}
		else
			break;
	}

	if (kd == 0)
		return (0);

	if (stat(input + kd, &st) == 0)
	{
		return (kd);
	}
	cstm_error_fetcher(dat, 127);

	return (-1);
}

/**
 * cstm_checkpermiss - a custom ftn that checks the permissions available to a particular user
 * @drctry: dest dirtory
 * @dat: strust
 * Return: 0 success / 1 otherwise
 */

int cstm_checkpermiss(char *drctry, cstmdata *dat)
{
	if (drctry == NULL)
	{
		cstm_error_fetcher(dat, 127);
		return (1);
	}

	if (cstmftn_str_cmp(dat->args[0], drctry) != 0)
	{
		if (access(drctry, X_OK) == -1)
		{
			cstm_error_fetcher(dat, 126);
			free(drctry);
			return (1);
		}

		free(drctry);
	}
	else
	{
		if (access(dat->args[0], X_OK) == -1)
		{
			cstm_error_fetcher(dat, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * cstm_executer_ftn - a custom made ftn to execute commands from user
 * @dat: user's input
 * Return: 1 on success.
 */

int cstm_executer_ftn(cstmdata *dat)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int ec;
	char *drctry;
	(void) wpd;

	ec = cstm_checkif_executable(dat);

	if (ec == -1)
		return (1);
	if (ec == 0)
	{
		drctry = cstmfnd_cmd(dat->args[0], dat->_environ);
		if (cstm_checkpermiss(drctry, dat) == 1)
			return (1);
	}

	pd = fork();

	if (pd == 0)
	{
		if (ec == 0)
			drctry = cstmfnd_cmd(dat->args[0], dat->_environ);
		else
			drctry = dat->args[0];
		execve(drctry + ec, dat->args, dat->_environ);
	}
	else if (pd < 0)
	{
		perror(dat->av[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	dat->status = state / 256;
	return (1);
}

