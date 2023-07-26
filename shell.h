#ifndef SHELL_H
#define SHELL_H

/* Required libraries */
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

/* Macro definitions */
#define INPUT_LEN 1024
#define MAX_LINE_LENGTH 1024
#define PROMPT "#cisfun$ "

/* Data structures */
typedef struct list_s
{
	char *str;
	struct list_s *next;
} list_t;

typedef struct info_s
{
	list_t *env;
} info_t;

extern char **environ;
extern int exitStatus;
extern int line_count;

/* Memory Operations (from memory_ops.c) */
void free_buffer(char **buffer);

/* String Operations (from string_ops.c) */
int _strlen(char *str);
int _strcmp(char *str1, char *str2);
char *_strtok(char *str, char delimiter);

/* Output Operations (from output_ops.c) */
int _putchar(char c);
void _eputs(char *str);
void print_d(int n, int fd);
int _puts(char *text);

/* Error Handling (from error_handling.c) */
int _print(char *text);
int _perror(char *errorMessage);
void print_error(char *fname, int line_count, char *command, char *estr);

/* Exit Operations (from exit_ops.c) */
void exit_shell(void);
void exit_shell_status(char **parameters, int exitStatus);

/* Tokenization (from tokenization.c) */
char **tokenize_input(char *line);

/* Prompt Operations (from prompt_ops.c) */
char *shell_prompt(void);
void prompt(char **arguments);

/* File Command Execution (from file_cmd_exec.c) */
void run_file_commands(const char *fileName, char **arguments, int line_count);
void file_shell_prompt(char *inputLine, char **arguments);

/* Shell Execution (from shell_exec.c) */
void execute_shell_command(char **parameters, char *parameter, int line_count);

/* Command Operations (from cmd_ops.c) */
void _cd(char *parameter, char **parameters, int line_count);
void _echo(char **parameters);

/* Environment Operations (from env_ops.c) */
void env_shell(char **parameters);
int set_env(char *varName, char *varValue);
int unset_env(char *varName);
void print_filtered_env(void);

/* List Operations (from list_ops.c) */
void add_to_list(list_t **list, char *str);
void print_list_string(list_t *list);

/* Main Function (from main.c) */
int main(int argCount, char **arguments);

#endif /* SHELL_H */
