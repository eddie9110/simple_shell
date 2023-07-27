#include "main.h"

/**
 * cstmftnerr_env - err info for get_env
 * @dat: data relevant (counter, arguments)
 * Return: err
 */

char *cstmftnerr_env(cstmdata *dat)
{
	char *err, *og, *inf;
	int lgth;

	og = cstmftn_itoa(dat->counter);

	inf = ": can't add/remove from envt\n";

	lgth = cstmstr_lgth(dat->av[0]) + cstmstr_lgth(og);
	lgth = lgth + cstmstr_lgth(dat->args[0]) + cstmstr_lgth(inf) + 4;

	err = malloc(sizeof(char) * (lgth + 1));

	if (err == 0)
	{
		free(err);
		free(og);
	
		return (NULL);
	}

	cstmftn_str_cpy(err, dat->av[0]);
	cstmftn_str_cat(err, ": ");
	cstmftn_str_cat(err, og);
	cstmftn_str_cat(err, ": ");
	cstmftn_str_cat(err, dat->args[0]);
	cstmftn_str_cat(err, inf);
	cstmftn_str_cat(err, "\0");

	free(og);

	return (err);
}

/**
 * cstmftnerr_path - custom ftn for err message for denied permission.
 * @dat: user input
 * Return: err
 */

char *cstmftnerr_path(cstmdata *dat)
{
	char *og, *err;
	int lgth;

	og = cstmftn_itoa(dat->counter);
	lgth = cstmstr_lgth(dat->av[0]) + cstmstr_lgth(og);
	lgth = lgth + cstmstr_lgth(dat->args[0]) + 24;
	err = malloc(sizeof(char) * (lgth + 1));

	if (err == 0)
	{
		free(err);
		free(og);
		return (NULL);
	}

	cstmftn_str_cpy(err, dat->av[0]);
	cstmftn_str_cat(err, ": ");
	cstmftn_str_cat(err, og);
	cstmftn_str_cat(err, ": ");
	cstmftn_str_cat(err, dat->args[0]);
	cstmftn_str_cat(err, ": unauthorised access\n");
	cstmftn_str_cat(err, "\0");

	free(og);

	return (err);
}
