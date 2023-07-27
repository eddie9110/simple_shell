#include "main.h"

/**
 * cstm_getlgnt - custom ftn that returns the no. lgnt
 * @no: parameter reps an integer
 * Return: lngt
 */

int cstmftn_getlgnt(int no)
{
	int lngt = 1;
	unsigned int num0;

	if (no < 0)
	{
		lngt++;
		num0 = no * -1;
	}
	else
	{
		num0 = no;
	}while (num0 > 9)
	{
		lngt++;  /*incrementing the value stored in lgnt to eventually get the length*/
		num0 = num0 / 10;
	}

	return (lngt);
}

/**
 * cstmftn_itoa - a cstm ftn that converts an integer to a string.
 * @nmbr: parameter reps integer of interest
 * Return: (stng)
 */

char *cstmftn_itoa(int nmbr)
{
	unsigned int no;
	int lngt = cstmftn_getlgnt(nmbr);
	char *stng;

	stng = malloc(sizeof(char) * (lngt + 1));
	if (stng == 0)
		return (NULL);

	*(stng + lngt) = '\0';

	if (nmbr < 0)
	{
		no = nmbr * -1;
		stng[0] = '-';
	}
	else
	{
		no = nmbr;
	}

	lngt--;

	do {
		*(stng + lngt) = (no % 10) + '0';
		no = no / 10;
		lngt--;
	}
	while (no > 0);

	return (stng);
}

/**
 * cstm_ftnatoi - a custom ftn to convert a string to an integer (atoi)
 * @stng: parameter reps the string of interest
 * Return: integer (jj*xv)
 */

int cstm_ftnatoi(char *stng)
{
	unsigned int cnt, cap, jj = 0;
	unsigned int xv = 1, ok = 1, ax;

	while (*(stng + cnt) != '\0')
	{
		if (cap > 0 && (*(stng + cnt) < '0' || *(stng + cnt) > '9'))
			break;

		if (*(stng + cnt) == '-')
			xv *= -1;

		if ((*(stng + cnt) >= '0') && (*(stng + cnt) <= '9'))
		{
			if (cap > 0)
				ok *= 10;
			cap++;
		}

		cnt++;
	}

	for (ax = cnt - cap; ax < cnt; ax++)
	{
		jj = jj + ((*(stng + ax) - 48) * ok);
		ok /= 10;
	}

	return (jj * xv);
}
