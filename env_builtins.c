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
	int var_len = strlen(variable);
	int value_len = strlen(value);
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
	size_t com_len = strlen("unset_env") + strlen(variable + 1);
	char *command = malloc(com_len);

	snprintf(command, com_len, "unset_env %s", variable);

	i = 0;
	while (environ[i] != NULL)
	{
		if (strncmp(environ[i], variable, strlen(variable)) == 0
		&& environ[i][strlen(variable)] == '=')
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
