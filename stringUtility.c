#include "shell.h"

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
 *Return: pointer to first time c is found in in str
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
