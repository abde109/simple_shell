#include "shell.h"

/**
 * execute_setenv_command - Executes the 'setenv' command.
 * @parameters: The parameters for the command.
 */
void execute_setenv_command(char **parameters)
{
	if (parameters[1] == NULL || parameters[2] == NULL)
	{
		_perror("setenv: Too few arguments\n");
		return;
	}
	if (set_env(parameters[1], parameters[2]) != 0)
	{
		_perror("setenv: Failed to set environment variable\n");
	}
}

/**
 * execute_unsetenv_command - Executes the 'unsetenv' command.
 * @parameters: The parameters for the command.
 */
void execute_unsetenv_command(char **parameters)
{
	if (parameters[1] == NULL)
	{
		_perror("unsetenv: Too few arguments\n");
		return;
	}
	if (unset_env(parameters[1]) != 0)
	{
		_perror("unsetenv: Failed to unset environment variable\n");
	}
}

/**
 * handle_built_in_commands - Handles the built-in commands.
 * @parameters: The parameters for the command.
 * @parameter: The parameter for the command.
 * @state: The ShellState struct containing the line count.
 * Return: Returns 1 if a built-in command was executed, 0 otherwise.
 */
int handle_built_in_commands(char **parameters,
							 char *parameter,
							 ShellState *state)
{
	if (_strcmp(parameters[0], "cd") == 0)
	{
		execute_cd_command(parameters, parameter, state->line_count);
		return (1);
	}
	else if (_strcmp(parameters[0], "echo") == 0)
	{
		execute_echo_command(parameters);
		return (1);
	}
	else if (_strcmp(parameters[0], "env") == 0)
	{
		execute_env_command(parameters);
		return (1);
	}
	else if (_strcmp(parameters[0], "setenv") == 0)
	{
		execute_setenv_command(parameters);
		return (1);
	}
	else if (_strcmp(parameters[0], "unsetenv") == 0)
	{
		execute_unsetenv_command(parameters);
		return (1);
	}
	return (0);
}

/**
 * execute_shell_command - Executes a shell command.
 * @parameters: The parameters for the command.
 * @param: The parameter for the command.
 * @state: The ShellState struct containing the line count.
 */
void execute_shell_command(char **parameters,
						   char *param,
						   ShellState *state)
{
	int processStatus;
	pid_t processId;

	if (handle_built_in_commands(parameters, param, state))
	{
		return;
	}

	processId = fork();
	if (processId == 0)
	{
		char *path = getenv("PATH");

		if (path == NULL)
		{
			if (execv(parameters[0], parameters) == -1)
			{
				print_error(param, state->line_count, parameters[0], "not found\n");
				exit(127);
			}
		}
		else
		{
			if (execvp(parameters[0], parameters) == -1)
			{
				print_error(param, state->line_count, parameters[0], "not found\n");
				exit(127);
			}
		}
	}
	else if (processId > 0)
	{
		waitpid(processId, &processStatus, WUNTRACED);
		state->exitStatus = WEXITSTATUS(processStatus);
	}
	else if (processId < 0)
	{
		_perror("failed to fork\n");
	}
}
