#include "main.h"

/**
 * cstmac_line - a custm ftn that assigns 
 * @lpt: space to store user's input
 * @buf: parameter reps
 * @nptr: size of lne
 * @om: size of buf
 */

void cstmac_line(char **lpt, size_t *nptr, char *buf, size_t om)
{

	if (*lpt == NULL)
	{
		if  (om > BUFSIZE)
			*nptr = om;

		else
			*nptr = BUFSIZE;
		*lpt = buf;
	}
	else if (*nptr < om)
	{
		if (om > BUFSIZE)
			*nptr = om;
		else
			*nptr = BUFSIZE;
		*lpt = buf;
	}
	else
	{
		cstmftn_str_cpy(*lpt, buf);
		free(buf);
	}
}

/**
 * cstm_getline - a custom ftn to read user's input
 * @lpt: space to store user's input
 * @nptr: lpt's size
 * @stm: space to read from
 * Return: (byts)
 */

ssize_t cstm_getline(char **lpt, size_t *nptr, FILE *stm)
{
	static ssize_t uinpt;
	int hb;
	char *buf;
	char ws = 'z';
	ssize_t byts;

	if (uinpt == 0)
		fflush(stm);
	else
		return (-1);

	uinpt = 0;

	buf = malloc(sizeof(char) * BUFSIZE);

	if (buf == NULL) /*error handling for malloc failure*/
		return (-1);

	while (ws != '\n')
	{
		hb = read(STDIN_FILENO, &ws, 1);
		if ( (hb == 0 && uinpt == 0) || hb == -1 )
		{
			free(buf);
			return (-1);
		}
		if (hb == 0 && uinpt != 0)
		{
			uinpt++;
			break;
		}
		if (uinpt >= BUFSIZE)
			buf = cstm_ftnrealloc(buf, uinpt, uinpt + 1);

		buf[uinpt] = ws;

		uinpt++;
	}

	buf[uinpt] = '\0';
	cstmac_line(lpt, nptr, buf, uinpt);
	byts = uinpt;

	if (hb != 0)
		uinpt = 0;

	return (byts);
}
