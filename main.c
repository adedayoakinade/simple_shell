#include "shell.h"

char **commands = NULL;
char *cmdLine = NULL;
char *shellName = NULL;
int exitStatus = 0;

/**
 * main - the main shell code
 * @argc: number of arguments passed
 * @argv: program arguments to be parsed
 *
 * Return: 0 on success
 */

int main(int argc __attribute__((unused)), char **argv)
{
	char **currentCmd = NULL;
	int index, commandType = 0;
	size_t bufferSize = 0;
	const char *variable = "MY_VARIABLE";
    	const char *value = "my_value";
	signal(SIGINT, ctrlCHandler);
	shellName = argv[0];
	while (1)
	{
		nonInteractiveMode();
		print(" ($) ", STDOUT_FILENO);
		if (getline(&cmdLine, &bufferSize, stdin) == -1)
		{
			free(cmdLine);
			exit(exitStatus);
		}
		removeNewline(cmdLine);
		removeComment(cmdLine);
		commands = tokenize(cmdLine, ";");

		if (set_env(variable, value) == 0) 
		{
        		printf("Environment variable '%s' set to '%s'\n", variable, value);
    		}


		for (index = 0; commands[index] != NULL; index++)
		{
			currentCmd = tokenize(commands[index], " ");
			if (currentCmd[0] == NULL)
			{
				free(currentCmd);
				break;
			}
			commandType = parseCommand(currentCmd[0]);

			/* initializer -   */
			initializeCommand(currentCmd, commandType);
			free(currentCmd);
		}
		
		free(commands);
	}
	free(cmdLine);

	return (exitStatus);
}
