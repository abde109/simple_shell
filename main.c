#include "shell.h"
#include "globle.h"

/**
 * main - The entry point of the program.
 * @argCount: The number of arguments.
 * @arguments: The arguments array.
 * Return: EXIT_SUCCESS on success, or other exit status on failure.
 */

int main(int argCount, char **arguments)
{
	if (argCount == 1)
		prompt(arguments);
	if (argCount == 2)
		run_file_commands(arguments[1], arguments, line_count);
	return (EXIT_SUCCESS);
}
