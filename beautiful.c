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
	char message[] = "My name is Favour and my partner is Jide\n";

	write(STDOUT_FILENO, message, strlen(message));
	return (0);
}

