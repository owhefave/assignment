#include "shell.h"

#define MAX_COMMAND_LENGTH 128

int main()
{
	char command[MAX_COMMAND_LENGTH];
	
	while (1)
	{
		/* Display the shell prompt */
		printf("simple_shell> ");
		fflush(stdout);
		/* Read a command from the user */
		if (fgets(command, sizeof(command), stdin) == NULL)
		{
			printf("\n");
			break; /* Exit the shell on EOF (Ctrl+D)*/
		}

        // Remove the trailing newline character
        size_t cmd_len = strlen(command);
        if (cmd_len > 0 && command[cmd_len - 1] == '\n') {
            command[cmd_len - 1] = '\0';
        }

        // Execute the command
        if (strlen(command) > 0) {
            if (fork() == 0) {
                /* Child process */
                if (execlp(command, command, (char *)NULL) == -1) {
                    // Handle the case when the executable is not found
                    printf("simple_shell: %s: command not found\n", command);
                    exit(1);
                }
            } else {
                /* Parent process */
                wait(NULL); /* Wait for the child process to complete */
            }
        }
    }

    return 0;
}
