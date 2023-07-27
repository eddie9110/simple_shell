#include "main.h"

/**
 * cstmrept_cntr - a custom ftn that counts intances of a char
 * @uipt: user input
 * @he: indx
 * Return: (he) - no. of instances
 */

int cstmrept_cntr(char *uipt, int he)
{
	if (*(uipt - 1) == *uipt)
		return (cstmrept_cntr(uipt - 1, he + 1));

	return (he);
}

/**
 * cstm_get_syntx_err - a custom ftn that gets syntx errors
 * @input: user input
 * @jo: indx
 * @lt: parameter reps
 * Return: index of error. 0 - no error
 */

int cstm_get_syntx_err(char *uipt, int jo, char lt)
{
	int cntt = 0;

	if (*uipt == '\0')
		return (0);

	if (*uipt == '\t' || *uipt == ' ')
		return (cstm_get_syntx_err(uipt + 1, jo + 1, lt));

	if (*uipt == ';')
		if (lt == '&' ||  lt == ';' || lt == '|')
			return (jo);

	if (*uipt == '|')
	{
		if (lt == ';' || lt == '&')
			return (jo);

		if (lt == '|')
		{
			cntt = cstmrept_cntr(uipt, 0);
			if (cntt == 0 || cntt > 1)
				return (jo);
		}
	}

	if (*uipt == '&')
	{
		if (lt == ';' || lt == '|')
			return (jo);

		if (lt == '&')
		{
			cntt = cstmrept_cntr(uipt, 0);
			if (cntt == 0 || cntt > 1)
				return (jo);
		}
	}

	return (cstm_get_syntx_err(uipt + 1, jo + 1, *uipt));
}

/**
 * cstmfst_ch - a custom ftn that gets the index of the first char in user's input string
 * @input: user's input
 * @ke: parameter reps
 * Return: 0 - success / 1 fail
 */

int cstmfst_ch(char *uipt, int *ke)
{

	for (*ke = 0; uipt[*ke]; *ke += 1)
	{
		if (uipt[*ke] == ' ' || uipt[*ke] == '\t')
			continue;

		if (uipt[*ke] == ';' || uipt[*ke] == '|' || uipt[*ke] == '&')
			return (-1);
		break;
	}

	return (0);
}

/**
 * cstmopt_syntx_err - cstm ftn print a syntax err
 * @dat: struct
 * @uipt: uipt string
 * @i: parameter reps
 * @bool: true / false
 * Return: void
 */

void cstmopt_syntx_err(cstmdata *dat, char *uipt, int se, int bool)
{
	char * err0, *mptrg, *mptr1g, *mptr2g;
	int lgth;
	char *cnttr;

	if (uipt[se] == ';')
	{
		if (bool == 0)
			mptrg = (uipt[se + 1] == ';' ? ";;" : ";");
		else
			mptrg = (uipt[se - 1] == ';' ? ";;" : ";");
	}

	if (uipt[se] == '|')
		mptrg = (uipt[se + 1] == '|' ? "||" : "|");

	if (uipt[se] == '&')
		mptrg = (uipt[se + 1] == '&' ? "&&" : "&");

	mptr1g = ": error in syn : \"";
	mptr2g = "\" error\n";

	cnttr = cstmftn_itoa(dat->counter);
	lgth = cstmstr_lgth(dat->av[0]) + cstmstr_lgth(cnttr);
	lgth = lgth + cstmstr_lgth(mptrg) + cstmstr_lgth(mptr1g) + cstmstr_lgth(mptr2g) + 2;

	err0 = malloc(sizeof(char) * (lgth + 1));

	if (err0 == 0)
	{
		free(cnttr);
		return;
	}
	cstmftn_str_cpy(err0, dat->av[0]);
	cstmftn_str_cat(err0, ": ");
	cstmftn_str_cat(err0, cnttr);
	cstmftn_str_cat(err0, mptr1g);
	cstmftn_str_cat(err0, mptrg);
	cstmftn_str_cat(err0, mptr2g);
	cstmftn_str_cat(err0, "\0");

	write(STDERR_FILENO, err0, lgth);
	free(err0);
	free(cnttr);
}

/**
 * cstm_chk_sntx_err - a custom ftn that check for syntax error ina user's input and prints it
 * @dat: struct
 * @uipt: uipt string
 * Return: 0 - success / 1 - fail
 */

int cstm_chk_sntx_err(cstmdata *dat, char *uipt)
{
	int fst, fst1 = 0;
	int jx = 0;

	fst1 = cstmfst_ch(uipt, &fst);

	if (fst1 == -1)
	{
		cstmopt_syntx_err(dat, uipt, fst, 0);
		return (1);
	}

	jx = cstm_get_syntx_err(uipt + fst, 0, *(uipt + fst));

	if (jx != 0)
	{
		cstmopt_syntx_err(dat, uipt, fst + jx, 1);
		return (1);
	}

	return (0);
}
