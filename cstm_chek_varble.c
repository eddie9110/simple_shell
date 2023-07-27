#include "main.h"

/**
 * cstm_verify_ifenv - a custom ftn that checks if user input is an envt variable
 * @hddr: head node of linked list
 * @uinpt: user input
 * @data: struct
 * Return: void
 */

void cstm_verify_ifenv(varble_lst **hddr, char *uinpt, cstmdata *data)
{
	int chr, jk, ko, gf;
	char **envtptr;

	envtptr = data->_environ;

	for (gf = 0; envtptr[gf]; gf++)
	{
		for (ko = 1, chr = 0; envtptr[gf][chr]; chr++)
		{
			if (envtptr[gf][chr] == '=')
			{
				jk = cstmstr_lgth(envtptr[gf] + chr + 1);
				add_varble_lst_node(hddr, ko, envtptr[gf] + chr + 1, jk);
				return;
			}

			if (uinpt[ko] == envtptr[gf][chr])
				ko++;
			else
				break;
		}
	}

	for (ko = 0; uinpt[ko]; ko++)
	{
		if (uinpt[ko] == ' ' || uinpt[ko] == '\t' || uinpt[ko] == ';' || uinpt[ko] == '\n')
			break;
	}

	add_varble_lst_node(hddr, ko, NULL, 0);
}

/**
 * cstm_chek_varble- a custom ftn to check if input is double $ or single $?
 * @hddr: head node of l list
 * @inptstr: user's stng input
 * @s_t: last status
 * @data: struct
 * Return: (oh)
 */

int cstm_chek_varble(varble_lst **hddr, char *inptstr, char *s_t, cstmdata *data)
{
	int lst, oh, lpd;

	lst = cstmstr_lgth(s_t);
	lpd = cstmstr_lgth(data->pid);

	for (oh = 0; inptstr[oh]; oh++)
	{
		if (inptstr[oh] == '$')
		{
			if (inptstr[oh + 1] == '?')
				add_varble_lst_node(hddr, 2, s_t, lst), oh++;

			else if (inptstr[oh + 1] == '$')
				add_varble_lst_node(hddr, 2, data->pid, lpd), oh++;
			else if (inptstr[oh + 1] == '\n')
				add_varble_lst_node(hddr, 0, NULL, 0);
			else if (inptstr[oh + 1] == '\0')
				add_varble_lst_node(hddr, 0, NULL, 0);
			else if (inptstr[oh + 1] == ' ')
				add_varble_lst_node(hddr, 0, NULL, 0);
			else if (inptstr[oh + 1] == '\t')
				add_varble_lst_node(hddr, 0, NULL, 0);
			else if (inptstr[oh + 1] == ';')
				add_varble_lst_node(hddr, 0, NULL, 0);

			else
				cstm_verify_ifenv(hddr, inptstr + oh, data);
		}
	}

	return (oh);
}

/**
 * cstm_new_input - a custom ftn to 
 * @hdrr: the head node of a l list
 * @inptstr: input string
 * @ninpt: new user inpt
 * @lgth: lgth of new user input 
 * Return: (ninpt)
 */

char *cstm_new_input(varble_lst **hddr, char *inptstr, char *ninpt, int lgth)
{
	int lm;
	varble_lst *no;
	int tr, ok;

	no = *hddr;

	for (tr = ok = 0; tr < lgth; tr++)
	{
		if (inptstr[ok] == '$')
		{
			if (!(no->vlulgth) && !(no->varlgnt))
			{
				ninpt[tr] = inptstr[ok];
				ok++;
			}
			else if (no->varlgnt && !(no->vlulgth))
			{
				for (lm = 0; lm < no->varlgnt; lm++)
					ok++;
				tr--;
			}

			else
			{
				for (lm = 0; lm < no->vlulgth; lm++)
				{
					ninpt[tr] = no->vlu[lm];
					tr++;
				}
				ok = ok + (no->varlgnt);
				tr--;
			}

			no = no->lnknxt;
		}
		else
		{
			ninpt[tr] = inptstr[ok];
			ok++;
		}
	}

	return (ninpt);
}

/**
 * cstm_replcr - a custom ftn that replaces
 * @inptstr: user's input stng
 * @dat: struct
 * Return: (ninpt)
 */

char *cstm_replcr(char *inptstr, cstmdata *dat)
{
	varble_lst *hddr, *no;
	char *stats, *ninpt;
	int lgth1, lgth;

	stats = cstmftn_itoa(dat->status);

	hddr = NULL;

	lgth1 = cstm_chek_varble(&hddr, inptstr, stats, dat);

	if (hddr == NULL)
	{
		free(stats);
		return (inptstr);
	}

	no = hddr;
	lgth = 0;

	while (no != NULL)
	{
		lgth += (no->vlulgth - no->varlgnt);
		no = no->lnknxt;
	}

	lgth = lgth + lgth1;

	ninpt = malloc(sizeof(char) * (lgth + 1));
	ninpt[lgth] = '\0';

	ninpt = cstm_new_input(&hddr, inptstr, ninpt, lgth);

	free(inptstr);
	free(stats);
	free_varble_lst(&hddr);

	return (ninpt);
}
