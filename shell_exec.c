#include "shell.h"

/**
 * execute_shell_command - Executes a shell command.
 * @parameters: The parameters for the command.
 * @parameter: The parameter for the command.
 * @line_count: The line count in the command.
 */
void execute_shell_command(char **parameters, char *parameter, int line_count)
{
	int processStatus;
	pid_t processId;
	if (_strcmp(parameters[0], "cd") == 0)
	{
		_cd(parameter, parameters, line_count);
		return;
	}
	else if (_strcmp(parameters[0], "echo") == 0)
	{
		_echo(parameters);
		return;
	}
	else if (_strcmp(parameters[0], "env") == 0)
	{
		env_shell(parameters);
		return;
	}
	else if (_strcmp(parameters[0], "setenv") == 0)
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
		return;
	}
	else if (_strcmp(parameters[0], "unsetenv") == 0)
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
				print_error(parameter, line_count, parameters[0], "not found\n");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (execvp(parameters[0], parameters) == -1)
			{
				print_error(parameter, line_count, parameters[0], "not found\n");
				exit(EXIT_FAILURE);
			}
		}
	}
	else if (processId > 0)
	{
		waitpid(processId, &processStatus, WUNTRACED);
		if (WIFEXITED(processStatus))
		{
			exitStatus = WEXITSTATUS(processStatus);
		}
	}
	else if (processId < 0)
	{
		_perror("failed to fork\n");
	}
}