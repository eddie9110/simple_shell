#include "main.h"

/**
 * add_varble_lst_node - a csto ftn that adds variable node at end of linked list
 * @hddr: the head node of the varble_lst linked list.
 * @varlgnt: variable length
 * @vlu: user input value
 * @vlulgth: value length
 * Return: hddr address
 */

varble_lst *add_varble_lst_node(varble_lst **hddr, int varlgnt, char *vlu, int vlulgth)
{
	varble_lst *nptr, *tmpo;

	nptr = malloc(sizeof(varble_lst));

	if (nptr == NULL) /*error handling if malloc fails*/
		return (NULL);

	nptr->varlgnt = varlgnt;
	nptr->vlu = vlu;
	nptr->vlulgth = vlulgth;

	nptr->lnknxt = NULL;
	tmpo = *hddr;

	if (tmpo == NULL)
	{
		*hddr = nptr;
	}
	else
	{
		while (tmpo->lnknxt != NULL)
			tmpo = tmpo->lnknxt;
		tmpo->lnknxt = nptr;
	}

	return (*hddr);
}

/**
 * free_varble_lst - a custom ftn that frees a varble_lst linked list
 * @hddr: parameter reps the head node of the linked list.
 * Return: void
 */

void free_varble_lst(varble_lst **hddr)
{
	varble_lst *tmpo;
	varble_lst *ptr;

	if (hddr != NULL)
	{
		ptr = *hddr;

		while ((tmpo = ptr) != NULL)
		{
			ptr = ptr->lnknxt;
			free(tmpo);
		}

		*hddr = NULL;
	}
}
