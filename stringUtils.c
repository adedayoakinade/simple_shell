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

	jointString = malloc(sizeof(*jointString) *
	(destStringLen + srcStringLen + 1));
	_strcpy(destString, jointString);
	_strcpy(srcString, jointString + destStringLen);
	jointString[destStringLen + srcStringLen] = '\0';
	return (jointString);
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



