#include "shell.h"

/**
 * envShell - Prints the current environment.
 * @args: An array of arguments passed to the shell.
 * @argStart: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *	   Otherwise - 0.
 *
 * Description: Prints one variable per line in the
 *              format 'variable'='value'.
 */
int envShell(char **args, char __attribute__((__unused__)) **argStart)
{
	int i;
	char nc = '\n';

	if (!environ)
		return (-1);

	for (i = 0; environ[i]; i++)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, &nc, 1);
	}

	(void)args;
	return (0);
}

/**
 * setenvShell - Changes or adds an environmental variable to the PATH.
 * @args: An array of arguments passed to the shell.
 * @argStart: A double pointer to the beginning of args.
 * Description: args[1] is the name of the new or existing PATH variable.
 *              args[2] is the value to set the new or changed variable to.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int setenvShell(char **args, char __attribute__((__unused__)) **argStart)
{
	char **envVariable = NULL, **newEnviron, *newValue;
	size_t size;
	int i;

	if (!args[0] || !args[1])
		return (createError(args, -1));

	newValue = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
	if (!newValue)
		return (createError(args, -1));
	_strcpy(newValue, args[0]);
	_strcat(newValue, "=");
	_strcat(newValue, args[1]);

	envVariable = _getenv(args[0]);
	if (envVariable)
	{
		free(*envVariable);
		*envVariable = newValue;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;

	newEnviron = malloc(sizeof(char *) * (size + 2));
	if (!newEnviron)
	{
		free(newValue);
		return (createError(args, -1));
	}

	for (i = 0; environ[i]; i++)
		newEnviron[i] = environ[i];

	free(environ);
	environ = newEnviron;
	environ[i] = newValue;
	environ[i + 1] = NULL;

	return (0);
}

/**
 * unsetenvShell - Deletes an environmental variable from the PATH.
 * @args: An array of arguments passed to the shell.
 * @argStart: A double pointer to the beginning of args.
 * Description: args[1] is the PATH variable to remove.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int unsetenvShell(char **args, char __attribute__((__unused__)) **argStart)
{
	char **envVariable, **newEnviron;
	size_t size;
	int i, i2;

	if (!args[0])
		return (createError(args, -1));
	envVariable = _getenv(args[0]);
	if (!envVariable)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	newEnviron = malloc(sizeof(char *) * size);
	if (!newEnviron)
		return (createError(args, -1));

	for (i = 0, i2 = 0; environ[i]; i++)
	{
		if (*envVariable == environ[i])
		{
			free(*envVariable);
			continue;
		}
		newEnviron[i2] = environ[i];
		i2++;
	}
	free(environ);
	environ = newEnviron;
	environ[size - 1] = NULL;

	return (0);
}
