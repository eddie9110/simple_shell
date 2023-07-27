#include "main.h"

/**
 * cstmcmpr_envnam - a custom ftn that compares env variables names with the name passed.
 * @envt: name of the environment variable
 * @envnam: envt name passed
 * Return: 0 if are not equal. Another value if they are.
 */

int cstmcmpr_envnam(const char *envt, const char *envnam)
{
	int ok;

	for (ok = 0; envt[ok] != '='; ok++)
	{
		if (envt[ok] != envnam[ok])
		{
			return (0);
		}
	}

	return (ok + 1);
}

/**
 * cstmget_env - a custom ftn that acquires an environment variable
 * @envnam: name of the envt variable
 * @_environ: envt variable
 * Return: (envptr + pt)
 */

char *cstmget_env(const char *envnam, char **_environ)
{
	char *envptr;
	int oh, pt;

	envptr = NULL;
	pt = 0;
	
	for (oh = 0; _environ[oh]; oh++)
	{
		pt = cstmcmpr_envnam(_environ[oh], envnam);

		if (pt)
		{
			envptr = _environ[oh];
			break;
		}
	}

	return (envptr + pt);
}

/**
 * cstm_retrieve_env - a custom ftn that retrieves the evironment variables and prints them
 * @dat: info from user
 * Return: 1 on success / otherwise fail
 */

int cstm_retrieve_env(cstmdata *dat)
{
	int ok, rf;

	for (ok = 0; dat->_environ[ok]; ok++)
	{

		for (rf = 0; dat->_environ[ok][rf]; rf++)
			;

		write(STDOUT_FILENO, dat->_environ[ok], rf);
		write(STDOUT_FILENO, "\n", 1);
	}
	dat->status = 0;

	return (1);
}
