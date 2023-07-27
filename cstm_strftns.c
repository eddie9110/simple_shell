#include "main.h"

/**
 * cstmstr_dup - a customised ftn to duplicate strings
 * @strng: parameter reps str of interest
 * Return: (cstptr) - duptd strng
 */

char* cstmstr_dup(const char* strng)
{
	char *cstptr;
	size_t len;

	len = cstmstr_lgth(strng);
	cstptr = malloc(sizeof(char) * (len + 1));
	if (cstptr == NULL)
		return (NULL);
	cstmftn_cpymem(cstptr, strng, len + 1);
	return (cstptr);
}

/**
 * cstmstr_lgth - a cstm ftn that gets string lgth
 * @strng: string of interest
 * Return: (0) - success / 1 - fail
 */

int cstmstr_lgth(const char *strng)
{
	int lgnt;

	for (lgnt = 0; strng[lgnt] != 0; lgnt++)
	{
	}
	return (lgnt);
}

/**
 * ftncharcmpr - a cstm ftn that compares string characters
 * @stng: parameter reps string of interest
 * @tokn: delimiter
 * Return: 1 if identical otherwise, 0
 */

int ftncharcmpr(char stng[], const char *tokn)
{
	unsigned int op, hl, dn;

	for (op = 0, dn = 0; stng[op]; op++)
	{
		for (hl = 0; tokn[hl]; hl++)
		{
			if (stng[op] == tokn[hl])
			{
				dn++;
				break;
			}
		}
	}
	if (op == dn)
		return (1);

	return (0);
}

/**
 * ftnstr_tokn - a cstm ftn that splits stng
 * @stng: parameter reps input string of interest.
 * @tokn: delim.
 * Return: string splited.
 */

char *ftnstr_tokn(char stng[], const char *tokn)
{
	unsigned int ls, bool;
	char *bgnstrn;
	static char *spt, *efstrn;
	

	if (stng != NULL)
	{
		if (ftncharcmpr(stng, tokn))
			return (NULL);
		spt = stng; 
		ls = cstmstr_lgth(stng);
		efstrn = &stng[ls]; 
	}

	bgnstrn = spt;

	if (bgnstrn == efstrn)
		return (NULL);

	for (bool = 0; *spt; spt++)
	{
		if (spt != bgnstrn)
			if (*spt && *(spt - 1) == '\0')
				break;
		for (ls = 0; tokn[ls]; ls++)
		{
			if (*spt == tokn[ls])
			{
				*spt = '\0';
				if (spt == bgnstrn)
					bgnstrn++;
				break;
			}
		}if (bool == 0 && *spt) /*when stng is not equal to tokn*/
			bool = 1;
	}
	if (bool == 0) /*when stng is equal to  tokn*/
		return (NULL);

	return (bgnstrn);
}

/**
 * ftnifdigt - a custom ftn that checks if str passed is a no.
 * @stn: parameter reps the stn of interest
 * Return: 1 - str is number / 0 otherwise
 */

int ftnifdigt(const char *stn)
{
	unsigned int jo;

	for (jo = 0; stn[jo]; jo++)
	{
		if (stn[jo] < 48 || stn[jo] > 57)
			return 0;
	}

	return 1;
}
