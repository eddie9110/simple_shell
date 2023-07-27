#include "main.h"

/**
 * cstmftn_str_cat - a custom ftn that concatenates strings
 * @dstn: parameter represents the destion of the string
 * @srce: source string
 * Return: dstn
 */

char* cstmftn_str_cat(char *dstn, const char *srce)
{
	int ko, pd = 0;

	for (ko = 0; dstn[ko] != '\0'; ko++)
		;

	for (pd = 0; srce[pd] != '\0'; pd++)
	{
		dstn[ko] = srce[pd];
		ko++;
	}

	dstn[ko] = '\0';
	return (dstn);
}

/**
 * cstmftn_str_cpy - a cstm ftn to copy string
 * @dstn: parameter reps a ptr to dest of str that was copied
 * @srce: parameter reps a ptr to string srce
 * Return: dstn
 */

char *cstmftn_str_cpy(char *dstn, char *srce)
{
	size_t tn;

	for (tn = 0; srce[tn] != '\0'; tn++)
	{
		dstn[tn] = srce[tn];
	}
	dstn[tn] = '\0';
	return (dstn);
}

/**
 * cstmftn_str_cmp - a custom ftn to compare strings.
 * @s1: first string of interest
 * @s2: second string of interest
 * Return: 0 - successful / 1 - otherwise
 */

int cstmftn_str_cmp(char *st0, char *st1)
{
	int eg;

	for (eg = 0; st0[eg] == st1[eg] && st0[eg]; eg++)
		;
	if (st0[eg] > st1[eg])
		return (1);
	if (st0[eg] < st1[eg])
		return (-1);

	return (0);
}
/**
 * cstmftn_str_loc - a custom ftn to find a char in a string
 * @s: string of interest
 * @c: character of interest
 * Return: location of the char
 */

char *cstmftn_str_loc(char *stng, char ch)
{
	unsigned int ke = 0;

	for (; *(stng + ke) != '\0'; ke++)
		if (*(stng + ke) == ch)
			return (stng + ke);

	if (*(stng + ke) == ch)
		return (stng + ke);

	return ('\0');
}

/**
 * cstmftn_str_pn - a custom ftn to find length of substring.
 * @stng: parameter reps the
 * @byts: bytes.
 * Return: (jo) no. of bytes
 */


int cstmftn_str_pn(char *stng, char *byts)
{
	int jo, hn;
	int bool;

	for (jo = 0; *(stng + jo) != '\0'; jo++)
	{
		bool = 1;
		for (hn = 0; *(byts + hn) != '\0'; hn++)
		{
			if (*(stng + jo) == *(byts + hn))
			{
				bool = 0;
				break;
			}
		}if (bool == 1)
			break;
	}
	return (jo);
}
