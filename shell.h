#ifndef _SHELL_H_
#define _SHELL_H_

#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*Command chaining MACRO*/
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/*MACRO for reading/writing buffers*/
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* MACRO to convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2


#define HIST_FILE	".simple_shell_history" /*store command history*/
#define HIST_MAX	4096 /*max. no. of commsands to be stored in history*/

/*returns 1. if its using systems getline() function*/
#define USE_GETLINE 0
#define USE_STRTOK 0

extern char **environ;

/**
 * struct liststr - A singly linked list node containing a number and a string.
 *
 * @num: The numeric value stored in the node.
 * @str: A pointer to a string stored in the node.
 * @next: A pointer to the next node in the list.
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - A data structure that contains pseudo
 * arguments to pass into a function,allowing for a uniform
 * prototype for function pointer structs.
 *
 * @arg: A string generated from getline containing command-line arguments.
 * @argv: An array of strings generated from arg.
 * @path: A string representing the path of the current command.
 * @argc: The number of arguments in the command-line.
 * @line_count: The count of errors.
 * @err_num: The error code for exit() calls.
 * @linecount_flag: A flag that indicates whether to count this input line.
 * @fname: The name of the program file.
 * @env: A linked list that is a local copy of the environment.
 * @environ: A custom modified copy of the environment from the lnked list env
 * @history: A linked list that stores the command history.
 * @alias: A linked list that stores the command aliases.
 * @env_changed: A flag that indicates whether the environment has bn modified
 * @status: The return status of the last executed command.
 * @cmd_buf: A pointer to the buffer for commands separated by ';'.
 * @cmd_buf_type: A variable that represents the type of command
 * separator ('||', '&&', or ';').
 *
 * @readfd: The file descriptor used to read input lines.
 * @histcount: A count of the number of lines in the command history.
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

	char **cmd_buf; /*Pointer to cmd, chain buffer for memory management*/
	int cmd_buf_type; /*CMD_type ||, &&, ;*/
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - used to represent a built-in command in a shell program.
 *@type: A pointer to a string that represents the built-in command.
 *@func: A function pointer to the implementation of the built-in command.
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/*func to handle user input & execute shell comm. in the shell program*/
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/*func to check if a given str is a valid shell,duplicate str,serch in $PATH*/
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/*Entry point for a shell program*/
int loophsh(char **);

int bfree(void **);

int _myhistory(info_t *);
int _myalias(info_t *);

ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

char **strtow(char *, char *);
char **strtow2(char *, char);

char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

#endif /*_SHELL_H_*/
