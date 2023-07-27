#include "main.h"

/**
 * cstmcd_drctry - a custom ftn that changes current directory
 * @dat: user's input
 * Return: 1
 */

int cstmcd_drctry(cstmdata *dat)
{
	int hmme;
	char *drctry;
	int hmmedir, hmmedir0;

	drctry = dat->args[1];

	if (drctry != NULL)
	{
		hmmedir = cstmftn_str_cmp("$HOME", drctry);
		hmmedir0 = cstmftn_str_cmp("~", drctry);
		hmme = cstmftn_str_cmp("--", drctry);
	}

	if (!hmmedir || !hmme || !hmmedir0 || drctry == NULL)
	{
		cstmcd_home(dat);
		return (1);
	}

	if (cstmftn_str_cmp("-", drctry) == 0)
	{
		cstmcd_prev(dat);
		return (1);
	}

	if (cstmftn_str_cmp("..", drctry) == 0 || cstmftn_str_cmp(".", drctry) == 0)
	{
		cd_parent_drctry(dat);
		return (1);
	}

	cstmcd(dat);

	return (1);
}
