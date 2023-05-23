#include "shell.h"


/**
 * quit_function - exits the shell
 * @tokenizedCommand: tokenized command 
 *
 * Return: void
 */

void quit_function(char **tokenizedCommand)
{
	int numTokens = 0, arg;
	for (; tokenizedCommand[numTokens] != NULL; numTokens++)
		;
	if (numTokens == 1)
	{
		free(tokenizedCommand);
		free(cmdLine);
		free(commands);
		exit(exitStatus);
	}
	else if (numTokens == 2)
	{
		arg = _atoi(tokenizedCommand[1]);
		if (arg == -1)
		{
			print(shellName, STDERR_FILENO);
			print(": 1: exit: Illegal number: ", STDERR_FILENO);
			print(tokenizedCommand[1], STDERR_FILENO);
			print("\n", STDERR_FILENO);
			exitStatus = 2;
		}
		else
		{
			free(cmdLine);
			free(tokenizedCommand);
			free(commands);
			exit(arg);
		}
	}
	else
		print("$: exit doesn't take more than one argument\n", STDERR_FILENO);
}

/**
 *env_function - prints the current_environnement
 *@tokenized_command: tokenized command 
 *
 *Return: void
 */

void env_function(char **tokenized_command __attribute__((unused)))
{
	int index;

	for (index = 0; environ[index] != NULL; index++)
	{
		print(environ[index], STDOUT_FILENO);
		print("\n", STDOUT_FILENO);
	}
}

