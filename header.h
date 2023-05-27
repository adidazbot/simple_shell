#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for buffers that read/write */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for chain command */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for converter() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * history_file - function to fetch the history of a file
 * display_history - this function appends existing files
 * input_history - reads history from file
 * i_cmd - Determines if a file is an executable command
 * dp_chars - Duplicates characters.
 * find_path - Finds the given command in the PATH string
 * bfr - Frees a pointer and sets its address to NULL
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* execmd.c */
int i_cmd(info_t *info, char *path);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* storage.c */
int bfr(void **ptr);



/* codetimeline.c */
char *history_file(info_t *info);
int display_history(info_t *detail);
int input_history(info_t *detail);
int create_history_items(info_t *detail, char *buffer, int count);
int recount_history(info_t *detail);

/* items.c */

/* items1.c */
size_t len_of_list(const list_t *header);
char **stringlist(list_t *header);
size_t print_all_list(const list_t *n);
list_t *starting_node(list_t *n, char *refix, char b);
size_t cratex(list_t *header, list_t *node);

#endif
