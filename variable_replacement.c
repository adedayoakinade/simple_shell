#include "shell.h"

/**
 * replace_vars - does just that
 * @commmand: pointer to the command given
 *
 * Return: always 0
 */
int replace_vars(char *command)
{
	int status;
	char *position;
	char pid[10];

	position = strstr(command, "$?");

	if (position != NULL)
	{
		snprintf(position, 3, "%d", status);
	}

	position = strstr(command, "$$");

	if (position != NULL)
	{
		snprintf(position, 6, "%d", getpid());
	}

	return 0;
}
