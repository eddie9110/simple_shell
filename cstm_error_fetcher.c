#include "main.h"

/**
 * cstm_error_fetcher - a ftn that gets the correct type of error
 * @dat: data structure that contains arguments
 * @eval: error value
 * Return: error (eval)
 */

int cstm_error_fetcher(cstmdata *dat, int eval)
{
	char *err0;

	switch (eval)
	{
		case -1:
			err0 = cstmftnerr_env(dat);
			break;
		case 126:
			err0 = cstmftnerr_path(dat);
			break;
		case 127:
			err0 = cstmftnerrnot_found(dat);
			break;
		case 2:
			if (cstmftn_str_cmp("exit", dat->args[0]) == 0)
			err0 = cstmftnerrext_shell(dat);
			else if (cstmftn_str_cmp("cd", dat->args[0]) == 0)
			err0 = cstmftnerr_getcd(dat);
			break;
	}

	if (err0)
	{
		write(STDERR_FILENO, err0, cstmstr_lgth(err0));
		free(err0);
	}

	dat->status = eval;
	return (eval);
}
