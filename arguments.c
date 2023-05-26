#include "shell.h"

/**
 * getArgs - This is used to get command to stdin.
 * @line: This stores the command.
 * @retLastExeCmd: This return value of the last executed command.
 * Return: On error return NULL.
 */
char *getArgs(char *line, int *retLastExeCmd)
{
	size_t n = 0;
	ssize_t read;
	char *prompt = "sam@munaray> ";
char *output = "You entered: ";
	if (line)
		free(line);

	read = _getline(&line, &n, STDIN_FILENO);
	write(STDOUT_FILENO, output, _strlen(output));
	write(STDOUT_FILENO, line, _strlen(line));
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, _strlen(prompt));
		return (getArgs(line, retLastExeCmd));
	}

	line[read - 1] = '\0';
	replaceVariable(&line, retLastExeCmd);
	lineHandler(&line, read);

	return (line);
}

/**
 * callArgs - This function takes an array of arguments
 * and partitions operators from commands.
 * @args: An array of arguments containing both
 * commands and operators.
 * @argStart: A double pointer to the beginning of args.
 * @retLastExeCmd: This return value of the last executed command..
 * Return: The return value of the last executed command.
 */
int callArgs(char **args, char **argStart, int *retLastExeCmd)
{
	int ret, i;

	if (!args[0])
		return (*retLastExeCmd);
	for (i = 0; args[i]; i++)
	{
		if (_strncmp(args[i], "||", 2) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			args = printAliasValue(args);
			ret = executeArgs(args, argStart, retLastExeCmd);
			if (*retLastExeCmd != 0)
			{
				args = &args[++i];
				i = 0;
			}
			else
			{
				for (i++; args[i]; i++)
					free(args[i]);
				return (ret);
			}
		}
		else if (_strncmp(args[i], "&&", 2) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			args = printAliasValue(args);
			ret = executeArgs(args, argStart, retLastExeCmd);
			if (*retLastExeCmd == 0)
			{
				args = &args[++i];
				i = 0;
			}
			else
			{
				for (i++; args[i]; i++)
					free(args[i]);
				return (ret);
			}
		}
	}
	args = printAliasValue(args);
	ret = executeArgs(args, argStart, retLastExeCmd);
	return (ret);
}

/**
 * executeArgs - This execute a command specified by the
 * given arguments.
 * @args: An array of arguments.
 * @argStart: A double pointer to the beginning of args.
 * @retLastExeCmd: This return value of the last executed command.
 *
 * Return: The return value of the last executed command.
 */
int executeArgs(char **args, char **argStart, int *retLastExeCmd)
{
	int ret, i;
	int (*builtin)(char **args, char **argStart);

	builtin = handleBuiltin(args[0]);

	if (builtin)
	{
		ret = builtin(args + 1, argStart);
		if (ret != EXIT)
			*retLastExeCmd = ret;
	}
	else
	{
		*retLastExeCmd = execute(args, argStart);
		ret = *retLastExeCmd;
	}

	hist++;

	for (i = 0; args[i]; i++)
		free(args[i]);

	return (ret);
}

/**
 * argsHandler - This function encapsulates all arguments functionality.
 * @retLastExeCmd: The return value of the last executed command.
 * Return: @EOF return -2, untokenized input return -1,
 *         otherwise: return the last executed command.
 */
int argsHandler(int *retLastExeCmd)
{
	int ret = 0, i;
	char **args, *line = NULL, **argStart;

	line = getArgs(line, retLastExeCmd);
	if (!line)
		return (END_OF_FILE);

	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (ret);
	if (checkArgs(args) != 0)
	{
		*retLastExeCmd = 2;
		freeArgs(args, args);
		return (*retLastExeCmd);
	}
	argStart = args;

	for (i = 0; args[i]; i++)
	{
		if (_strncmp(args[i], ";", 1) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			ret = callArgs(args, argStart, retLastExeCmd);
			args = &args[++i];
			i = 0;
		}
	}
	if (args)
		ret = callArgs(args, argStart, retLastExeCmd);

	free(argStart);
	return (ret);
}

/**
 * checkArgs - This checks the possibility of any leading lines.
 * @args: A pointer that tokenized commands and arguments.
 * Return: on success return 0.
 */
int checkArgs(char **args)
{
	size_t i;
	char *current, *next;

	for (i = 0; args[i]; i++)
	{
		current = args[i];
		if (current[0] == ';' || current[0] == '&' || current[0] == '|')
		{
			if (i == 0 || current[1] == ';')
				return (createError(&args[i], 2));
			next = args[i + 1];
			if (next && (next[0] == ';' || next[0] == '&' || next[0] == '|'))
				return (createError(&args[i + 1], 2));
		}
	}
	return (0);
}
