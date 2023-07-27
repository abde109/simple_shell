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
 * execute_shell_command - Executes a shell command.
 * @parameters: The parameters for the command.
 * @parameter: The parameter for the command.
 * @line_count: The line count in the command.
 */
void execute_shell_command(char **parameters, char *parameter, ShellState *state)
{
	int processStatus;
	pid_t processId;

	if (_strcmp(parameters[0], "cd") == 0)
	{
		execute_cd_command(parameters, parameter, state->line_count);
		return;
	}
	else if (_strcmp(parameters[0], "echo") == 0)
	{
		execute_echo_command(parameters);
		return;
	}
	else if (_strcmp(parameters[0], "env") == 0)
	{
		execute_env_command(parameters);
		return;
	}
	else if (_strcmp(parameters[0], "setenv") == 0)
	{
		execute_setenv_command(parameters);
		return;
	}
	else if (_strcmp(parameters[0], "unsetenv") == 0)
	{
		execute_unsetenv_command(parameters);
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
				print_error(parameter, state->line_count, parameters[0], "not found\n");
				exit(127);
			}
		}
		else
		{
			if (execvp(parameters[0], parameters) == -1)
			{
				print_error(parameter, state->line_count, parameters[0], "not found\n");
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
