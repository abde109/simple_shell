#include "shell.h"

/**
 * shell_prompt - Prompts the shell.
 * Return: The input line from the user.
 */
char *shell_prompt(void)
{
	char *inputLine = NULL;
	size_t bufferSize = 0;

	if (getline(&inputLine, &bufferSize, stdin) == -1)
	{
		free(inputLine);
		exit(1);
	}
	return (inputLine);
}

/**
 * prompt - Prompts the user for input.
 * @arguments: The arguments for the prompt.
 * @state: The current state of the shell.
 */
void prompt(char **arguments __attribute__((unused)), ShellState *state)
{
	char inputLine[INPUT_LEN];
	int terminalCheck = isatty(STDIN_FILENO);

	while (1)
	{
		if (terminalCheck)
			_print(PROMPT);
		if (fgets(inputLine, INPUT_LEN, stdin) == NULL)
			break;
		file_shell_prompt(inputLine, arguments, state);
	}
}
