#include "shell.h"

/**
 * main - Entry point for the simple shell.
 * @ac: The argument count (not used).
 * @av: The argument vector (not used).
 *
 * Return: Always 0.
 */
int main(int ac, char **av)
{
    info_t info = INFO_INIT;
    int interactive_mode = isatty(STDIN_FILENO);

    /* Set up signal handler for interactive mode */
    if (interactive_mode)
        signal(SIGINT, sigintHandler);

    /* Initialize environment */
    populate_env_list(&info);

    /* Run the shell loop */
    if (ac == 1)
        hsh(&info, av);
    else
        fprintf(stderr, "Usage: %s\n", av[0]);

    /* Free allocated memory and exit */
    free_info(&info, 0);
    return (0);
}

/**
 * hsh - Main shell loop.
 * @info: Structure containing potential arguments.
 * @av: Argument vector.
 *
 * Return: 0 on success, 1 on failure.
 */
int hsh(info_t *info, char **av)
{
    ssize_t input_size = 0;
    char *input = NULL;
    int status = 0;

    while (1)
    {
        if (interactive(info))
            printf("#cisfun$ "); /* Display prompt */

        /* Get user input */
        input_size = get_input(info);
        if (input_size == -1) /* Handle EOF */
        {
            if (feof(stdin))
            {
                printf("\n");
                exit(0);
            }
            else
            {
                perror("getline");
                exit(1);
            }
        }

        /* Parse and execute command */
        info->arg = input;
        if (info->arg && *info->arg)
        {
            info->arg = replace_vars(info->arg, info); /* Perform variable expansion */
            info->argv = split_string(info->arg, " \t");
            if (info->argv[0])
            {
                status = find_builtin(info);
                if (!status)
                {
                    find_cmd(info);
                }
            }
            free(info->arg);
            free(info->argv);
        }
        free(input);
    }

    return status;
}

/**
 * find_builtin - Checks if a command is a built-in and executes it.
 * @info: Structure containing potential arguments.
 *
 * Return: 1 if a built-in command was executed, 0 otherwise.
 */
int find_builtin(info_t *info)
{
    int i;
    builtin_table builtin_cmds[] = {
        {"exit", _myexit},
        {"cd", _mycd},
        {"help", _myhelp},
        {"env", _myenv},
        {"setenv", _mysetenv},
        {"unsetenv", _myunsetenv},
        {"history", _myhistory},
        {"alias", _myalias},
        {NULL, NULL}
    };

    for (i = 0; builtin_cmds[i].type; i++)
    {
        if (_strcmp(info->arg, builtin_cmds[i].type) == 0)
        {
            return builtin_cmds[i].func(info);
        }
    }
    return 0;
}

/**
 * find_cmd - Finds and executes a command.
 * @info: Structure containing potential arguments.
 */
void find_cmd(info_t *info)
{
    char *path = find_path(info, info->arg, NULL);

    if (path != NULL)
    {
        if (execve(path, info->argv, info->environ) == -1)
        {
            perror(info->argv[0]);
        }
        free(path);
    }
    else
    {
        fprintf(stderr, "%s: Command not found\n", info->argv[0]);
    }
}

/**
 * interactive - Checks if the shell is running in interactive mode.
 * @info: Structure containing potential arguments.
 *
 * Return: 1 if in interactive mode, 0 otherwise.
 */
int interactive(info_t *info)
{
    return isatty(STDIN_FILENO);
}

/**
 * replace_vars - Replaces environment variables in the input string.
 * @input: The command string.
 * @info: Structure containing environment variables.
 *
 * Return: The command string with environment variables replaced.
 */
char *replace_vars(char *input, info_t *info)
{
    char *start, *end, *var_name, *var_value, *new_input;
    size_t len, var_len;

    if (input == NULL)
        return NULL;

    new_input = malloc(strlen(input) + 1); /* Allocate new string */
    if (new_input == NULL)
        return NULL;

    strcpy(new_input, input);

    start = strchr(new_input, '$');
    while (start != NULL)
    {
        end = strpbrk(start + 1, " \t\n"); /* Find end of variable */
        if (end == NULL)
            end = start + strlen(start);

        var_len = end - (start + 1);
        var_name = malloc(var_len + 1);
        if (var_name == NULL)
        {
            free(new_input);
            return NULL;
        }

        strncpy(var_name, start + 1, var_len);
        var_name[var_len] = '\0';

        var_value = _getenv(info, var_name);
        if (var_value != NULL)
        {
            len = strlen(new_input) - (end - start) + strlen(var_value) + 1;
            new_input = realloc(new_input, len);
            if (new_input == NULL)
            {
                free(var_name);
                return NULL;
            }

            memmove(start + strlen(var_value), end, strlen(end) + 1);
            memcpy(start, var_value, strlen(var_value));
        }

        free(var_name);
        start = strchr(start + strlen(var_value), '$'); /* Find next variable */
    }

    return new_input;
}

