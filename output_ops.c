#include "shell.h"

/**
 * _putchar - Writes the character c to stdout.
 * @c: The character to be written.
 * Return: On success, the character is returned. On error, -1 is returned.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _eputs - Writes a string to the standard error.
 * @str: The string to be written.
 */
void _eputs(char *str)
{
	write(STDERR_FILENO, str, _strlen(str));
}

/**
 * print_d - Prints an integer as a decimal.
 * @n: The integer to be printed.
 * @fd: The file descriptor where the integer will be written.
 */
void print_d(int n, int fd)
{
	char c;

	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	if (n / 10)
		print_d(n / 10, fd);

	c = n % 10 + '0';

	write(fd, &c, 1);
}

/**
 * _puts - Writes a string to stdout.
 * @text: The string to be written.
 * Return: The number of characters written.
 */
int _puts(char *text)
{
	int counter;

	if (!(text))
		return (0);

	for (counter = 0; text[counter]; counter++)
		write(STDOUT_FILENO, &text[counter], 1);

	return (counter);
}
