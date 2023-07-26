#include "shell.h"

/**
 * _cd - Changes the current directory of the process.
 * @parameter: The directory to change to.
 * @parameters: The parameters for the change.
 * @line_count: The line count in the command.
 */
void _cd(char *parameter, char **parameters, int line_count)
{
	char *s;
	char *dir;
	char buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");

	if (!parameters[1])
	{
		dir = getenv("HOME");
		if (!dir)
			chdir_ret = chdir((dir = getenv("PWD")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(parameters[1], "-") == 0)
	{
		dir = getenv("OLDPWD");
		if (!dir)
		{
			_puts(s);
			_putchar('\n');
			return;
		}
		_puts(dir);
		_putchar('\n');
		chdir_ret = chdir(dir);
	}
	else
		chdir_ret = chdir(parameters[1]);

	if (chdir_ret == -1)
	{
		print_error(parameter, line_count, parameters[0], "can't cd to ");
		_perror(parameters[1]);
		_perror("\n");
	}
	else
	{
		setenv("OLDPWD", getenv("PWD"), 1);
		setenv("PWD", getcwd(buffer, 1024), 1);
	}
}

/**
 * _echo - Displays a line of text.
 * @parameters: The parameters for the echo command.
 */
void _echo(char **parameters)
{
	int i = 1;

	while (parameters[i])
	{
		_print(parameters[i]);
		if (parameters[i + 1])
			_print(" ");
		i++;
	}
	_print("\n");
}
