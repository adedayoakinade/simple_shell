#include "shell.h"

/* 
 * set_env - Initialises a new environment variable,
 * 	     or modifies an existing one.
 *
 * Return: nothing
 */

void set_env(char *args[])
{
	if (args[1] != NULL && args[2] != NULL)
	{
		int rudisha = setenv(args[1], args[2], 1);

		if (rudisha == -1)
		{
			fprintf(stderr, "Sorry! Failed to set environment variable\n");
		}
		else
		{
			fprintf(stderr, "Usage: set_env VARIABLE VALUE\n");
		}
	}
}

/*
 * unset_env - deletes an environment variable
 *
 * Return: void
 */
void unset_env(char *args[])
{
	if(args[1] != NULL)
	{
		int rudisha = unsetenv(args[1]);

		if (rudisha == -1)
		{
			fprintf(stderr, "Sorry! Failed to unset environment variable\n");
		}
		else
		{
			fprintf(stderr, "Usage: unset_env VARIABLE VALUE\n");
		}
	}

}
