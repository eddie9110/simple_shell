#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <limits.h>

/*Macros*/
#define TOK_DELIM " \t\r\n\a"
#define BUFSIZE 1024
#define TOK_BUFSIZE 128

extern char **environ;


/**
 * struct user_data - struct that contains all relevant data on runtime
 * @av: argv
 * @input: user cmds
 * @args: user cmd args
 * @status: shells's last stats
 * @counter: lines cnt
 * @_environ: environment variable
 * @pid: shell PID
 */

typedef struct user_data
{
	char **av;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
	char *input;
} cstmdata;

/**
 * struct s_llist - a custom singly linked list no. one
 * @tok: delimiter
 * @nxtlnk: nxt node
 */

typedef struct s_llist
{
	char tok;
	struct s_llist *lnknxt;

} cstm_s_llist;

/**
 * struct s_list - custom singly linked list no. two
 * @lneinpt: cmmd line user input
 * @lnknxt: the link part of the node
 * Description: single linked list to store user's cmds
 */

typedef struct s_list
{
	char *lneinpt;
	struct s_list *lnknxt;
} cstm_s_list2;

/**
 * struct cstm_varble_lst - custom singly linked list no. three to store variable
 * @varlgnt: variable length
 * @vlu: variable value
 * @vlulgth: value length
 * @lnknxt: parameter reps the address of the next node
 */

typedef struct cstm_varble_lst
{
	int varlgnt;
	char *vlu;
	int vlulgth;
	struct cstm_varble_lst *lnknxt;
} varble_lst;

/**
 * struct cstmbuilt_in_s - Builtin struct for command args.
 * @cmnd: parameter reps name of built-in command e.g. cd, exit, env
 * @f: a ftn ptr
 */

typedef struct cstmbuilt_in_s
{
	char *cmnd;
	int (*f)(cstmdata *dat);
} cstm_builtin;

cstm_s_llist *cstmftn_addnode_end(cstm_s_llist **hddr, char sptr);
void free_s_llist(cstm_s_llist **hddr);
cstm_s_list2 *cstm_add_node_end(cstm_s_list2 **hddr, char *lneinpt);
void freecstm_s_list(cstm_s_list2 **hddr);
varble_lst *add_varble_lst_node(varble_lst **hddr, int varlgnt, char *vlu, int vlulgth);
void free_varble_lst(varble_lst **hddr);
char *cstmftn_str_cat(char *dstn, const char *srce);
char *cstmftn_str_cpy(char *dstn, char *srce);
int cstmftn_str_cmp(char *st0, char *st1);
char *cstmftn_str_loc(char *stng, char ch);
int cstmftn_str_pn(char *stng, char *byts);
void cstmftn_cpymem(void *nptrr, const void *pntrr, unsigned int cap);
void *cstm_ftnrealloc(void *pntrr, unsigned int osze, unsigned int nsze);
char **cstmftn_dprealloc(char **pntrr, unsigned int ocap, unsigned int ncap);
char* cstmstr_dup(const char* strng);
int cstmstr_lgth(const char* strng); 
int ftncharcmpr(char stng[], const char *tokn);
char *ftnstr_tokn(char stng[], const char *tokn);
int ftnifdigt(const char *stn);
void cstmstr_reverser(char *stng);
int cstmrept_cntr(char *uipt, int he);
int cstm_get_syntx_err(char *uipt, int jo, char lt);
int cstmfst_ch(char *uipt, int *ke);
void cstmopt_syntx_err(cstmdata *dat, char *uipt, int se, int bool);
int cstm_chk_sntx_err(cstmdata *dat, char *uipt);
char *cstmrmve_comment(char *inptstr);
void sloop(cstmdata *dat);
char *cstm_readline(int *endf);
char *cstm_swapp_ftn(char *inpt, int bool);
void cstm_ad_node(cstm_s_llist **hddrs, cstm_s_list2 **hddrlst, char *inpt);
void cstm_nxt_cmd(cstm_s_llist **lstptr, cstm_s_list2 **lst, cstmdata *dat);
int cstm_cmnd_splitter_ftn(cstmdata *dat, char *inpt);
char **cstm_tkn_ftn(char *inpt);
void cstm_verify_ifenv(varble_lst **hddr, char *uinpt, cstmdata *data);
int cstm_chek_varble(varble_lst **hddr, char *in, char *s_t, cstmdata *data);
char *cstm_new_input(varble_lst **hddr, char *inptstr, char *ninpt, int lgth);
char *cstm_replcr(char *inptstr, cstmdata *dat);
void cstmac_line(char **lpt, size_t *nptr, char *buf, size_t om);
ssize_t cstm_getline(char **lpt, size_t *nptr, FILE *stm);
int cstmexec_ftn(cstmdata *dat);
int cstm_checkifin_dir(char *pth, int *iptr);
char *fnd_cmd(char *cmd, char **_environ);
int cstm_checkif_executable(cstmdata *dat);
int cstm_checkpermiss(char *drctry, cstmdata *dat);
int cstm_executer_ftn(cstmdata *dat);
char *cstmget_env(const char *envnam, char **_environ);
int cstm_retrieve_env(cstmdata *dat);
char *cstm_infocpy(char* ,char* );
void cstm_set_env(char* ,char* ,cstmdata *dat);
int cstmftn_setenv(cstmdata *dat);
int cstm_unset_envt(cstmdata *dat);
void cd_parent_drctry(cstmdata *dat);
void cstmcd(cstmdata *dat);
void cstmcd_prev(cstmdata *dat);
void cstmcd_home(cstmdata *dat);
int cstmcd_drctry(cstmdata *dat);
int (*cstmacqr_builtin(char *ucmds))(cstmdata *);
int cstm_my_exit(cstmdata *dat);
int cstmftn_getlgnt(int );
char *cstmftn_itoa(int );
int cstm_ftnatoi(char* );
char *cstmftn_str_cat_cd(cstmdata *dat, char*, char*, char*);
char *cstmftnerr_getcd(cstmdata *dat);
char *cstmftnerrnot_found(cstmdata *dat);
char *cstmftnerrext_shell(cstmdata *dat);
char *cstm_err_getalias(char **args);/*today*/
char *cstmftnerr_env(cstmdata *dat);
char *cstm_err_perm(char **args);/*today*/
char *cstmftnerr_path(cstmdata *dat);
int cstm_error_fetcher(cstmdata *dat, int );
void cstm_sigint(int sghndlr);
void cstmst_dat(cstmdata *dat, char **av);
void cstm_freedata(cstmdata *dat);

#endif
