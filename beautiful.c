#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
 * main - Entry point of the program
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	char *message = malloc(50 * sizeof(char));

	if (message == NULL)
	{
	perror("Error in allocating memory");
		return (EXIT_FAILURE);
	}

	sprintf(message, "Beautiful code that passes Betty checks\n");
	write(STDOUT_FILENO, message, strlen(message));

	free(message);
	return (EXIT_SUCCESS);
}
