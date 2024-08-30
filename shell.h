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
char *find_command(char *command);

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

/* memory.c */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* List of allowed functions and system calls */
int access(const char *pathname, int mode);
int chdir(const char *path);
int close(int fd);
int closedir(DIR *dirp);
int execve(const char *filename, char *const argv[], char *const envp[]);
void exit(int status);
void _exit(int status);
int fflush(FILE *stream);
pid_t fork(void);
void free(void *ptr);
char *getcwd(char *buf, size_t size);
ssize_t getline(char **lineptr, size_t *n, FILE *stream);
pid_t getpid(void);
int isatty(int fd);
int kill(pid_t pid, int sig);
void *malloc(size_t size);
int open(const char *pathname, int flags);
DIR *opendir(const char *name);
void perror(const char *s);
ssize_t read(int fd, void *buf, size_t count);
struct dirent *readdir(DIR *dirp);
void (*signal(int signum, void (*handler)(int)))(int);
int stat(const char *pathname, struct stat *statbuf);
int lstat(const char *pathname, struct stat *statbuf);
int fstat(int fd, struct stat *statbuf);
char *strtok(char *str, const char *delim);
pid_t wait(int *wstatus);
pid_t waitpid(pid_t pid, int *wstatus, int options);
pid_t wait3(int *wstatus, int options, struct rusage *rusage);
pid_t wait4(pid_t pid, int *wstatus, int options, struct rusage *rusage);
ssize_t write(int fd, const void *buf, size_t count);

#endif /* SHELL_H */

