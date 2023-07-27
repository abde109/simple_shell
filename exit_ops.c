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
 * @state: The current state of the shell.
 */
void exit_shell_status(char **parameters, ShellState *state)
{
	free(parameters);
	exit(state->exitStatus);
}
