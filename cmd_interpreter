// shell.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024

void prompt(void)
{
    printf("#cisfun$ ");
}

int main(void)
{
    char input[MAX_INPUT_LENGTH];
    char *command;
    char *args[2];
    pid_t pid;

    while (1)
    {
        prompt();  // Display prompt

        if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL)
        {
            if (feof(stdin))  // Handle Ctrl+D
            {
                printf("\n");
                break;
            }
            perror("fgets");
            exit(EXIT_FAILURE);
        }

        // Remove trailing newline
        input[strcspn(input, "\n")] = 0;

        // Only handle single commands without arguments
        command = strtok(input, " ");
        args[0] = command;
        args[1] = NULL;

        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)  // Child process
        {
            if (execve(command, args, NULL) == -1)
            {
                perror(command);
                exit(EXIT_FAILURE);
            }
        }
        else  // Parent process
        {
            wait(NULL);
        }
    }

    return 0;
}

