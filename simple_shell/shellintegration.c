#include "shell.h"

int main(void)
{
    char input[MAX_INPUT_LENGTH];
    char *command;
    char *args[2];
    char *full_command;
    pid_t pid;
    int status;

    while (1)
    {
        printf("#cisfun$ ");  // Display prompt
        if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL)
        {
            if (feof(stdin))
            {
                printf("\n");
                break;  // Handle Ctrl+D gracefully
            }
            perror("fgets");
            continue;
        }

        // Remove trailing newline
        input[strcspn(input, "\n")] = '\0';

        if (input[0] == '\0')
            continue;  // Empty input, continue to next prompt

        command = strtok(input, " ");
        if (command == NULL)
            continue;  // Continue if command is empty

        args[0] = command;
        args[1] = strtok(NULL, " ");  // Only handle one argument

        // Check for built-in commands
        if (_strcmp(command, "exit") == 0)
        {
            return execute_exit();
        }
        else if (_strcmp(command, "cd") == 0)
        {
            execute_cd(args[1]);
            continue;
        }
        else if (_strcmp(command, "env") == 0)
        {
            execute_env();
            continue;
        }

        // Handle PATH and external commands
        full_command = find_command_in_path(command);
        if (full_command == NULL)
        {
            fprintf(stderr, "%s: command not found\n", command);
            continue;
        }

        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            free(full_command);
            continue;
        }
        else if (pid == 0)
        {
            if (execve(full_command, args, environ) == -1)
            {
                perror(command);  // Print error message
                free(full_command);
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            wait(&status);
        }

        free(full_command);  // Free the allocated memory for the full command path
    }

    return 0;
}

