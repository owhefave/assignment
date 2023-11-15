#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 128

/* Display the shell prompt */
void display_prompt() {
    printf("#cisfun$ ");
    fflush(stdout);
}

/* Execute the specified command */
void execute_command(char *command) {
    pid_t pid;

    pid = fork();

    if (pid == -1) {
        /* Handle fork error */
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        /* Child process */
        if (execlp(command, command, (char *)NULL) == -1) {
            /* Handle the case when the executable is not found */
            perror("exec");
            exit(EXIT_FAILURE);
        }
    } else {
        /* Parent process */
        int status;
        waitpid(pid, &status, 0);
    }
}

int main() {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        size_t cmd_len;

        display_prompt();

        /* Read a command from the user */
        if (fgets(command, sizeof(command), stdin) == NULL) {
            if (feof(stdin)) {
                /* Exit the shell on EOF (Ctrl+D) */
                printf("\nExiting the shell. Goodbye!\n");
                break;
            } else {
                /* Handle fgets error */
                perror("fgets");
                exit(EXIT_FAILURE);
            }
        }

        /* Remove the trailing newline character */
        cmd_len = strlen(command);
        if (cmd_len > 0 && command[cmd_len - 1] == '\n') {
            command[cmd_len - 1] = '\0';
        }

        /* Execute the command */
        if (strlen(command) > 0) {
            execute_command(command);
        }
    }

    return 0;
}

