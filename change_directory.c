#include "shell.h"

/**
 * home_dir - finds the home directory
 *
 * Return: pointer to the home directory
 *
 */
char *home_dir()
{
	return getenv("HOME");
}

/**
 * cd - chnages directories
 *
 * Return: nothing
 */
void change_directory(char *args[])
{
	char *home_directory = home_dir();
	char *targ_dir = args[1];
	char *current_dir = getenv("PWD");

	if (targ_dir == NULL)
	{
		targ_dir = home_directory;
	}
	else if (strcmp(targ_dir, "-") == 0)
	{
		targ_dir = getenv("OLDPWD");

		if (targ_dir == NULL)
		{
			fprintf(stderr, "Sorry! Previous directory not set\n");
			return;
		}

		printf("%s\n", targ_dir);
	}

	if (chdir(targ_dir) != 0)
	{
		fprintf(stderr, "Sorry! Failed to change directories\n");
		return;
	}

	if (getcwd(current_dir, MAX_INPUT_SIZE) != NULL)
	{
		setenv("PWD", current_dir, 1);
	}
	else
	{
		fprintf(stderr, "Sorry! Faile to get current directory\n");
	}
}
