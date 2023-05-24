#include "shell.h"

/**
 * cd - changes the cwd to a specified directory
 *
 * Return: nothing
 */
void change_directory(const char *path)
{
	char *argv[3];
	char buf[MAX_INPUT_SIZE];
	char *envp[] = {NULL};

	if (strcmp(path, "-") == 0)
	{
		char *prev_pwd = getenv("OLDPWD");

		if (prev_pwd == NULL)
		{
			fprintf(stderr, "Sorry! Previous directory not set\n");
			return;
		}

		printf("%s\n", prev_pwd);
		path = prev_pwd;
	}

	if (chdir(path) != 0)
	{
		perror("chdir");
		return;
	}

	getcwd(buf, sizeof(buf));
		set_env("OLDPWD", getenv("PWD"));
		set_env("PWD", buf);

		argv[0] = "cd";
		argv[1] = (char *)path;
		argv[2] = NULL;

		if (execve("bin/cd", argv, envp) == -1)
		{
			perror("execve");
			return;
		}
}
