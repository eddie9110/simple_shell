#include "main.h"

/**
 * cstm_my_exit - a custom ftn to exit the simple shell
 * @dat: user's input
 * Return: 0 on success.
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
