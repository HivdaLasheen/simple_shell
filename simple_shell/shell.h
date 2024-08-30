// shell.h

#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

// Macros
#define MAX_INPUT_LENGTH 1024
#define MAX_ARGS 64
#define BUFFER_SIZE 1024

// Function Prototypes
void prompt(void);
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream);
char *find_command(char *command);
void execute_command(char **args);
void handle_exit(char **args);
void handle_env(void);

#endif /* SHELL_H */

