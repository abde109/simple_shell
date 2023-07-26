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
int exitStatus = 0;
int line_count = 0;

/* Function prototypes */
void free_buffer(char **buffer);
void exit_shell(void);
void exit_shell_status(char **parameters);
int _putchar(char c);
void _eputs(char *str);
void print_d(int n, int fd);
void _cd(char **parameters);
void add_to_list(list_t **list, char *str);
void print_list_string(list_t *list);
void print_filtered_env(void);
void env_shell(char **parameters);
int set_env(char *varName, char *varValue);
int unset_env(char *varName);
void _echo(char **parameters);
void print_error(char *fname, int line_count, char *command, char *estr);
void execute_shell_command(char **parameters, char *parameter, int line_count);
char **tokenize_input(char *line);
char *shell_prompt(void);
int _print(char *text);
int _perror(char *errorMessage);
void prompt(char **arguments);
void run_file_commands(const char *fileName, char **arguments);
void file_shell_prompt(char *inputLine, char **arguments);
char *_strtok(char *str, char delimiter);
int _strlen(char *str);
int _strcmp(char *str1, char *str2);
int _puts(char *text);

#endif /* SHELL_H */
