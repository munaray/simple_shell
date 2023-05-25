#include "shell.h"


/**
 * _copyenv - Creates a copy of the environment.
 *
 * Return: If an error occurs - NULL.
 *         O/w - a double pointer to the new copy.
 */
char **_copyenv(void)
{
	char **newEnviron;
	size_t size;
	int i;

	for (size = 0; environ[size]; size++)
		;

	newEnviron = malloc(sizeof(char *) * (size + 1));
	if (!newEnviron)
		return (NULL);

	for (i = 0; environ[i]; i++)
	{
		newEnviron[i] = malloc(_strlen(environ[i]) + 1);

		if (!newEnviron[i])
		{
			for (i--; i >= 0; i--)
				free(newEnviron[i]);
			free(newEnviron);
			return (NULL);
		}
		_strcpy(newEnviron[i], environ[i]);
	}
	newEnviron[i] = NULL;

	return (newEnviron);
}

/**
 * freeEnv - Frees the the environment copy.
 */
void freeEnv(void)
{
	int i;

	for (i = 0; environ[i]; i++)
		free(environ[i]);
	free(environ);
}

/**
 * _getenv - Gets an environmental variable from the PATH.
 * @var: The name of the environmental variable to get.
 *
 * Return: If the environmental variable does not exist - NULL.
 *         Otherwise - a pointer to the environmental variable.
 */
char **_getenv(const char *var)
{
	int i, len;

	len = _strlen(var);
	for (i = 0; environ[i]; i++)
	{
		if (_strncmp(var, environ[i], len) == 0)
			return (&environ[i]);
	}

	return (NULL);
}

/**
 * envValueHandler - Gets the value corresponding to an environmental variable.
 * @search: The environmental variable to search for.
 * @len: The length of the environmental variable to search for.
 *
 * Return: If the variable is not found - an empty string.
 *         Otherwise - the value of the environmental variable.
 *
 * Description: Variables are stored in the format VARIABLE=VALUE.
 */
char *envValueHandler(char *search, int len)
{
	char **variableAddr;
	char *replacement = NULL, *temp, *var;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, search, len);

	variableAddr = _getenv(var);
	free(var);
	if (variableAddr)
	{
		temp = *variableAddr;
		while (*temp != '=')
			temp++;
		temp++;
		replacement = malloc(_strlen(temp) + 1);
		if (replacement)
			_strcpy(replacement, temp);
	}

	return (replacement);
}

