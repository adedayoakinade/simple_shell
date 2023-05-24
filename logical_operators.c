#include "shell.h"

/**
 * execute_command - does just that
 *
 * Return: -1 if failure
 */
int execute_command()
{
	int status;
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		char *args[] = {"bin/sh", "-c", NULL};
		execve("bin/sh", args, NULL);
		exit(EXIT_FAILURE);
	}	
	else waitpid(pid, &status, 0);

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (-1);

}


/**
 * logic_commands - executes logical commands
 *
 * Return: -1
 */
int logic_operation(char *command)
{
	int res;
	char *first_command = strtok(command, "&|");
	char *second_command = strtok(NULL, "&|");
	char *operation = strtok(NULL, "&|");


	if (first_command == NULL || operation == NULL || second_command == NULL)
	{
		printf("ERROR: Invalid command format!\n");
		return (-1);
	}

	res = execute_command(first_command);


	if (strcmp(operation, "||") == 0)
	{
		if (res != 0)
			res = execute_command(second_command);
		
	}
	else if (strcmp(operation, "&&") == 0)
	{
	
		if (res == 0)
			res = execute_command(second_command);
	}
	else
	{
		printf("ERROR: Invalid operator: %s\n", operation);
		return (-1);
	}

	return (res);
}

