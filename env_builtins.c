#include "shell.h"

/*
 * set_env - Initialises a new environment variable,
 * or modifies an existing one.
 *
 * @value: value of the variable
 * @variable: pointer to the variable
 *
 * Return: 0 if success, -1 otherwise
 */int set_env(const char *variable, const char *value)
{
	pid_t pid;
	int var_len = _strlen(variable);
	int value_len = _strlen(value);
	int com_len = 9 + var_len + value_len;
	char *command = malloc(com_len + 1);

	if (command == NULL)
	{
		perror("ERROR: Sorry! Failed to allocate memory\n");
		return (-1);
	}

	snprintf(command, com_len + 1, "set_env %s %s", variable, value);

	pid = fork();

	if (pid == -1)
	{
		perror("ERROR: Sorry! Fork failed\n");
		free(command);
		return (-1);
	}

	if (pid == 0)
	{
		char *args[MAX_ARGS];

		args[0] = "/bin/sh";
		args[1] = "-c";
		args[2] = command;
		args[3] = NULL;

		execve(args[0], args, NULL);

		perror("ERROR: Sorry! Command execution failed\n");
		exit(1);
	}
	else
	{
		int status;

		waitpid(pid, &status, 0);

		if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
		{
			free(command);
			return (0);
		}
		else
		{
			fprintf(stderr, "ERROR: Sorry! Failed to set environment variable\n");
			free(command);
			return (-1);
		}

	}

}

/*
 * unset_env - deletes an environment variable
 * @variable: pointer to variable
 *
 * Return: void
 *
 */void unset_env(const char *variable)
{
	int i, res;
	size_t com_len = _strlen("unset_env") + strlen(variable + 1);
	char *command = malloc(com_len);

	snprintf(command, com_len, "unset_env %s", variable);

	i = 0;
	while (environ[i] != NULL)
	{
		if (_strncmp(environ[i], variable, _strlen(variable)) == 0
		&& environ[i][_strlen(variable)] == '=')
		{
			environ[i] = NULL;
			break;
		}
		i++;
	}

	res = putenv(command);

	if (res != 0)
	{
		fprintf(stderr, "ERROR:
		Sorry! Failed to unset environment variable: %s\n", variable);
	}

	free(command);

}

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
                                                                                                                                            48,1          Bot
