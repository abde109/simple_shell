#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_CMD_LEN 256
#define PROMPT "#cisfun$ "

int main(int argc __attribute__((unused)), char **argv)
{
    char cmd[MAX_CMD_LEN];
    char *cmd_argv[2];
    char *envp[] = {NULL};

    while (1)
    {
        printf(PROMPT);
        if (fgets(cmd, sizeof(cmd), stdin) == NULL)
        {
            printf("\n");
            exit(EXIT_SUCCESS);
        }

        cmd[strlen(cmd) - 1] = '\0';  /* Remove trailing newline */

        cmd_argv[0] = cmd;
        cmd_argv[1] = NULL;

        if (access(cmd, X_OK) == 0)
        {
            if (fork() == 0)
            {
                execve(cmd, cmd_argv, envp);
            }
            else
            {
                wait(NULL);
            }
        }
        else
        {
            fprintf(stderr, "%s: No such file or directory\n", argv[0]);
        }
    }

    return EXIT_SUCCESS;
}
