#include "shell.h"

#define MAX_COMMAND_LENGTH 128

int main() {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        /* Display the shell prompt */
        printf("#cisfun$ ");
        fflush(stdout);

        /* Read a command from the user */
        {
            size_t cmd_len;
            if (fgets(command, sizeof(command), stdin) == NULL) {
                if (feof(stdin)) {
                    /* Exit the shell on EOF (Ctrl+D) */
                    printf("\nExiting the shell. Goodbye!\n");
                    break;
                } else {
                    perror("fgets");
                    exit(EXIT_FAILURE);
                }
            }

            /* Remove the trailing newline character */
            cmd_len = strlen(command);
            if (cmd_len > 0 && command[cmd_len - 1] == '\n') {
                command[cmd_len - 1] = '\0';
            }
        }

        /* Execute the command */
        if (strlen(command) > 0) {
            pid_t child_pid = fork();

            if (child_pid == -1) {
                perror("fork");
                exit(EXIT_FAILURE);
            }

            if (child_pid == 0) {
                /* Child process */
                if (execlp("/bin/sh", "sh", "-c", command, (char *)NULL) == -1) {
                    /* Handle the case when the executable is not found */
                    perror("exec");
                    exit(EXIT_FAILURE);
                }
            } else {
                /* Parent process */
                int status;
                if (waitpid(child_pid, &status, 0) == -1) {
                    perror("waitpid");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }

    return 0;
}

