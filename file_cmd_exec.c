#include "shell.h"

/**
 * run_file_commands - Runs commands from a file.
 * @fileName: The name of the file.
 * @arguments: The arguments for the command.
 * @state: The state of the shell, including line count.
 */
void run_file_commands(const char *fileName, char **arguments,
					   ShellState *state)
{
	char inputLine[MAX_LINE_LENGTH];
	FILE *filePointer;

	filePointer = fopen(fileName, "r");
	if (!filePointer)
	{
		char errorMsg[128];

		snprintf(errorMsg, sizeof(errorMsg), "cannot open %s", fileName);
		print_error(arguments[0], state->line_count, errorMsg, "No such file\n");
		exit(2);
	}

	while (fgets(inputLine, MAX_LINE_LENGTH, filePointer) != NULL)
	{
		file_shell_prompt(inputLine, arguments, state);
	}

	fclose(filePointer);
}

/**
 * handle_exit - Handles the exit command.
 * @tokens: The tokenized command.
 * @state: The state of the shell.
 */
void handle_exit(char **tokens, ShellState *state)
{
	if (tokens[0] != NULL)
	{
		exit_shell_status(tokens, state);
	}
	free(tokens);
	exit_shell();
}

/**
 * file_shell_prompt - Prompts the shell with a file.
 * @inputLine: The input line from the file.
 * @arguments: The arguments for the command.
 * @state: The state of the shell.
 */
void file_shell_prompt(char *inputLine, char **arguments, ShellState *state)
{
	char **tokens, previousChar, *linePointer, *comment;
	int quoteFlag;

	state->line_count++;

	previousChar = '\0';
	comment = NULL;
	quoteFlag = 0;
	linePointer = inputLine;
	while (*linePointer != '\0')
	{
		if (*linePointer == '"' && previousChar != '\\')
			quoteFlag = !quoteFlag;
		else if (*linePointer == '#' && previousChar != '\\' && !quoteFlag)
		{
			if (previousChar == ' ')
			{
				comment = linePointer;
				break;
			}
		}
		previousChar = *linePointer;
		linePointer++;
	}
	if (comment != NULL)
		*comment = '\0';
	inputLine[strcspn(inputLine, "\n")] = '\0';
	tokens = tokenize_input(inputLine);
	if (tokens[0] != NULL)
	{
		if (strcmp(tokens[0], "exit") == 0)
		{
			handle_exit(tokens, state);
		}
		execute_shell_command(tokens, arguments[0], state);
	}
	free(tokens);
}
