#include "shell.h"

/**
 *_strcmp - compare two strings
 *@string1: first string to be compared
 *@string2: second string to be compared
 *
 * Return: difference of the two strings
 */

int _strcmp(char *string1, char *string2)
{
	int index = 0;

	while (string1[index] != '\0')
	{
		if (string1[index] != string2[index])
			break;
		index++;
	}
	return (string1[index] - string2[index]);
}

/**
 *_strcat - concatenates two strings
 *@destString: string to be concatenated to
 *@srcString:  string to concatenate
 *
 * Return: concatenated string
 */

char *_strcat(char *destString, char *srcString)
{
	char *jointString =  NULL;
	int destStringLen = _strlen(destString);
	int srcStringLen = _strlen(srcString);

	jointString = malloc(sizeof(*jointString) * (destStringLen + srcStringLen + 1));
	_strcpy(destString, jointString);
	_strcpy(srcString, jointString + destStringLen);
	jointString[destStringLen + srcStringLen] = '\0';
	return (jointString);
}

/**
 *_strspn - gets the length of a prefix substring
 *@string1: string to be searched
 *@string2: string to be used
 *
 *Return: number of bytes in the initial segment of string
 */

int _strspn(char *string1, char *string2)
{
	int index = 0;
	int charMatch = 0;

	while (string1[index] != '\0')
	{
		if (_strchr(string2, string1[index]) == NULL)
			break;
		charMatch++;
		index++;
	}
	return (charMatch);
}

/**
 *_strcspn - computes segment of str1 which consists of characters not in str2
 *@string1: string to be searched
 *@string2: string to be used
 *
 *Return: index at which a char in str1 exists in str2
 */


int _strcspn(char *string1, char *string2)
{
	int value = 0, index;

	for (index = 0; string1[index] != '\0'; index++)
	{
		if (_strchr(string2, string1[index]) != NULL)
			break;
		value++;
	}
	return (value);
}

/**
 *_strchr - locates a char in a string
 *@str: string to be searched
 *@c: char to be checked
 *
 *Return: pointer to the first occurence of c in s
 */

char *_strchr(char *str, char c)
{
	int index = 0;

	for (; str[index] != c && str[index] != '\0'; index++)
		;
	if (str[index] == c)
		return (str + index);
	else
		return (NULL);
}

/**
 *_strcpy - copies a string to another buffer
 *@srcString: source to copy from
 *@destString: destination to copy to
 *
 * Return: void
 */

void _strcpy(char *srcString, char *destString)
{
	int index = 0;

	for (; srcString[index] != '\0'; index++)
		destString[index] = srcString[index];
	destString[index] = '\0';
}

/**
 *_strlen - counts string length
 *@str: string to be counted
 *
 * Return: length of the string
 */

int _strlen(char *str)
{
	int stringLength = 0;

	if (str == NULL)
		return (stringLength);
	for (; str[stringLength] != '\0'; stringLength++)
		;
	return (stringLength);
}

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
