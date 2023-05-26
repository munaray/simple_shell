#include "shell.h"

/**
 * tokenLength - This locates the delimiter marking the end
 *             of the first token contained within a string.
 * @str: The string to be searched.
 * @delim: The delimiter character.
 *Return: The delimiter marking the end of
 *         the intitial token pointed to be str.
 */
int tokenLength(char *str, char *delim)
{
	int i = 0, len = 0;

	while (*(str + i) && *(str + i) != *delim)
	{
		len++;
		i++;
	}

	return (len);
}

/**
 * tokensCounter - This counts the number of delimited
 *                words contained within a string.
 * @str: The string to be searched.
 * @delim: The delimiter character.
 * Return: The number of words contained within str.
 */
int tokensCounter(char *str, char *delim)
{
	int i, tokens = 0, len = 0;

	for (i = 0; *(str + i); i++)
		len++;

	for (i = 0; i < len; i++)
	{
		if (*(str + i) != *delim)
		{
			tokens++;
			i += tokenLength(str + i, delim);
		}
	}

	return (tokens);
}

/**
 * _strtok - This breaks down string into smaller unit .
 * @line: The string to be tokenized.
 * @delim: The delimiter character to tokenize the string by.
 * Return: A pointer to an array containing the tokenized words.
 */
char **_strtok(char *line, char *delim)
{
	char **ptr;
	int i = 0, tokens, t, chars, l;

	tokens = tokensCounter(line, delim);
	if (tokens == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (tokens + 2));
	if (!ptr)
		return (NULL);

	for (t = 0; t < tokens; t++)
	{
		while (line[i] == *delim)
			i++;

		chars = tokenLength(line + i, delim);

		ptr[t] = malloc(sizeof(char) * (chars + 1));
		if (!ptr[t])
		{
			for (i -= 1; i >= 0; i--)
				free(ptr[i]);
			free(ptr);
			return (NULL);
		}

		for (l = 0; l < chars; l++)
		{
			ptr[t][l] = line[i];
			i++;
		}

		ptr[t][l] = '\0';
	}
	ptr[t] = NULL;
	ptr[t + 1] = NULL;

	return (ptr);
}
