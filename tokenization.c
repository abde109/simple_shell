#include "shell.h"

/**
 * tokenize_input - Tokenizes an input line.
 * @line: The input line to be tokenized.
 * Return: A pointer to the array of tokens.
 */
char **tokenize_input(char *line)
{
	int length = 0;
	int bufferCapacity = 15;
	char *delimiter, *token, **tokens = malloc(bufferCapacity * sizeof(char *));

	if (!tokens)
	{
		_perror("ERROR token malloc failed");
		exit(1);
	}

	delimiter = " \t\r\n";
	token = strtok(line, delimiter);

	while (token != NULL)
	{
		if (token[0] == '#')
		{
			break;
		}
		if (token[0] == '"' && token[strlen(token) - 1] == '"')
		{
			token[strlen(token) - 1] = '\0';
			token++;
		}

		tokens[length] = token;
		length++;

		if (length >= bufferCapacity)
		{
			bufferCapacity = (int)(bufferCapacity * 1.5);
			tokens = realloc(tokens, bufferCapacity * sizeof(char *));
		}

		token = strtok(NULL, delimiter);
	}

	tokens[length] = NULL;
	return (tokens);
}
