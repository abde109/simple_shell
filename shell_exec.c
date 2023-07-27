#include "shell.h"

/**
 * execute_cd_command - Executes the 'cd' command.
 * @parameters: The parameters for the command.
 * @parameter: The parameter for the command.
 * @line_count: The line count in the command.
 */
void execute_cd_command(char **parameters, char *parameter, int line_count)
{
	_cd(parameter, parameters, line_count);
}

/**
 * execute_echo_command - Executes the 'echo' command.
 * @parameters: The parameters for the command.
 */
void execute_echo_command(char **parameters)
{
	_echo(parameters);
}

/**
 * execute_env_command - Executes the 'env' command.
 * @parameters: The parameters for the command.
 */
void execute_env_command(char **parameters)
{
	env_shell(parameters);
}
