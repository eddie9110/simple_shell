#include "main.h"

/**
 * cstmftn_cpymem - a custom ftn that info into void pointers
 * @nptrr: dstn ptr
 * @pntrr: srce pointr
 * @cap: size of the new ptr
 * Return: void
 */

void cstmftn_cpymem(void *nptrr, const void *pntrr, unsigned int cap)
{
	char *cptr = (char *)pntrr;
	char *cnewptr = (char *)nptrr;
	unsigned int ld;

	for (ld = 0; ld < cap; ld++)
		cnewptr[ld] = cptr[ld];
}

/**
 * cstm_ftnrealloc - a custom realloc ftn
 * @pntrr: parameter reps ptr to the old space
 * @osze: size of the old allocated space
 * @nsze: parameter reps new size, in bytes
 * Return: ptr on success / NULL otherwise
 */

void *cstm_ftnrealloc(void *pntrr, unsigned int osze, unsigned int nsze)
{
	void *nptr;

	if (pntrr == NULL)
		return (malloc(nsze));

	if (nsze == 0)
	{
		free(pntrr);
		return (NULL);
	}

	if (nsze == osze)
		return (pntrr);

	nptr = malloc(nsze);

	if (nptr == NULL) /*error handling for malloc*/
		return (NULL);

	if (nsze < osze)
		cstmftn_cpymem(nptr, pntrr, nsze);
	else
		cstmftn_cpymem(nptr, pntrr, osze);

	free(pntrr);

	return (nptr);
}

/**
 * cstmftn_dprealloc - a custom ftn to reallocate memory block to a double ptr.
 * @pntrr: double pointer to the old space.
 * @ocap: sizeof old space`
 * @ncap: newly allocated space
 * Return: ptr - successful, otherwise NULL
 */

char **cstmftn_dprealloc(char **pntrr, unsigned int ocap, unsigned int ncap)
{
	char **nptrr;
	unsigned int pk;

	if (pntrr == NULL)
		return (malloc(sizeof(char *) * ncap));

	if (ncap == ocap)
		return (pntrr);

	nptrr = malloc(sizeof(char *) * ncap);

	if (nptrr == NULL)
		return (NULL);

	for (pk = 0; pk < ocap; pk++)
		nptrr[pk] = pntrr[pk];

	free(pntrr);

	return (nptrr);
}
