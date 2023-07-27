#include "main.h"

/**
 * main - the begining of the code for the simple shell
 * @ac: argc
 * @av: argv
 * Return: 0 if successful / 1 otherwise
 */

int main(int ac, char **av)
{
	cstmdata dat;
	(void) ac;

	signal(SIGINT, cstm_sigint);
	cstmst_dat(&dat, av);
	sloop(&dat);
	cstm_freedata(&dat);

	if(dat.status < 0)
		return (255);

	return (dat.status);
}

/**
 * cstm_freedata - a  custom ftn to free data struct
 * @dat: struct
 * void
 */

void cstm_freedata(cstmdata *dat)
{
	unsigned int oz;

	for (oz = 0; dat->_environ[oz]; oz++)
	{
		free(dat->_environ[oz]);
	}

	free(dat->_environ);

	free(dat->pid);
}

/**
 * cstmst_dat -  custom ftn that
 * @dat: struct
 * @av: argument vector
 * Return: void
 */

void cstmst_dat(cstmdata *dat, char **av){
	unsigned int jf;

	dat->av = av;
	dat->input = NULL;
	dat->args = NULL;
	dat->status = 0;
	dat->counter = 1;

	for (jf = 0; environ[jf]; jf++)
		;

	dat->_environ = malloc(sizeof(char *) * (jf + 1));

	for (jf = 0; environ[jf]; jf++)
	{
		dat->_environ[jf] = cstmstr_dup(environ[jf]);
	}

	dat->_environ[jf] = NULL;
	dat->pid = cstmftn_itoa(getpid());
}
