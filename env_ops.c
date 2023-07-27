#include "shell.h"

/**
 * env_shell - Prints the shell environment.
 * @parameters: The parameters for the env command.
 */
void env_shell(char **parameters)
{
	if (parameters[1] != NULL)
	{
		_perror("fenv: Too many arguments\n");
		return;
	}

	print_filtered_env();
}

/**
 * set_env - Sets an environment variable.
 * @varName: The name of the variable.
 * @varValue: The value of the variable.
 *
 * Return: 0 on success, -1 on failure.
 */
int set_env(char *varName, char *varValue)
{
	char *environmentVar;
	int length;

	length = strlen(varName) + strlen(varValue) + 2;
	environmentVar = malloc(length);

	if (environmentVar == NULL)
		return (-1);

	snprintf(environmentVar, length, "%s=%s", varName, varValue);

	if (putenv(environmentVar) != 0)
		return (-1);

	return (0);
}

/**
 * unset_env - Unsets an environment variable.
 * @varName: The name of the variable.
 *
 * Return: 0 on success, -1 on failure.
 */
int unset_env(char *varName)
{
	if (unsetenv(varName) != 0)
		return (-1);

	return (0);
}

/**
 * print_filtered_env - Prints the filtered environment.
 */
void print_filtered_env(void)
{
	char **envp = environ;

	info_t info;

	info.env = NULL;

	while (*envp)
	{
		add_to_list(&(info.env), *envp);
		envp++;
	}

	print_list_string(info.env);
}
