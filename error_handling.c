#include "shell.h"

/**
 * _print - Writes a string to stdout.
 * @text: The string to be written.
 * Return: The number of characters written.
 */
int _print(char *text)
{
	return (write(STDOUT_FILENO, text, _strlen(text)));
}

/**
 * _perror - Writes an error message to stderr.
 * @errorMessage: The error message to be written.
 * Return: The number of characters written.
 */
int _perror(char *errorMessage)
{
	return (write(STDERR_FILENO, errorMessage, _strlen(errorMessage)));
}

/**
 * print_error - Prints an error message to stderr.
 * @fname: The function name where the error occurred.
 * @line_count: The line count where the error occurred.
 * @command: The command which caused the error.
 * @estr: The error string to be printed.
 */
void print_error(char *fname, int line_count, char *command, char *estr)
{
	_eputs(fname);
	_eputs(": ");
	print_d(line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(command);
	_eputs(": ");
	_eputs(estr);
}
