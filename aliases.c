#include "shell.h"

/**
 * handleAliasCmd - This function encapsulates all alias functionality
 * @args: This holds the argument parameter.
 * @argStart: This point to the beginning of args.
 *
 * Return: on success 0 otherwise -1
 */
int handleAliasCmd(char **args, char __attribute__((__unused__)) **argStart)
{
	alias_t *temp = aliases;
	int i, ret = 0;
	char *value;

	if (!args[0])
	{
		while (temp)
		{
			printAlias(temp);
			temp = temp->next;
		}
		return (ret);
	}
	for (i = 0; args[i]; i++)
	{
		temp = aliases;
		value = _strchr(args[i], '=');
		if (!value)
		{
			while (temp)
			{
				if (_strcmp(args[i], temp->name) == 0)
				{
					printAlias(temp);
					break;
				}
				temp = temp->next;
			}
			if (!temp)
				ret = createError(args + i, 1);
		}
		else
			updateAlias(args[i], value);
	}
	return (ret);
}

/**
* updateAlias - This is used to update or create new alias
*@name: Takes the name parameter for logic to be perform.
*@value: Takes the value parameter for logic to be perform.
*/

void updateAlias(char *name, char *value)
{
	alias_t *temp = aliases;
	int len, j, k;
	char *newValue;

	*value = '\0';
	value++;
	len = _strlen(value) - _strspn(value, "'\"");
	newValue = malloc(sizeof(char) * (len + 1));
	if (!newValue)
		return;
	for (j = 0, k = 0; value[j]; j++)
	{
		if (value[j] != '\'' && value[j] != '"')
			newValue[k++] = value[j];
	}
	newValue[k] = '\0';
	while (temp)
	{
		if (_strcmp(name, temp->name) == 0)
		{
			free(temp->value);
			temp->value = newValue;
			break;
		}
		temp = temp->next;
	}
	if (!temp)
		addAliasEnd(&aliases, name, newValue);
}

/**
 * printAlias- to print the aliases in the desired format..
 * @alias: This is a pointer to an alias.
 */
void printAlias(alias_t *alias)
{
	char *aliasString;
	int len = _strlen(alias->name) + _strlen(alias->value) + 4;

	aliasString = malloc(sizeof(char) * (len + 1));
	if (!aliasString)
		return;
	_strcpy(aliasString, alias->name);
	_strcat(aliasString, "='");
	_strcat(aliasString, alias->value);
	_strcat(aliasString, "'\n");

	write(STDOUT_FILENO, aliasString, len);
	free(aliasString);
}

/**
 * printAliasValue - This is used to print the value of specified alias.
 * @args: This holds the argument parameter..
 *Return: on success return args.
 */

char **printAliasValue(char **args)
{
	alias_t *temp;
	int i;
	char *newValue;

	if (_strcmp(args[0], "alias") == 0)
		return (args);
	for (i = 0; args[i]; i++)
	{
		temp = aliases;
		while (temp)
		{
			if (_strcmp(args[i], temp->name) == 0)
			{
				newValue = malloc(sizeof(char) * (_strlen(temp->value) + 1));
				if (!newValue)
				{
					freeArgs(args, args);
					return (NULL);
				}
				_strcpy(newValue, temp->value);
				free(args[i]);
				args[i] = newValue;
				i--;
				break;
			}
			temp = temp->next;
		}
	}

	return (args);
}
