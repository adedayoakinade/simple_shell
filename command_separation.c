#include "shell.h"

/**
 * parse_command - traverses the command
 *
 * Return: nothing
 */
void parse_command(char *command, char *args[])
{
	int i;
	char* token = strtok(command, " ");

	for (i = 0; i < MAX_ARGS - 1; i++)
	{
		if (token != NULL)
		{
			args[i] = token;
			token = strtok(NULL, " ");
		}
	}

	args[i] = NULL;

}