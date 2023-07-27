#include "main.h"

/**
 * cstmftn_addnode_end - a custom ftn that adds at the end of a sl list
 * @hddr: parameter reps the addrss of head node of linked list
 * @sptr: parameter reps separator
 * Return: the memory address of the hddr node
 */

cstm_s_llist *cstmftn_addnode_end(cstm_s_llist **hddr, char sptr)
{
	cstm_s_llist *nnode, *cstmptr;

	nnode = malloc(sizeof(cstm_s_llist));

	if (nnode == NULL) /*error  handling incase of malloc failure*/
		return (NULL);

	nnode->tok = sptr;
	nnode->lnknxt = NULL;
	cstmptr = *hddr;

	if (cstmptr == NULL)
	{
		*hddr = nnode;
	}
	else
	{
		while (cstmptr->lnknxt != NULL)
			cstmptr = cstmptr->lnknxt;
		cstmptr->lnknxt = nnode;
	}

	return (*hddr);
}

/**
 * free_s_llist - a custom ftn that frees a cstm_s_llist
 * @hddr: parameter reps the head node of linked list.
 * Return: void
 */

void free_s_llist(cstm_s_llist **hddr)
{
	cstm_s_llist *cstmptr;
	cstm_s_llist *tmp;

	if (hddr != NULL)
	{
		tmp = *hddr;

		while ((cstmptr = tmp) != NULL)
		{
			tmp = tmp->lnknxt;
			free(cstmptr);
		}

		*hddr = NULL;
	}
}

/**
 * cstm_add_node_end - custom ftn that adds node called cmmnd line at the end of cstm_s_list2.
 * @hddr: parameter reps the head of the linked list.
 * @lneinpt: commd line input.
 * Return: the memory address of the hddr node.
 */

cstm_s_list2 *cstm_add_node_end(cstm_s_list2 **hddr, char *lneinpt)
{
	cstm_s_list2 *nnode, *cstmptr;

	nnode = malloc(sizeof(cstm_s_list2));

	if (nnode == NULL) /*error handling in case malloc fails*/
		return (NULL);

	nnode->lneinpt = lneinpt;
	nnode->lnknxt = NULL;
	cstmptr = *hddr;

	if (cstmptr == NULL)
	{
		*hddr = nnode;
	}
	else
	{
		while (cstmptr->lnknxt != NULL)
			cstmptr = cstmptr->lnknxt;
		cstmptr->lnknxt = nnode;
	}

	return (*hddr);
}

/**
 * freecstm_s_list - a custom ftn that frees a cstm_s_list
 * @hddr: parameter reps the head node of a cstm_s_list2.
 * Return: void
 */

void freecstm_s_list(cstm_s_list2 **hddr)
{
	cstm_s_list2 *cstmptr;
	cstm_s_list2 *tmp;

	if (hddr != NULL)
	{
		tmp = *hddr;

		while ((cstmptr = tmp) != NULL)
		{
			tmp = tmp->lnknxt;
			free(cstmptr);
		}

		*hddr = NULL;
	}
}
