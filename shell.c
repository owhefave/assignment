#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 128

/* Display the shell prompt */
void display_prompt(void)
{
	printf("#cisfun$ ");
	fflush(stdout);
}

/* Execute the specified command */
void execute_command(char *command)
{
	pid_t pid;
	int status;

	pid = fork();

	if (pid == -1)
	{
		/* Handle fork error */
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		/* Child process */

	if (execlp(command, command, (char *)NULL) == -1)
	{
	
	/*Handle the case when exec not found*/

	fprintf(stderr, "Error: Cannot execute '%s'. Command not found.\n", command);
			exit(EXIT_FAILURE);
	}
	}
	else 
	{
		/* Parent process */
		waitpid(pid, &status, 0);
	}
}
int main(void)
{
		char command[MAX_COMMAND_LENGTH];

		while (1) 
		{
		display_prompt();

		/* Read a command from the user */
		if (fgets(command, sizeof(command), stdin) == NULL)
		{
			if (feof(stdin)) 
		{
			/* Exit the shell on EOF (Ctrl+D) */
			printf("\nExiting the shell. Goodbye!\n");
			break;
		}
		else 
		{
			/* Handle fgets error */
			perror("fgets");
			exit(EXIT_FAILURE);
		}
	}
	return 0;


		/* Remove the trailing newline character */

size_t cmd_len = strlen(command);
if (cmd_len > 0 && command[cmd_len - 1] == '\n') 
	{
		command[cmd_len - 1] = '\0';
	}

		/* Execute the command */
		if (strlen(command) > 0) 
		{
			execute_command(command);
		}
	}
	}
	return 0;
}
