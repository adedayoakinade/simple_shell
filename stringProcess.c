#include "shell.h"

/**
 *_strtok_r - tokenizes a string
 *@str: string to be tokenized
 *@delimiters: delimiter to be used to tokenize the string
 *@savePointer: pointer to be used to keep track of the next token
 *
 *Return: The next token
 */
char *_strtok_r(char *str, char *delimiters, char **savePointer)
{
	char *finishStr;

	if (str == NULL)
		str = *savePointer;

	if (*str == '\0')
	{
		*savePointer = str;
		return (NULL);
	}

	str += _strspn(str, delimiters);
	if (*str == '\0')
	{
		*savePointer = str;
		return (NULL);
	}

	finishStr = str + _strcspn(str, delimiters);
	if (*finishStr == '\0')
	{
		*savePointer = finishStr;
		return (str);
	}

	*finishStr = '\0';
	*savePointer = finishStr + 1;
	return (str);
}

/**
 * _atoi - changes a string to an integer
 * @str: the string to be changed
 *
 * Return: the converted integer
 */
int _atoi(char *str)
{
	unsigned int convertedInteger = 0;

	do {
		if (*str == '-')
			return (-1);
		else if ((*str < '0' || *str > '9') && *str != '\0')
			return (-1);
		else if (*str >= '0'  && *str <= '9')
			convertedInteger = (convertedInteger * 10) + (*str - '0');
		else if (convertedInteger > 0)
			break;
	} while (*str++);
	return (convertedInteger);
}

/**
 *print - prints a string to terminal
 *@str: string to be printed
 *@stream: stream to print out to
 *
 *Return: void
 */
void print(char *str, int stream)
{
	int index = 0;

	for (; str[index] != '\0'; index++)
		write(stream, &str[index], 1);
}
