#include "shell.h"

/**
 * execute_env - Print the current environment variables.
 * 
 * Return: 1 to indicate the shell should continue running.
 */
int execute_env(void)
{
    char **env = environ;  // Access global environment variable

    // Print each environment variable
    while (*env)
    {
        printf("%s\n", *env);
        env++;
    }

    return 1;  // Return 1 to signal the shell should continue running
}

