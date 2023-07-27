#include "shell.h"

/**
 * _strlen - Returns the length of a string.
 * @str: The string to be measured.
 * Return: The length of the string.
 */
int _strlen(char *str)
{
	int length = 0;

	if (!str)
		return (0);

	while (*str++)
		length++;
	return (length);
}

/**
 * _strcmp - Compares two strings.
 * @str1: The first string.
 * @str2: The second string.
 * Return:An integer less than,equal to,or greater than zero if str1 is found,
 * respectively, to be less than, to match, or be greater than str2.
 */
int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * _strtok - Splits a string into tokens.
 * @str: The string to be split.
 * @delimiter: The delimiter that separates the tokens.
 * Return: A pointer to the next token, or NULL if there are no more tokens.
 */
char *_strtok(char *str, char delimiter)
{
	char *inputStr = NULL;
	char *resultStr;
	int counter = 0;

	if (str != NULL)
		inputStr = str;

	if (inputStr == NULL)
		return (NULL);

	resultStr = malloc(strlen(inputStr) + 1);

	for (; inputStr[counter] != '\0'; counter++)
	{
		if (inputStr[counter] != delimiter)
			resultStr[counter] = inputStr[counter];
		else
		{
			resultStr[counter] = '\0';
			inputStr = inputStr + counter + 1;
			return (resultStr);
		}
	}

	resultStr[counter] = '\0';
	inputStr = NULL;

	return (resultStr);
}
