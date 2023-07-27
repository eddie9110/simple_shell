#include "main.h"

/**
 * cstm_infocpy - a custom ftn that copys info to be created
 * @name: name of new env
 * @vale: value 
 * Return: (nptr)
 */

char *cstm_infocpy(char *name, char *vale)
{
	char *nptr;
	int nam, val, lgth;

	nam = cstmstr_lgth(name);
	val = cstmstr_lgth(vale);
	lgth = nam + val + 2;

	nptr = malloc(sizeof(char) * (lgth));

	cstmftn_str_cpy(nptr, name);
	cstmftn_str_cat(nptr, "=");
	cstmftn_str_cat(nptr, vale);
	cstmftn_str_cat(nptr, "\0");

	return (nptr);
}

/**
 * cstm_set_env - a custom ftn that sets an envt varble
 * @name: envt var name
 * @vale: envt var val
 * @dat: envt
 * Return: void
 */

void cstm_set_env(char *name, char *vale, cstmdata *dat)
{
	char *envrble, *namenv;
	int lm;

	for (lm = 0; dat->_environ[lm]; lm++)
	{
		envrble = cstmstr_dup(dat->_environ[lm]);
		namenv = ftnstr_tokn(envrble, "=");

		if (cstmftn_str_cmp(namenv, name) == 0)
		{
			free(dat->_environ[lm]);
			dat->_environ[lm] = cstm_infocpy(namenv, vale);
			free(envrble);
			return;
		}
		free(envrble);
	}

	dat->_environ = cstmftn_dprealloc(dat->_environ, lm, sizeof(char *) * (lm + 2));
	dat->_environ[lm] = cstm_infocpy(name, vale);
	dat->_environ[lm + 1] = NULL;
}

/**
 * cstmftn_setenv - a custom ftn that compares the names of 2 envt vars
 * @dat: data of interest
 * Return: 1 
 */

int cstmftn_setenv(cstmdata *dat)
{

	if (dat->args[1] == NULL || dat->args[2] == NULL)
	{
		cstm_error_fetcher(dat, -1);
		return (1);
	}

	cstm_set_env(dat->args[1], dat->args[2], dat);

	return (1);
}

/**
 * cstm_unset_env - a custom ftn that deletes an envt var
 * @dat: data to delete
 * Return: 1
 */

int cstm_unset_envt(cstmdata *dat)
{
	char **envptr;
	int gf, bw, dd;
	char *envrble, *namenv;

	if (dat->args[1] == NULL)
	{
		cstm_error_fetcher(dat, -1);
		return (1);
	}

	dd = -1;

	for (gf = 0; dat->_environ[gf]; gf++)
	{
		envrble = cstmstr_dup(dat->_environ[gf]);
		namenv = ftnstr_tokn(envrble, "=");
	
		if (cstmftn_str_cmp(namenv, dat->args[1]) == 0)
		{
			dd  = gf;
		}

		free(envrble);
	}

	if (dd == -1)
	{
		cstm_error_fetcher(dat, -1);
		return (1);
	}

	envptr = malloc(sizeof(char *) * (gf));

	for (gf = bw = 0; dat->_environ[gf]; gf++)
	{
		if (gf != dd)
		{
			envptr[bw] = dat->_environ[gf];
			bw++;
		}
	}
	envptr[bw] = NULL;
	free(dat->_environ[dd]);
	free(dat->_environ);
	dat->_environ = envptr;

	return (1);
}
