#include "main.h"

/**
 * cstmrmve_comment - a custom ftn to remove comments from user's input
 * @inptstr: input str
 * Return: inptstr
 */

char *cstmrmve_comment(char *inptstr)
{
	int untl = 0;
	int od;

	for (od = 0; inptstr[od]; od++)
	{
		if (inptstr[od] == '#')
		{
			if (od == 0)
			{
				free(inptstr);
				return (NULL);
			}

			if (inptstr[od - 1] == '\t' || inptstr[od - 1] == ' '|| inptstr[od - 1] == ';')
				untl = od;
		}
	}

	if (untl != 0)
	{
		inptstr = cstm_ftnrealloc(inptstr, od, untl + 1);
		inptstr[untl] = '\0';
	}

	return (inptstr);
}

/**
 * sloop - a ftn that is the Loop of my shell
 * @dat: input data from user
 * Return: void
 */

void sloop(cstmdata *dat)
{
	int endf;
	int lp = 1;
	char *uinpt;

	while (lp == 1)
	{
		write(STDIN_FILENO, "$ ", 4);

		uinpt = cstm_readline(&endf);

		if (endf != -1)
		{
			uinpt = cstmrmve_comment(uinpt);

			if (uinpt == NULL)
				continue;

			if (cstm_chk_sntx_err(dat, uinpt) == 1)
			{
				dat->status = 2;
				free(uinpt);
				continue;
			}

			uinpt = cstm_replcr(uinpt, dat);
			lp = cstm_cmnd_splitter_ftn(dat, uinpt);

			dat->counter += 1;

			free(uinpt);
		}
		else
		{
			lp = 0;
			free(uinpt);
		}
	}
}
