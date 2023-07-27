#include "shell.h"

/**
 * main - The entry point of the program.
 * @argCount: The number of arguments.
 * @arguments: The arguments array.
 * Return: EXIT_SUCCESS on success, or other exit status on failure.
 */
int main(int argCount, char **arguments)
{
	ShellState state;

	state.exitStatus = 0;
	state.line_count = 0;

	if (argCount == 1)
		prompt(arguments, &state);
	if (argCount == 2)
		run_file_commands(arguments[1], arguments, &state);
	return (EXIT_SUCCESS);
}
