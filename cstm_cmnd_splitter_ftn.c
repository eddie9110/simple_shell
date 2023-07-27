#include "main.h"

/**
 * cstm_swapp_ftn - a custom ftn that swaps characters
 * @inpt: inpt string
 * @bool: true or false
 * Return: (inpt stng)
 */

char *cstm_swapp_ftn(char *inpt, int bool)
{
	int kg;

	if (bool == 0)
	{
		for (kg = 0; inpt[kg]; kg++)
		{
			if (inpt[kg] == '|')
			{
				if (inpt[kg + 1] != '|')
					inpt[kg] = 16;
				else
					kg++;
			}
/* the inpt is checked for */
			if (inpt[kg] == '&')
			{
				if (inpt[kg + 1] != '&')
					inpt[kg] = 12;
				else
					kg++;
			}
		}
	}
	else
	{
		for (kg = 0; inpt[kg]; kg++)
		{
			inpt[kg] = (inpt[kg] == 16 ? '|' : inpt[kg]);
			inpt[kg] = (inpt[kg] == 12 ? '&' : inpt[kg]);
		}
	}
	return (inpt);
}

/**
 * cstm_ad_node - a custom ftn that adds septrs
 * @hddrs: head node of separator s list
 * @hddrlst: head node of command lines s list
 * @inpt: strng inpt
 * Return: no return
 */

void cstm_ad_node(cstm_s_llist **hddrs, cstm_s_list2 **hddrlst, char *inpt)
{
	char *in;
	int oj;
	
	inpt = cstm_swapp_ftn(inpt, 0);

	for (oj = 0; inpt[oj]; oj++)
	{
		if (inpt[oj] == ';')
			cstmftn_addnode_end(hddrs, inpt[oj]);

		if (inpt[oj] == '|' || inpt[oj] == '&')
		{
			cstmftn_addnode_end(hddrs, inpt[oj]);
			oj++;
		}
	}

	in = ftnstr_tokn(inpt, ";|&");

	do {
		in = cstm_swapp_ftn(in, 1);
		cstm_add_node_end(hddrlst, in);
		in = ftnstr_tokn(NULL, ";|&");
	} while (in != NULL);

}

/**
 * cstm_nxt_cmd - custom ftn that looks for the next cmd in line
 * @lstptr: separator list
 * @lst: command line list
 * @dat: struct
 * Return: void
 */

void cstm_nxt_cmd(cstm_s_llist **lstptr, cstm_s_list2 **lst, cstmdata *dat)
{
	cstm_s_llist *ptr = *lstptr;
	int sptr = 1;
	cstm_s_list2 *lstptr1 = *lst;

	while (ptr != NULL && sptr)
	{
		if (dat->status == 0)
		{
			if (ptr->tok == '&' || ptr->tok == ';')
				sptr = 0;
			if (ptr->tok == '|')
				lstptr1 = lstptr1->lnknxt, ptr = ptr->lnknxt;
		}

		else
		{
			if (ptr->tok == '|' || ptr->tok == ';')
				sptr = 0;

			if (ptr->tok == '&')
				lstptr1 = lstptr1->lnknxt, ptr = ptr->lnknxt;
		}
	
		if (ptr != NULL && !sptr)
			ptr = ptr->lnknxt;
	}

	*lstptr = ptr;
	*lst = lstptr1;
}

/**
 * cstm_cmnd_splitter_ftn - a custom ftn to parse cmnds using the separators
 * @dat: data structure
 * @inpt: inpt string
 * Return: 0 or 1
 */

int cstm_cmnd_splitter_ftn(cstmdata *dat, char *inpt)
{

	cstm_s_llist *hddrs, *lstptr;
	cstm_s_list2 *hddrlst, *lst;
	int lp;

	hddrs = NULL;
	hddrlst = NULL;

	cstm_ad_node(&hddrs, &hddrlst, inpt);

	lstptr = hddrs;
	lst = hddrlst;

	while (lst != NULL)
	{
		dat->input = lst->lneinpt;
		dat->args = cstm_tkn_ftn(dat->input);
		lp = cstmexec_ftn(dat);
		free(dat->args);

		if (lp == 0)
			break;

		cstm_nxt_cmd(&lstptr, &lst, dat);

		if (lst != NULL)
			lst = lst->lnknxt;
	}

	free_s_llist(&hddrs);

	freecstm_s_list(&hddrlst);

	if (lp == 0)
		return (0);

	return (1);
}

/**
 * cstm_tkn_ftn - a custom ftn to tokenise the inpt stng
 * @inpt: inpt stng
 * Return: tokenised string
 */

char **cstm_tkn_ftn(char *inpt)
{
	char **tokns;
	size_t jj;
	char *tok;
	size_t yg;
	
	jj = TOK_BUFSIZE;

	tokns = malloc(sizeof(char *) * (jj));
	if (tokns == NULL)
	{
		write(STDERR_FILENO, ":error in allocating\n", 18);
		exit(EXIT_FAILURE);
	}

	tok = ftnstr_tokn(inpt, TOK_DELIM);

	tokns[0] = tok;

	for (yg = 1; tok != NULL; yg++)
	{
		if (yg == jj)
		{
			jj = jj + TOK_BUFSIZE;
			tokns = cstmftn_dprealloc(tokns, yg, sizeof(char *) * jj);
			if (tokns == NULL)
			{
				write(STDERR_FILENO, ":error in allocating\n", 18);
				exit(EXIT_FAILURE);
			}
		}

		tok = ftnstr_tokn(NULL, TOK_DELIM);

		tokns[yg] = tok;
	}

	return (tokns);
}
