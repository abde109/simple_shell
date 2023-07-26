#include "shell.h"

/**
 * exit_shell - Exits the shell.
 */
void exit_shell(void)
{
	exit(EXIT_SUCCESS);
}

/**
 * exit_shell_status - Exits the shell with a status.
 * @parameters: The parameters for exit status.
 */
void exit_shell_status(char **parameters, int exitStatus)
{
	int status;
	char *endptr;

	if (parameters[1] == NULL)
	{
		free(parameters);
		exit(exitStatus);
	}

	status = strtol(parameters[1], &endptr, 10);

	if (*endptr != '\0' || endptr == parameters[1])
	{
		print_error("hsh", line_count, "exit", ": Illegal number: ");
		print_error(parameters[1], line_count, "", "\n");
		exit(2);
	}
	else if (status < 0)
	{
		print_error("hsh", line_count, "exit", ": Illegal number: ");
		print_error(parameters[1], line_count, "", "\n");
		exit(2);
	}
	else
	{
		free(parameters);
		exit(status % 256);
	}
}