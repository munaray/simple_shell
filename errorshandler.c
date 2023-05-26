
#include "shell.h"

/**
 * numLen - This counts the digit length of a number.
 * @num: The number to measure.
 * Return: return the digit length.
 */
int numLen(int num)
{
	unsigned int num1;
	int len = 1;

	if (num < 0)
	{
		len++;
		num1 = num * -1;
	}
	else
	{
		num1 = num;
	}
	while (num1 > 9)
	{
		len++;
		num1 /= 10;
	}

	return (len);
}

/**
 * _itoa - This converts an integer to a string.
 * @num: The integer to be converted.
 * Return: return the converted string.
 */
char *_itoa(int num)
{
	char *buffer;
	int len = numLen(num);
	unsigned int num1;

	buffer = malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);

	buffer[len] = '\0';

	if (num < 0)
	{
		num1 = num * -1;
		buffer[0] = '-';
	}
	else
	{
		num1 = num;
	}

	len--;
	do {
		buffer[len] = (num1 % 10) + '0';
		num1 /= 10;
		len--;
	} while (num1 > 0);

	return (buffer);
}


/**
 * createError - This writes an error message to stderr.
 * @args: An array of arguments.
 * @err: The error value.
 * Return: return the error value.
 */
int createError(char **args, int err)
{
	char *error;

	switch (err)
	{
	case -1:
		error = errorEnv(args);
		break;
	case 1:
		error = error1(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			error = errorToExit(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			error = syntaxError(args);
		else
			error = errorToCd(args);
		break;
	case 126:
		error = error126(args);
		break;
	case 127:
		error = error127(args);
		break;
	}
	write(STDERR_FILENO, error, _strlen(error));

	if (error)
		free(error);
	return (err);

}
