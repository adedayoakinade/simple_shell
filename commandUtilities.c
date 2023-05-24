#include "shell.h"

/** parseCommand - decrypt the command given to the system
 * @command: command to be decrypted
 *
 * Return: constant representing the type of the command
 */

int parseCommand(char *command)
{
	int index;
	char *internalCommands[] = {"env", "exit","setenv", "unsetenv", "cd",  NULL};
	char *commandPath = NULL;

	for (index = 0; command[index] != '\0'; index++)
	{
		if (command[index] == '/')
			return (EXT_CMD);
	}
	for (index = 0; internalCommands[index] != NULL; index++)
	{
		if (_strcmp(command, internalCommands[index]) == 0)
			return (INT_CMD);
	}
	/* @checkPath - checks if a command is found in the PATH */
	commandPath = checkPath(command);
	if (commandPath != NULL)
	{
		free(commandPath);
		return (PATH_CMD);
	}

	return (INVALID_CMD);
}

/**
 * executeCommand - executes a command
 * @tokenizedCommand: tokenized form of the command)
 * @commandType: type of the command
 *
 * Return: void
 */
void executeCommand(char **tokenizedCommand, int commandType)
{
	void (*function)(char **command);
	if (commandType == EXT_CMD)
	{
		if (execve(tokenizedCommand[0], tokenizedCommand, NULL) == -1)
		{
			perror(getEnvironmentVariable("PWD"));
			exit(2);
		}
	}
	if (commandType == PATH_CMD)
	{
		if (execve(checkPath(tokenizedCommand[0]), tokenizedCommand, NULL) == -1)
		{
			perror(getEnvironmentVariable("PWD"));
			exit(2);
		}
	}
	if (commandType == INT_CMD)
	{
		function = getFunction(tokenizedCommand[0]);
		function(tokenizedCommand);
	}
	if (commandType == INVALID_CMD)
	{
		print(shellName, STDERR_FILENO);
		print(": 1: ", STDERR_FILENO);
		print(tokenizedCommand[0], STDERR_FILENO);
		print(": not found\n", STDERR_FILENO);
		exitStatus = 127;
	}
}

/**
 * initializeCommand - starts executing all commands
 * @currentCommand: verify current command
 * @commandType: type of the current command
 *
 * Return: void function
 */
void initializeCommand(char **currentCommand, int commandType)
{
	pid_t pid;
	if (commandType == EXT_CMD || commandType == PATH_CMD)
	{
		pid = fork();
		if (pid == 0)
			executeCommand(currentCommand, commandType);
		else
		{
			waitpid(pid, &exitStatus, 0);
			exitStatus >>= 8;
		}
	}
	else
		executeCommand(currentCommand, commandType);
}

/**
 * getFunction - retrieves a function based on the command given
 * @command: command required to retrieve its function
 *
 * Return: pointer to the proper function, or null on fail
 */
void (*getFunction(char *command))(char **)
{
	int index;
	mapFunction mapping[] = {
		{"env", env_function}, {"exit", quit_function}, {"setenv", set_env}, {"unsetenv", unset_env}, {"cd", change_directory};
	for (index = 0; index < 5; index++)
	{
		if (_strcmp(command, mapping[index].commandName) == 0)
			return (mapping[index].function);
	}
	return (NULL);
}

/**
 * tokenize - tokenizes the input command
 * @inputString: input to be tokenized
 *@delimiter: delimiter to be used for tokenization
 *
 *Return: tokens array
 */

char **tokenize(char *inputString, char *delimiter)
{
	int numDelimiters = 0;
	char **resultArray = NULL;
	char *token = NULL;
	char *savePointer = NULL;
	token = _strtok_r(inputString, delimiter, &savePointer);

	while (token != NULL)
	{
		resultArray = _realloc(resultArray, sizeof(*resultArray) * numDelimiters, sizeof(*resultArray) * (numDelimiters + 1));
		resultArray[numDelimiters] = token;
		token = _strtok_r(NULL, delimiter, &savePointer);
		numDelimiters++;
	}

	resultArray = _realloc(resultArray, sizeof(*resultArray) * numDelimiters, sizeof(*resultArray) * (numDelimiters + 1));
	resultArray[numDelimiters] = NULL;

	return (resultArray);
}
