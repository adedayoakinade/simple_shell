#include "shell.h"


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
 * _realloc - implements the realloc function in C
 * @ptr: pointer to the previously allocated memory
 * @old_size: size of ptr
 * @new_size: size of the new memory to be allocated
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
