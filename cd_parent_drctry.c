#include "main.h"

/**
 * cd_parent_drctry - a ftn that changes to the parent directory
 * @dat: data relevant (environ)
 * Return: void
 */

void cd_parent_drctry(cstmdata *dat)
{
	char*cpds;
	char pwd[PATH_MAX];
	char *cpwd, *drctry;

	getcwd(pwd, sizeof(pwd));
	cpds = cstmstr_dup(pwd);
	cstm_set_env("OLDPWD", cpds, dat);
	drctry = dat->args[1];

	if (cstmftn_str_cmp(".", drctry) == 0)
	{
		cstm_set_env("PWD", cpds, dat);
		free(cpds);
		return;
	}
	if (cstmftn_str_cmp("/", cpds) == 0)
	{
		free(cpds);
		return;
	}

	cpwd = cpds;
	cstmstr_reverser(cpwd);
	cpwd = ftnstr_tokn(cpwd, "/");

	if (cpwd != NULL)
	{
		cpwd = ftnstr_tokn(NULL, "\0");

		if (cpwd != NULL)
			cstmstr_reverser(cpwd);
	}
	if (cpwd != NULL)
	{
		chdir(cpwd);
		cstm_set_env("PWD", cpwd, dat);
	}
	else
	{
		chdir("/");
		cstm_set_env("PWD", "/", dat);
	}
	dat->status = 0;

	free(cpds);
}

/**
 * cstmcd - custom function that changes directory of interest
 * @dat: dir info
 * Return: void
 */

void cstmcd(cstmdata *dat)
{
	char *drctry, *cpds, *cdir;
	char pd[PATH_MAX];

	getcwd(pd, sizeof(pd));

	drctry = dat->args[1];

	if (chdir(drctry) == -1)
	{
		cstm_error_fetcher(dat, 2);
		return;
	}

	cpds = cstmstr_dup(pd);
	cstm_set_env("OLDPWD", cpds, dat);

	cdir = cstmstr_dup(drctry);
	cstm_set_env("PWD", cdir, dat);

	free(cpds);
	free(cdir);

	dat->status = 0;

	chdir(drctry);
}

/**
 * cstmcd_prev - custom ftn that changes to previous directory
 * @dat: data relevant (environ)
 * Return: no return
 */

void cstmcd_prev(cstmdata *dat)
{
	char pwd[PATH_MAX];
	char *pntwd, *pwdo, *cpds, *pwdo0;

	getcwd(pwd, sizeof(pwd));
	cpds = cstmstr_dup(pwd);

	pwdo = cstmget_env("OLDPWD", dat->_environ);

	if (pwdo == NULL)
		pwdo0 = cpds;
	else
		pwdo0 = cstmstr_dup(pwdo);

	cstm_set_env("OLDPWD", cpds, dat);

	if (chdir(pwdo0) == -1)
		cstm_set_env("PWD", cpds, dat);
	else
		cstm_set_env("PWD", pwdo0, dat);

	pntwd = cstmget_env("PWD", dat->_environ);

	write(STDOUT_FILENO, pntwd, cstmstr_lgth(pntwd));

	write(STDOUT_FILENO, "\n", 1);

	free(cpds);

	if (pwdo)
		free(pwdo0);

	dat->status = 0;

	chdir(pntwd);
}

/**
 * cstmcd_home - a custom ftn to change wdir to home dir
 * @dat: parameter represents data of interest
 * Return: void
 */

void cstmcd_home(cstmdata *dat)
{
	char *pntwd, *hmme;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	pntwd = cstmstr_dup(pwd);

	hmme = cstmget_env("HOME", dat->_environ);

	if (hmme == NULL)
	{
		cstm_set_env("OLDPWD", pntwd, dat);
		free(pntwd);
		return;
	}

	if (chdir(hmme) == -1)
	{
		cstm_error_fetcher(dat, 2);
		free(pntwd);
		return;
	}

	cstm_set_env("OLDPWD", pntwd, dat);
	cstm_set_env("PWD", hmme, dat);

	free(pntwd);
	dat->status = 0;
}
