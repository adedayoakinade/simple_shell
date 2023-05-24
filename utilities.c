#include "shell.h"

/**
 * parseCommand - decrypt the command given to the system
 * @command: command to be decrypted
 *
 * Return: constant representing the type of the command
 */
int parseCommand(char *command)
{
	int index;
	char *internalCommands[] = {"env", "exit", NULL};
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
 * checkPath - checks if a command is found in the PATH
 * @command: command to be checked for in the PATH
 *
 * Return: path where the command is found in, NULL if not found
 */
char *checkPath(char *command)
{
	char **pathArray = NULL;
	char *tempString, *tempString2, *pathCopy;
	char *path = getEnvironmentVariable("PATH");
	int index;

	if (path == NULL || _strlen(path) == 0)
		return (NULL);
	pathCopy = malloc(sizeof(*pathCopy) * (_strlen(path) + 1));
	_strcpy(path, pathCopy);
	pathArray = tokenize(pathCopy, ":");
	for (index = 0; pathArray[index] != NULL; index++)
	{
		tempString2 = _strcat(pathArray[index], "/");
		tempString = _strcat(tempString2, command);
		if (access(tempString, F_OK) == 0)
		{
			free(tempString2);
			free(pathArray);
			free(pathCopy);
			return (tempString);
		}
		free(tempString);
		free(tempString2);
	}
	free(pathCopy);
	free(pathArray);
	return (NULL);
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
		{"env", env_function}, {"exit", quit_function}};
	for (index = 0; index < 2; index++)
	{
		if (_strcmp(command, mapping[index].commandName) == 0)
			return (mapping[index].function);
	}
	return (NULL);
}

/**
 * getEnvironmentVariable - gets the value of an environment variable
 * @name: name of the environment variable
 *
 * Return: the value of the variable as a string
 */
char *getEnvironmentVariable(char *name)
{
	char **environment;
	char *pairPointer;
	char *nameCopy;

	for (environment = environ; *environment != NULL; environment++)
	{
		for (pairPointer = *environment, nameCopy = name;
			 *pairPointer == *nameCopy; pairPointer++, nameCopy++)
		{
			if (*pairPointer == '=')
				break;
		}
		if ((*pairPointer == '=') && (*nameCopy == '\0'))
			return (pairPointer + 1);
	}
	return (NULL);
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
 * tokenize - tokenizes the input string
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
		resultArray = _realloc(resultArray, sizeof(*resultArray)
		* numDelimiters, sizeof(*resultArray) * (numDelimiters + 1));
		resultArray[numDelimiters] = token;
		token = _strtok_r(NULL, delimiter, &savePointer);
		numDelimiters++;
	}

	resultArray = _realloc(resultArray, sizeof(*resultArray)
	* numDelimiters, sizeof(*resultArray) * (numDelimiters + 1));
	resultArray[numDelimiters] = NULL;

	return (resultArray);
}

/**
 * _realloc - implements the realloc function in C
 * @ptr: pointer to the previously allocated memory
 * @oldSize: size of ptr
 * @newSize: size of the new memory to be allocated
 *
 * Return: pointer to the address of the new memory block
 */
void *_realloc(void *ptr, unsigned int oldSize, unsigned int newSize)
{
	void *tempBlock;
	unsigned int index;

	if (ptr == NULL)
	{
		tempBlock = malloc(newSize);
		return (tempBlock);
	}
	else if (newSize == oldSize)
		return (ptr);
	else if (newSize == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	else
	{
		tempBlock = malloc(newSize);
		if (tempBlock != NULL)
		{
			for (index = 0; index < min(oldSize, newSize); index++)
				*((char *)tempBlock + index) = *((char *)ptr + index);
			free(ptr);
			return (tempBlock);
		}
		else
			return (NULL);
	}
}

/**
 * ctrlCHandler - handles the output due to CTRL-C command
 * @signalNum: signal number
 *
 * Return: void
 */
void ctrlCHandler(int signalNum)
{
	if (signalNum == SIGINT)
		print("\n($) ", STDIN_FILENO);
}

/**
 * nonInteractiveMode - runs the shell in non interactive mode
 *
 * Return: void
 */

void nonInteractiveMode(void)
{
	char **currentCommand = NULL;
	int index, commandType = 0;
	size_t bufferSize = 0;

	if (!(isatty(STDIN_FILENO)))
	{
		while (getline(&cmdLine, &bufferSize, stdin) != -1)
		{
			removeNewline(cmdLine);
			removeComment(cmdLine);
			commands = tokenize(cmdLine, ";");
			for (index = 0; commands[index] != NULL; index++)
			{
				currentCommand = tokenize(commands[index], " ");
				if (currentCommand[0] == NULL)
				{
					free(currentCommand);
					break;
				}
				commandType = parseCommand(currentCommand[0]);
				initializeCommand(currentCommand, commandType);
				free(currentCommand);
			}
			free(commands);
		}
		free(cmdLine);
		exit(exitStatus);
	}
}
