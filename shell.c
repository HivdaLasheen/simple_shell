#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024

int main() {
    char input[MAX_INPUT_LENGTH];
    char *command;
    char *envp[] = {NULL}; // Pass an empty environment for now

    while (1) {
        printf("#cisfun$ "); // Display prompt
        if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL) {
            if (feof(stdin)) {
                printf("\n"); // Handle Ctrl+D gracefully
                exit(0);
            } else {
                perror("fgets");
                exit(1);
            }
        }

        // Remove trailing newline
        input[strcspn(input, "\n")] = 0; 

        command = strtok(input, " "); // Get the first word (command)

        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(1);
        } else if (pid == 0) { // Child process
            if (execve(command, &command, envp) == -1) {
                perror(command); // Print error message
                exit(1);
            }
        } else { // Parent process
            wait(NULL);
        }
    }

    return 0; // Should never reach here
}
