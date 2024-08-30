#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

/* Macros */
#define MAX_INPUT_LENGTH 1024

/* Global environment */
extern char **environ;

/* Function Prototypes */

/* shell.c */
int main(void);

/* helper.c */
void handle_error(const char *msg);
void free_resources(char *input, char *command);

/* path.c */
char *find_command_in_path(char *command);

/* builtins.c */
int execute_exit(void);
int execute_cd(char *path);
int execute_env(void);

/* string_utils.c */
char *_strdup(const char *str);
int _strlen(const char *str);
int _strcmp(const char *str1, const char *str2);
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, const char *src);

/* memory.c */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

#endif /* SHELL_H */
