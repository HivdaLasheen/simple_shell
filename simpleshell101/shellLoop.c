#include "shell.h"

/**
 * main - Entry point for the shell
 * @ac: Argument count
 * @av: Argument vector
 * 
 * Return: 0 on success
 */
int main(int ac, char **av)
{
    info_t info;
    (void)ac;
    (void)av;

    /* Initialize info structure */
    memset(&info, 0, sizeof(info_t));
    info.readfd = STDIN_FILENO;

    while (1)
    {
        /* Display the prompt */
        if (isatty(STDIN_FILENO))
            write(STDOUT_FILENO, "#cisfun$ ", 9);

        /* Read command input */
        if (get_input(&info) == -1)
            break;

        /* Process the command */
        if (info.arg && *info.arg)
        {
            info.argv = split_string(info.arg, " \t");
            if (info.argv[0])
                execute_command(&info);
            free(info.arg);
            free(info.argv);
        }

        /* Clean up */
        free(info.arg);
        free(info.argv);
    }

    /* Free the info structure */
    if (info.cmd_buf)
        free(info.cmd_buf);

    return 0;
}

/**
 * get_input - Reads a line of input from stdin
 * @info: The info_t structure
 * 
 * Return: 0 on success, -1 on failure or EOF
 */
ssize_t get_input(info_t *info)
{
    char *buf = NULL;
    size_t bufsize = 0;
    ssize_t nread;

    nread = getline(&buf, &bufsize, stdin);
    if (nread == -1)
    {
        if (feof(stdin))
        {
            free(buf);
            return -1;
        }
        perror("getline");
        free(buf);
        return -1;
    }

    info->arg = buf;
    return nread;
}

/**
 * execute_command - Executes a command
 * @info: The info_t structure
 */
void execute_command(info_t *info)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return;
    }

    if (pid == 0)  /* Child process */
    {
        if (execve(info->argv[0], info->argv, environ) == -1)
        {
            perror(info->argv[0]);
            _exit(EXIT_FAILURE);
        }
    }
    else  /* Parent process */
    {
        waitpid(pid, &status, 0);
    }
}

/**
 * split_string - Splits a string into an array of strings
 * @str: The string to split
 * @delim: The delimiter characters
 * 
 * Return: Array of strings
 */
char **split_string(char *str, const char *delim)
{
    char **result;
    size_t count = 0;
    char *token;

    /* Count the number of tokens */
    char *str_copy = strdup(str);
    token = strtok(str_copy, delim);
    while (token)
    {
        count++;
        token = strtok(NULL, delim);
    }
    free(str_copy);

    /* Allocate memory for the result array */
    result = malloc((count + 1) * sizeof(char *));
    if (!result)
        return NULL;

    /* Populate the result array */
    str_copy = strdup(str);
    token = strtok(str_copy, delim);
    count = 0;
    while (token)
    {
        result[count++] = strdup(token);
        token = strtok(NULL, delim);
    }
    result[count] = NULL;

    free(str_copy);
    return result;
}

