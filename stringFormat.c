#include "shell.h"

/**
 *removeNewline - removes new line from a string
 *@str: string to be used
 *
 *
 *Return: void
 */

void removeNewline(char *str)
{
	int index = 0;

	while (str[index] != '\0')
	{
		if (str[index] == '\n')
			break;
		index++;
	}
	str[index] = '\0';
}

/**
 * removeComment - removes/ignores everything after a '#' char
 * @inputString: inputString to be modified
 *
 * Return: void
 */
void removeComment(char *inputString)
{
	int index = 0;

	if (inputString[index] == '#')
		inputString[index] = '\0';
	while (inputString[index] != '\0')
	{
		if (inputString[index] == '#' && inputString[index - 1] == ' ')
			break;
		index++;
	}
	inputString[index] = '\0';
}
