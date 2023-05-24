#include "shell.h"

/**
 * file_command - executes commands within a file given as input
 * @command: pointer to said file
 *
 */
void file_command(char *command)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		char *args[] = {"bin/sh", "-c", (char *)command, NULL};
		execve("bin/sh", args, NULL);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		int status;

		waitpid(pid, &status, 0);

		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
			fprintf(stderr, "Command '%s' exited with non-zero status\n", command);
			
		}
	}
}
