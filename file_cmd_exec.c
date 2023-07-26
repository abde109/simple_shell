#include "shell.h"

/**
 * run_file_commands - Runs commands from a file.
 * @fileName: The name of the file.
 * @arguments: The arguments for the command.
 * @line_count: The line count in the file.
 */
void run_file_commands(const char *fileName, char **arguments, int line_count)
{
	char inputLine[MAX_LINE_LENGTH];
	FILE *filePointer = fopen(fileName, "r");

	if (!filePointer)
	{
		if (!filePointer)
		{
			char errorMsg[128];
			snprintf(errorMsg, sizeof(errorMsg), "cannot open %s", fileName);
			print_error(arguments[0], line_count, errorMsg, "No such file\n");
			exit(2);
		}
	}

	while (fgets(inputLine, MAX_LINE_LENGTH, filePointer) != NULL)
	{
		file_shell_prompt(inputLine, arguments);
	}

	fclose(filePointer);
}

/**
 * file_shell_prompt - Prompts the shell with a file.
 * @inputLine: The input line from the file.
 * @arguments: The arguments for the command.
 */
void file_shell_prompt(char *inputLine, char **arguments)
{
	static int line_count = 0;
	char **tokens, previousChar, *linePointer, *comment;
	int quoteFlag;

	line_count++;

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
			if (tokens[0] != NULL)
			{
				exit_shell_status(tokens,exitStatus);
			}
			free(tokens);
			exit_shell();
		}
		execute_shell_command(tokens, arguments[0], line_count);
	}
	free(tokens);
}