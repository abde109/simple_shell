#include "shell.h"

void free_buffer(char **buffer)
{
    int counter = 0;

    if (buffer)
    {
        for (counter = 0; buffer[counter]; counter++)
            free(buffer[counter]);
        free(buffer);
    }
}

void exit_shell(void)
{
    exit(EXIT_SUCCESS);
}

void exit_shell_status(char **parameters)
{
    int status;
    char *endptr;

    if (parameters[1] == NULL)
    {
        free(parameters);
        exit(exitStatus);
    }

    status = strtol(parameters[1], &endptr, 10);

    if (*endptr != '\0' || endptr == parameters[1])
    {
        print_error("hsh", line_count, "exit", ": Illegal number: ");
        print_error(parameters[1], line_count, "", "\n");
        exit(2);
    }
    else if (status < 0)
    {
        print_error("hsh", line_count, "exit", ": Illegal number: ");
        print_error(parameters[1], line_count, "", "\n");
        exit(2);
    }
    else
    {
        free(parameters);
        exit(status % 256);
    }
}

int _putchar(char c)
{
    return write(1, &c, 1);
}

void _eputs(char *str)
{
    write(STDERR_FILENO, str, _strlen(str));
}

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

void _cd(char **parameters)
{
    char *s, *dir, buffer[1024];
    int chdir_ret;

    s = getcwd(buffer, 1024);
    if (!s)
        _puts("TODO: >>getcwd failure emsg here<<\n");
    if (!parameters[1])
    {
        dir = getenv("HOME");
        if (!dir)
            chdir_ret = chdir((dir = getenv("PWD")) ? dir : "/");
        else
            chdir_ret = chdir(dir);
    }
    else if (_strcmp(parameters[1], "-") == 0)
    {
        dir = getenv("OLDPWD");
        if (!dir)
        {
            _puts(s);
            _putchar('\n');
            return;
        }
        _puts(dir);
        _putchar('\n');
        chdir_ret = chdir(dir);
    }

    else
        chdir_ret = chdir(parameters[1]);
    if (chdir_ret == -1)
    {
        _perror("can't cd to ");
        _perror(parameters[1]), _perror("\n");
    }
    else
    {
        setenv("OLDPWD", getenv("PWD"), 1);
        setenv("PWD", getcwd(buffer, 1024), 1);
    }
}

void add_to_list(list_t **list, char *str)
{
    list_t *new_node = malloc(sizeof(list_t));
    new_node->str = str;
    new_node->next = *list;
    *list = new_node;
}

void print_list_string(list_t *list)
{
    while (list)
    {
        printf("%s\n", list->str);
        list = list->next;
    }
}

void print_filtered_env()
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

void env_shell(char **parameters)
{
    if (parameters[1] != NULL)
    {
        _perror("fenv: Too many arguments\n");
        return;
    }
    print_filtered_env();
}

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

int unset_env(char *varName)
{
    if (unsetenv(varName) != 0)
        return (-1);
    return (0);
}

void _echo(char **parameters)
{
    int i = 1;
    while (parameters[i])
    {
        _print(parameters[i]);
        if (parameters[i + 1])
            _print(" ");
        i++;
    }
    _print("\n");
}

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

void execute_shell_command(char **parameters, char *parameter, int line_count)
{
    int processStatus;
    pid_t processId;
    if (_strcmp(parameters[0], "cd") == 0)
    {
        _cd(parameters);
        return;
    }
    else if (_strcmp(parameters[0], "echo") == 0)
    {
        _echo(parameters);
        return;
    }
    else if (_strcmp(parameters[0], "env") == 0)
    {
        env_shell(parameters);
        return;
    }
    else if (_strcmp(parameters[0], "setenv") == 0)
    {
        if (parameters[1] == NULL || parameters[2] == NULL)
        {
            _perror("setenv: Too few arguments\n");
            return;
        }
        if (set_env(parameters[1], parameters[2]) != 0)
        {
            _perror("setenv: Failed to set environment variable\n");
        }
        return;
    }
    else if (_strcmp(parameters[0], "unsetenv") == 0)
    {
        if (parameters[1] == NULL)
        {
            _perror("unsetenv: Too few arguments\n");
            return;
        }
        if (unset_env(parameters[1]) != 0)
        {
            _perror("unsetenv: Failed to unset environment variable\n");
        }
        return;
    }
    processId = fork();
    if (processId == 0)
    {
        char *path = getenv("PATH");
        if (path == NULL)
        {
            if (execv(parameters[0], parameters) == -1)
            {
                print_error(parameter, line_count, parameters[0], "not found\n");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            if (execvp(parameters[0], parameters) == -1)
            {
                print_error(parameter, line_count, parameters[0], "not found\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    else if (processId > 0)
    {
        waitpid(processId, &processStatus, WUNTRACED);
        if (WIFEXITED(processStatus))
        {
            exitStatus = WEXITSTATUS(processStatus);
            
            if (exitStatus != 0)
            {
                exit(exitStatus);
            }
        }
    }
    else if (processId < 0)
    {
        _perror("failed to fork\n");
    }
}

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

char *shell_prompt()
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

int _print(char *text)
{
    return (write(STDOUT_FILENO, text, _strlen(text)));
}

int _perror(char *errorMessage)
{
    return (write(STDERR_FILENO, errorMessage, _strlen(errorMessage)));
}

void prompt(char **arguments __attribute__((unused)))
{
    char inputLine[INPUT_LEN];
    int terminalCheck = isatty(STDIN_FILENO);

    while (1)
    {
        if (terminalCheck)
            _print(PROMPT);
        if (fgets(inputLine, INPUT_LEN, stdin) == NULL)
            break;
        file_shell_prompt(inputLine, arguments);
    }
}

void run_file_commands(const char *fileName, char **arguments)
{
    char inputLine[MAX_LINE_LENGTH];
    FILE *filePointer = fopen(fileName, "r");

    if (!filePointer)
    {
        _perror(arguments[0]);
        _perror(": 0: Can't open");
        _perror("\n");
        exit(127);
    }

    while (fgets(inputLine, MAX_LINE_LENGTH, filePointer) != NULL)
    {
        file_shell_prompt(inputLine, arguments);
    }

    fclose(filePointer);
}

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
                exit_shell_status(tokens);
            }
            free(tokens);
            exit_shell();
        }
        execute_shell_command(tokens, arguments[0], line_count); /* Pass line_count as the third argument */
    }
    free(tokens);
}

int main(int argCount, char **arguments)
{
    if (argCount == 1)
        prompt(arguments);
    if (argCount == 2)
        run_file_commands(arguments[1], arguments);
    return (EXIT_SUCCESS);
}

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

int _strlen(char *str)
{
    int length = 0;

    if (!str)
        return (0);

    while (*str++)
        length++;
    return (length);
}

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

int _puts(char *text)
{
    int counter;

    if (!(text))
        return (0);
    for (counter = 0; text[counter]; counter++)
        write(STDOUT_FILENO, &text[counter], 1);
    return (counter);
}
