#include "shell.h"

/**
 * logic_commands - executes logical commands
 *
 * Return: void
 */
void logic_commands(char *command)
{
	char* token_and = strstr(command, "&&");
	char *args[MAX_ARGS];


	if (token_and != NULL)
	{
		int status;
		char *first_command = strtok(command, "&&");
		char *second_command = strtok(NULL, "&&");
		pid_t pid = fork();


		if (pid == 0)
		{
			int i;
			char *tokenised = strtok(first_command, " ");
			char *args[MAX_ARGS];

			for (i = 0; i < MAX_ARGS - 1; i++)
			{
				if (tokenised != NULL)
				{
					args[i] = tokenised;
					tokenised = strtok(NULL, " ");
				}
			}

			args[i] = NULL;

			execve(args[0], args, environ);
			printf("Sorry! Command not found: %s\n", args[0]);
			exit(EXIT_FAILURE);
		}
		else if (pid < 0)
		{
			printf("Sorry! Fork failed");
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);

			if (status == 0)
			{
				return;
			}
		}

		if (second_command != NULL)
		{
			logic_commands(second_command);
		}
		return;

	}

	parseCommand(command);

	if (strcmp(args[0], "exit") == 0)
		exit(0);
	else if (strcmp(args[0], "setenv") == 0)
		set_env(args);
	else if (strcmp(args[0], "unsetenv") == 0)
		unset_env(args);
	else if (strcmp(args[0], "cd") == 0)
		change_directory(args);
	else
		executeCommand(args, 1);


}
