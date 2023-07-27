#include "main.h"

/**
 * cstmftn_str_cat_cd - function that concatenates the message for cd error
 * @dat: data from user
 * @inf: feedback to user
 * @err: parameter reps output error message
 * @og: parameter reps 
 * Return: err info
 */

char *cstmftn_str_cat_cd(cstmdata *dat, char *inf, char *err, char *og)
{
	char *uknown;

	cstmftn_str_cpy(err, dat->av[0]);
	cstmftn_str_cat(err, ": ");
	cstmftn_str_cat(err, og);
	cstmftn_str_cat(err, ": ");
	cstmftn_str_cat(err, dat->args[0]);
	cstmftn_str_cat(err, inf);


	if (dat->args[1][0] == '-')
	{
		uknown = malloc(3);
		uknown[0] = '-';
		uknown[1] = dat->args[1][1];
		uknown[2] = '\0';
		cstmftn_str_cat(err, uknown);
	
		free(uknown);
	}else
	{
		cstmftn_str_cat(err, dat->args[1]);
	}

	cstmftn_str_cat(err, "\n");
	cstmftn_str_cat(err, "\0");

	return (err);
}

/**
 * cstmftnerr_getcd - custom ftn to output error message for cd
 * @dat: user input
 * Return: Err info
 */

char *cstmftnerr_getcd(cstmdata *dat)
{
	int lgth;
	char *err, *inf, *og;
	int idlgth;

	og = cstmftn_itoa(dat->counter);

	if (dat->args[1][0] == '-')
	{
		inf = ":action not legal ";
		idlgth = 2;
	}
	else
	{
		inf = ":can't cd ";
		idlgth = cstmstr_lgth(dat->args[1]);
	}

	lgth = cstmstr_lgth(dat->av[0]) + cstmstr_lgth(dat->args[0]);
	lgth += cstmstr_lgth(og) + cstmstr_lgth(inf) + idlgth + 5;
	err = malloc(sizeof(char) * (lgth + 1));

	if (err == 0)
	{
		free(og);
		return (NULL);
	}

	err = cstmftn_str_cat_cd(dat, inf, err, og);

	free(og);

	return (err);
}

/**
 * cstmftnerrnot_found - a custom ftn that generates command not found
 * @dat: parameter represents user's input
 * Return: Err info
 */

char *cstmftnerrnot_found(cstmdata *dat)
{
	int lgth;
	char *err;
	char *og;

	og = cstmftn_itoa(dat->counter);

	lgth = cstmstr_lgth(dat->av[0]) + cstmstr_lgth(og);
	lgth = lgth + cstmstr_lgth(dat->args[0]) + 16;

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
	cstmftn_str_cat(err, ": unfound\n");
	cstmftn_str_cat(err, "\0");

	free(og);

	return (err);
}

/**
 * cstmftnerrext_shell - a custom ftn that generates error msge for exit
 * @dat: parameter reps users input
 * Return: err message
 */

char *cstmftnerrext_shell(cstmdata *dat)
{
	int lgth;
	char *err;
	char *og;

	og = cstmftn_itoa(dat->counter);

	lgth = cstmstr_lgth(dat->av[0]) + cstmstr_lgth(og);
	lgth += cstmstr_lgth(dat->args[0]) + cstmstr_lgth(dat->args[1]) + 23;

	err = malloc(sizeof(char) * (lgth + 1));

	if (err == 0)
	{
		free(og);
		return (NULL);
	}

	cstmftn_str_cpy(err, dat->av[0]);
	cstmftn_str_cat(err, ": ");
	cstmftn_str_cat(err, og);
	cstmftn_str_cat(err, ": ");
	cstmftn_str_cat(err, dat->args[0]);
	cstmftn_str_cat(err, ": no. doesn't exist: ");
	cstmftn_str_cat(err, dat->args[1]);
	cstmftn_str_cat(err, "\n\0");

	free(og);

	return (err);
}
