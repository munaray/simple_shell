#include "shell.h"

/**
 * _strchr - This locates a character in a string.
 * @str: The string to be searched.
 * @c: The character to be located.
 * Return: found c return a pointer the first occurence
 * otherwise return NULL.
 */
char *_strchr(char *str, char c)
{
	int i;

	for (i = 0; str[i]; i++)
	{
		if (str[i] == c)
			return (str + i);
	}

	return (NULL);
}

/**
 * _strspn - This gets the length of a prefix substring.
 * @str: The string to be searched.
 * @accept: The prefix to be measured.
 * Return: on success return bytes.
 */
int _strspn(char *str, char *accept)
{
	int bytes = 0;
	int i;

	while (*str)
	{
		for (i = 0; accept[i]; i++)
		{
			if (*str == accept[i])
			{
				bytes++;
				break;
			}
		}
		str++;
	}
	return (bytes);
}

/**
 * _strcmp - This is used to compares two strings.
 * @str1: The first string to be compared.
 * @str2: The second string to be compared.
 *
 * Return: if str1 > str2 return +ve byte
 *         otherwise if str1 = str2 return 0
 *         otherwise return -ve byte if str1 < str2.
 */
int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}

	if (*str1 != *str2)
		return (*str1 - *str2);

	return (0);
}

/**
 * _strncmp - This compare two strings.
 * @str1: The first pointer to a string.
 * @str2: The second pointer to a string.
 * @n: The first n bytes of the strings to compare.
 *
 * Return: if str1 > str2 return +ve byte
 *         otherwise if str1 = str2 return 0
 *         otherwise return -ve byte if str1 < str2.
 */
int _strncmp(const char *str1, const char *str2, size_t n)
{
	size_t i;

	for (i = 0; str1[i] && str2[i] && i < n; i++)
	{
		if (str1[i] > str2[i])
			return (str1[i] - str2[i]);
		else if (str1[i] < str2[i])
			return (str1[i] - str2[i]);
	}
	if (i == n)
		return (0);
	else
		return (-15);
}
